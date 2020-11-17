#include <iostream>
#include <string>
#include <ctime>
#include <random>
#include "GameEngine.h"
#include "MapLoader.h"

void GameEngine::startGame()
{
	cout << "Welcome!" << endl; //TODO: change to better message later
	cout << endl;

	selectMap();
	cout << endl;

	selectPlayers();
	cout << endl;

	setObservers();
	cout << endl;

	//start up phase
	startupPhase();

	/* 
	TODO/FIX:
	(1) different valid maps can be loaded and
		their validity is verified(i.e.it is a connected graph, etc.), and invalid maps are gracefully rejected; 
	(2) the right number of players is created, a deck with the right number of cards is created;
	
	
	*/
}

void GameEngine::startupPhase()
{
	chooseFirstPlayer();
	cout << endl;

	setInitialArmies();
	cout << endl;

	/*
	TODO/FIX:
		2. All territories in the map are randomly assigned to players one by one in a round-robin fashion
	*/
}

vector<Player*> GameEngine::getTotalPlayers()
{
	return players;
}

Map * GameEngine::getMap()
{
	return map;
}

string GameEngine::getPhase()
{
	return phase;
}

void GameEngine::selectMap()
{
	string dominationMap;
	MapLoader* mapLoader = new MapLoader();

	do
	{
		cout << "Select the map to play with: ";
		cin >> dominationMap;
		map = mapLoader->GetMap(dominationMap);

		if (map == NULL)
		{
			cout << "Map is invalid." << endl;
		}
	} while (map == NULL);

	//cout << *map;
}

void GameEngine::selectPlayers()
{
	// create all the players, create a deck of cards, and assign an empty hand of
	// cards to each player.
	int playernum = 0;

	do
	{
		cout << "Select the number of players (2-5): ";
		cin >> playernum;

		if (playernum < 2 || playernum > 5)
		{
			cout << "Please enter a valid number of players." << endl;
		}
	} while (playernum < 2 || playernum > 5);

	string playername;
	for (int i = 0; i < playernum; i++)
	{
		cout << "What is the name of player " << (i + 1) << " ?: ";
		cin >> playername;
		Player* p = new Player(playername);
		players.push_back(p);
	}

	numOfPlayers = playernum; // set number of players
}

void GameEngine::setObservers()
{
	char answer;
	cout << "Would you like to turn on the observers ? (y/n): ";
	cin >> answer;

	if (answer == 'y')
	{
		observerOn = true;
		new PhaseObserver(this);
		new GameStatisticsObserver(this);
		cout << "Observers will be on." << endl;
	}
	else if (answer == 'n')
	{
		observerOn = false;
		cout << "Observers will be off." << endl;
	}
}

void GameEngine::setInitialArmies()
{
	// set specific number
	int numOfArmies;
	switch (numOfPlayers)
	{
	case 2:
		numOfArmies = 40;
		break;
	case 3:
		numOfArmies = 35;
		break;
	case 4:
		numOfArmies = 30;
		break;
	case 5:
		numOfArmies = 25;
		break;
	}

	//attach number to all players
	for (int i = 0; i < players.size(); i++)
	{
		players.at(i)->addReinforcements(numOfArmies);
	}
}

void GameEngine::chooseFirstPlayer()
{
	int first = randomNumber(0, numOfPlayers - 1);
	firstPlayer = players.at(first);
	//cout << *firstPlayer;
}

// Code from https://stackoverflow.com/questions/12657962/how-do-i-generate-a-random-number-between-two-variables-that-i-have-stored
int GameEngine::randomNumber(int min, int max)
{
	std::random_device seeder;
	std::mt19937 engine(seeder());
	std::uniform_int_distribution<int> dist(min, max);
	int rand = dist(engine);

	return rand;
}

// Function that controls the main game
// Loops through 3 phases
void GameEngine::mainGameLoop()
{
	int rounds = 0; // number of rounds the game lasted
	Player* winner = NULL;
	do {
		cout << "##########" << endl;
		cout << "Round " << ++rounds;
		cout << "##########" << endl << endl;

		// Reinforcement phase
		cout << "Reinforcement phase:" << endl;
		cout << "====================" << endl;
		for (int i = 0; i < numOfPlayers; i++)
		{
			//cout << "Player " << i << endl;
			reinforcementPhase(players[i]);
		}
		cout << endl;

		// Issuing Orders phase
		cout << "Issuing orders phase:" << endl;
		cout << "=====================" << endl;
		for (int i = 0; i < numOfPlayers; i++)
		{
			issueOrdersPhase(players[i]);
		}
		cout << endl;

		// Orders execution phase
		cout << "Orders execution phase:" << endl;
		cout << "=======================" << endl;
		for (int i = 0; i < numOfPlayers; i++)
		{
			executeOrdersPhase(players[i]);
		}
		cout << endl;

		if (checkWinner() != NULL) // check if a Player has already won before continuing
		{
			endGamePhase(checkWinner());
		}
		kickPlayer(); // check if a Player owns no Territories; if yes, kick them from the game
		winner = checkWinner(); // check if a Player has won the game
	} while (winner == NULL);

}

// Determines how many armies to add to the input Player's reinforcement pool at the start of each reinforcement phase
void GameEngine::reinforcementPhase(Player* currPlayer)
{
	phase = "Reinforcement Phase";

	int newArmies = 3; // minimum number of new armies to assign to Player

	// check if Player owns whole Continent
	int bonusArmies = 0; // if Player gets bonus reinforcements from owning whole Continent
	Continent* currContinent = NULL; // for readability
	for (int i = 0; i < map->listOfContinents.size(); i++ )
	{
		currContinent = map->listOfContinents[i];
		if (currContinent->controlsContinent(currPlayer))
			bonusArmies += currContinent->armyvalue;
	}
	currContinent = NULL;

	// Player gets number of armies equal to their number of Territories / 3, unless this number is less than 3
	if ((currPlayer->getTerritories().size() / 3) < newArmies)
		newArmies = currPlayer->getTerritories().size() / 3;

	cout << "Player " << currPlayer->getPlayerNumber() << " will receive " << newArmies << " new reinforcements " 
		<< "and " << bonusArmies << " bonus reinforcements." << endl;
	currPlayer->addReinforcements(newArmies + bonusArmies); // add armies
}

// Prompts user for Order to be issued and calls issueOrder()
void GameEngine::issueOrdersPhase(Player* currPlayer) {
	
	phase = "Issue Order Phase";

	// issue Deploy orders
	// for simplicity, each Deploy order will deploy all of the Player's reinforcement pool to the first Territory returned by toDefend()
	currPlayer->issueOrder(new Deploy(currPlayer, currPlayer->toDefend()[0], currPlayer->getNumOfArmies()));
	cout << "Player " << currPlayer->getPlayerNumber() << " issued a Deploy order." << endl;

	// issue Advance orders
	// for simplicity, each Advance order will move half the armies from the source Territory to the target Territory

	// first issue an advance order to attack
	Territory* target = currPlayer->toAttack()[0]; // first Territory returned by toAttack() is the Territory to attack
	Territory* source = NULL; // Territory to move armies from
	for (int i = 0; i < target->listOfAdjTerritories.size(); i++)
	{
		// find the first adjacent Territory of toAttack that the Player owns to take armies from
		if (target->listOfAdjTerritories[i]->owner == currPlayer)
		{
			source = target->listOfAdjTerritories[i];
			break;
		}
	}
	// note: order will still be issued if 0 armies are to be moved (e.g. if numberOfArmies = 1, then numberOfArmies / 2 = 0)
	currPlayer->issueOrder(new Advance(currPlayer, source, target, source->numberOfArmies / 2));
	cout << "Player " << currPlayer->getPlayerNumber() << " issued an Advance order." << endl;

	// now issue an advance order to defend
	target = currPlayer->toDefend()[0]; // first Territory returned by toDefend() is the Territory to defend
	int maxArmies = 0;
	for (int i = 0; i < target->listOfAdjTerritories.size(); i++)
	{
		if (target->listOfAdjTerritories[i]->owner == currPlayer)  // if player owns the adjacent territory
		{
			if (target->listOfAdjTerritories[i]->numberOfArmies > maxArmies) // if adjacent territory has more armies, use this one as source
			{
				source = target->listOfAdjTerritories[i];
				maxArmies = target->listOfAdjTerritories[i]->numberOfArmies;
			}
		}
	}
	// note: order will still be issued if 0 armies are to be moved (e.g. if numberOfArmies = 1, then numberOfArmies / 2 = 0)
	currPlayer->issueOrder(new Advance(currPlayer, source, target, source->numberOfArmies / 2));
	cout << "Player " << currPlayer->getPlayerNumber() << " issued an Advance order." << endl;

	target = NULL;
	source = NULL;

	// play the first Card in the Player's Hand
	cout << "Player " << currPlayer->getPlayerNumber() << " played a " << currPlayer->getHand()->cardsInHand[0] << "." << endl;
	currPlayer->getHand()->play();
}

void GameEngine::executeOrdersPhase(Player* currPlayer)
{
	phase = "Execute Order Phase";
	// execute deploy orders
	for (int i = 0; i < currPlayer->getOrders().size(); i++)
	{
		if (currPlayer->getOrders()[i]->getType() == "Deploy")
		{
			cout << "Player " << currPlayer->getPlayerNumber() << " has executed a " << currPlayer->getOrders()[i]->getType() << " order." << endl;
			currPlayer->getOrders()[i]->execute();
			delete currPlayer->getOrders()[i]; // deleting the Order will not change the size of the vector during the loop
			currPlayer->getOrders()[i] = NULL;
		}
	}

	// execute airlift orders
	for (int i = 0; i < currPlayer->getOrders().size(); i++)
	{
		if (currPlayer->getOrders()[i]->getType() == "Airlift")
		{
			cout << "Player " << currPlayer->getPlayerNumber() << " has executed a " << currPlayer->getOrders()[i]->getType() << " order." << endl;
			currPlayer->getOrders()[i]->execute();
			delete currPlayer->getOrders()[i]; // deleting the Order will not change the size of teh vector during the loop
			currPlayer->getOrders()[i] = NULL;
		}
	}

	// execute blockade orders
	for (int i = 0; i < currPlayer->getOrders().size(); i++)
	{
		if (currPlayer->getOrders()[i]->getType() == "Blockade")
		{
			cout << "Player " << currPlayer->getPlayerNumber() << " has executed a " << currPlayer->getOrders()[i]->getType() << " order." << endl;
			currPlayer->getOrders()[i]->execute();
			delete currPlayer->getOrders()[i]; // deleting the Order will not change the size of teh vector during the loop
			currPlayer->getOrders()[i] = NULL;
		}
	}

	// execute all other orders in the order they appear in the OrdersList
	for (int i = 0; i < currPlayer->getOrders().size(); i++)
	{
		cout << "Player " << currPlayer->getPlayerNumber() << " has executed a " << currPlayer->getOrders()[i]->getType() << " order." << endl;
		currPlayer->getOrders()[i]->execute();
		delete currPlayer->getOrders()[i]; // deleting the Order will not change the size of teh vector during the loop
		currPlayer->getOrders()[i] = NULL;
	}
}

// Checks if a Player has lost the game.
// a Player loses if he does not control any Territories
void GameEngine::kickPlayer()
{
	for (int i = 0; i < this->numOfPlayers; i++)
	{
		if (this->players[i]->getTerritories().size() <= 0) // if Player has no Territories delete them from the game
		{
			cout << "Player " << this->players[i]->getPlayerNumber() << " controls no more Territories. They are removed from the game." << endl;
			//delete this->players[i]; //uncomment when Player destructor is fixed; until then there will be memory leak
			this->players.erase(this->players.begin() + i);
			this->players[i] = NULL;
		}

	}
}

// Checks if a Player has won the game; if so return that winning Player, else return NULL
// a Player has won if they conrol all the Territories on the Map
Player* GameEngine::checkWinner()
{
	Player* checkIfWinner = this->players[0]; // to check if it is the same Player that owns all Territories
	for (int i = 1; i < this->getMap()->listOfTerritories.size(); i++)
	{
		if (this->getMap()->listOfTerritories[i]->owner == checkIfWinner) // if owner is different then there is no winner yet
			return NULL;
	}
	return checkIfWinner;
}

// Launches end of game winner message
void GameEngine::endGamePhase(Player* winner)
{
	cout << "########################################" << endl;
	cout << "			Winner!!!" << endl;
	cout << "########################################" << endl;
	cout << "Congratulations, Player " << winner->getPlayerNumber() << "! You won!" << endl;
	cout << "Restart the program to play again." << endl;
}