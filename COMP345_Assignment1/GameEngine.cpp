#include <iostream>
#include <string>
#include <ctime>
#include <random>
#include <algorithm>
#include <chrono> 
#include "GameEngine.h"

GameEngine::~GameEngine()
{
	delete this->map;
	delete this->deck;
	this->firstPlayer = NULL;

	for (int i = 0; i < this->players.size(); i++)
	{
		delete this->players[i];
		this->players[i] = NULL;
	}
	this->players.clear();
}

void GameEngine::startGame()
{
	cout << "Welcome!" << endl;
	cout << endl;

	selectMap();
	cout << endl;

	createComponents();
	cout << endl;

	setObservers();
	cout << endl;

	//start up phase
	startupPhase();
}

void GameEngine::startupPhase()
{
	setRandomOrder();
	cout << endl;

	setRandomTerritory();
	cout << endl;

	setInitialArmies();
	cout << endl;
}

Map * GameEngine::getMap()
{
	return map;
}

// Accessor of the GameEngine's players vector
vector<Player*> GameEngine::getPlayers()
{
	return this->players;
}

string GameEngine::getPhase()
{
	return phase;
}

Deck* GameEngine::getDeck()
{
	return this->deck;
}

void GameEngine::selectMap()
{
	string dominationMap;
	MapLoader* mapLoader = new MapLoader();
	bool isValid = false;

	do
	{
		cout << "Select the map to play with: ";
		cin >> dominationMap;
		map = mapLoader->GetMap(dominationMap);

		if(map != NULL)
			isValid = map->validate();

		if (map == NULL || !isValid)
		{
			cout << "Map is invalid." << endl;
		}
	} while (map == NULL || !isValid);

	delete mapLoader;
}

void GameEngine::createComponents()
{
	// how many players
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
	numOfPlayers = playernum; // set number of players

	// create deck and players with set hand
	deck = new Deck();

	for (int i = 0; i < playernum; i++)
	{
		Player* p = new Player(); // deallocate memory later

		// Draw 5 cards from the deck and place it in the player's hand
		for (int i = 0; i < 5; i++)
		{
			deck->draw(p);
		}

		players.push_back(p);
	}
}

void GameEngine::setObservers()
{
	char answer;

  do
  {
    cout << "Would you like to turn on the observers ? (y/n): ";
    cin >> answer;

    if (answer == 'y')
    {
      observerOn = true;
      new PhaseObserver(this);
      new GameStatisticsObserver(this);
      cout << "Observers will be on." << endl;
      break;
    }
    else if (answer == 'n')
    {
      observerOn = false;
      cout << "Observers will be off." << endl;
      break;
    }
  } while (answer != 'y' || answer != 'n');
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

// shuffle code from: http://www.cplusplus.com/reference/algorithm/shuffle/
void GameEngine::setRandomOrder()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(players.begin(), players.end(), std::default_random_engine(seed));

	std::cout << "The playing order is: ";
	for (int i = 0; i < numOfPlayers; i++)
	{
		cout << players[i]->getPlayerNumber() << " ";
	}
	cout << endl;
}

void GameEngine::setRandomTerritory()
{
	vector<Territory*> territoriesCopy = map->listOfTerritories;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(territoriesCopy.begin(), territoriesCopy.end(), std::default_random_engine(seed));

	int turn = 0;
	for (int i = 0; i < territoriesCopy.size(); i++)
	{
		territoriesCopy[i]->setOwner(players[turn]); // set the owner of this Territory to be the Player it is assigned to
		players[turn]->addTerritory(territoriesCopy[i]);
		turn++;

		if (turn > (players.size() - 1))
			turn = 0;
	}

	/* FOR DRIVER
	for (int j = 0; j < players.size(); j++)
	{
		cout << "Player " << j << "'s Territories" << endl;
		vector<Territory*> temp = players[j]->getTerritories();
		for (int i = 0; i < players[j]->getTerritories().size(); i++)
		{
			cout << temp[i]->name << endl;
		}
		cout << endl;
	}
	*/
}

// Function that controls the main game
// Loops through 3 phases
void GameEngine::mainGameLoop()
{
	int rounds = 0; // number of rounds the game lasted
	Player* winner = NULL;
	do {
		cout << "========" << endl;
		cout << "Round " << ++rounds << endl;
		cout << "========" << endl << endl;

		// Reinforcement phase
		cout << "Reinforcement phase:" << endl;
		cout << "--------------------" << endl;
		for (int i = 0; i < this->players.size(); i++)
		{
			if (!this->players[i]->isEliminated())
			{
				reinforcementPhase(players[i]);
				notify();
			}
		}
		cout << endl;

		for (int i = 0; i < this->players.size(); i++)
		{
			cout << *this->players[i] << endl;
		}
		cout << endl;
		// Issuing Orders phase
		cout << "Issuing orders phase:" << endl;
		cout << "---------------------" << endl;
		for (int i = 0; i < this->players.size(); i++)
		{
			if (!this->players[i]->isEliminated())
			{
				issueOrdersPhase(players[i]);
				notify();
			}
		}
		cout << endl;
		for (int i = 0; i < this->players.size(); i++)
		{
			cout << *(this->players[i]->getOrdersList()) << endl;
		}

		// Orders execution phase
		cout << "Orders execution phase:" << endl;
		cout << "-----------------------" << endl;
		for (int i = 0; i < this->players.size(); i++)
		{
			if (!this->players[i]->isEliminated())
			{
				executeOrdersPhase(players[i]);
				notify();
			}
		}
		cout << endl;

		kickPlayers(); // check if a Player owns no Territories; if yes, kick them from the game
		winner = checkWinner(); // check if a Player has won the game
	} while (winner == NULL);

	endGamePhase(winner);
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
	if ((currPlayer->getTerritories().size() / 3) > newArmies)
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
	Territory* source = target; // Territory to move armies from
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
	Card* c = currPlayer->getHand()->cardsInHand[0]; // for readability
	cout << "Player " << currPlayer->getPlayerNumber() << " played a " << c->getType() << "." << endl;

	/*
	// check for each type of card so the proper data members can be created
	// need to downcast each Card to be able to set subclass data members
	// for all orders that need a target Territory, take the first one returned in Player's toAttack()
	// for all orders that need a source Territory, take the first one returned in Player's toDefend()
	if (c->getType() == "BombCard")
	{
		((BombCard*)c)->setTarget(currPlayer->toAttack()[0]);
		((BombCard*)c)->setSource(currPlayer->toDefend()[0]);
	}
	else if (c->getType() == "ReinforcementCard")
	{
		// nothing needs to be done here I think but leave this if statement for now
	}
	else if (c->getType() == "BlockadeCard")
	{
		((BlockadeCard*)c)->setTarget(currPlayer->toAttack()[0]);
	}
	else if (c->getType() == "AirliftCard")
	{
		// for now, make Airlift only to one of the current Player's Territories
		((AirliftCard*)c)->setTarget(currPlayer->toDefend()[0]);
	}
	else if (c->getType() == "DiplomacyCard")
	{
		// set enemey to be the owner of first Territory returned by Player's toAttack()
		((DiplomacyCard*)c)->setEnemy(currPlayer->toAttack()[0]->getOwner());
	}
	*/

	c = NULL;
	currPlayer->getHand()->play();
}

void GameEngine::executeOrdersPhase(Player* currPlayer)
{
	phase = "Execute Order Phase";
	// execute deploy orders
	for (int i = 0; i < currPlayer->getOrders().size(); i++)
	{
		if (!currPlayer->getOrders()[i]->isExecuted())
		{
			if (currPlayer->getOrders()[i]->getType() == "Deploy")
			{
				cout << "Player " << currPlayer->getPlayerNumber() << " has executed a " << currPlayer->getOrders()[i]->getType() << " order." << endl;
				currPlayer->getOrders()[i]->execute();
				delete currPlayer->getOrders()[i]; // deleting the Order will not change the size of the vector during the loop
				currPlayer->getOrders()[i] = NULL;
			}
		}
	}

	// execute airlift orders
	for (int i = 0; i < currPlayer->getOrders().size(); i++)
	{
		if (!currPlayer->getOrders()[i]->isExecuted())
		{
			if (currPlayer->getOrders()[i]->getType() == "Airlift")
			{
				cout << "Player " << currPlayer->getPlayerNumber() << " has executed a " << currPlayer->getOrders()[i]->getType() << " order." << endl;
				currPlayer->getOrders()[i]->execute();
				delete currPlayer->getOrders()[i]; // deleting the Order will not change the size of teh vector during the loop
				currPlayer->getOrders()[i] = NULL;
			}
		}
	}

	// execute blockade orders
	for (int i = 0; i < currPlayer->getOrders().size(); i++)
	{
		if (!currPlayer->getOrders()[i]->isExecuted())
		{
			if (currPlayer->getOrders()[i]->getType() == "Blockade")
			{
				cout << "Player " << currPlayer->getPlayerNumber() << " has executed a " << currPlayer->getOrders()[i]->getType() << " order." << endl;
				currPlayer->getOrders()[i]->execute();
				delete currPlayer->getOrders()[i]; // deleting the Order will not change the size of teh vector during the loop
				currPlayer->getOrders()[i] = NULL;
			}
		}
	}

	// execute all other orders in the order they appear in the OrdersList
	for (int i = 0; i < currPlayer->getOrders().size(); i++)
	{
		if (!currPlayer->getOrders()[i]->isExecuted())
		{
			cout << "Player " << currPlayer->getPlayerNumber() << " has executed a " << currPlayer->getOrders()[i]->getType() << " order." << endl;
			currPlayer->getOrders()[i]->execute();
			delete currPlayer->getOrders()[i]; // deleting the Order will not change the size of teh vector during the loop
			currPlayer->getOrders()[i] = NULL;
		}
	}
	// TODO: should we delete the execute orders here, or just leave them as executed?
}

// Checks if a Player has lost the game.
// a Player loses if he does not control any Territories
void GameEngine::kickPlayers()
{
	Player* currPlayer = NULL; // for readability
	for (int i = 0; i < this->getPlayers().size(); i++)
	{
		currPlayer = this->players[i];
		if (currPlayer->getTerritories().size() <= 0) // if Player has no Territories kick them from the game
		{
			cout << "Player " << currPlayer->getPlayerNumber() << " controls no more Territories. They are removed from the game." << endl;
			
			// put the losing Player's Cards back in the Deck
			Hand* hand = currPlayer->getHand(); // for readability
			for (int j = 0; j < hand->getCardsInHand().size(); j++)
			{
				this->deck->insertBackToDeck(hand->getCardsInHand()[j]); // put each Card back in the Deck
				hand->getCardsInHand()[j] = NULL;
			}
			hand->getCardsInHand().clear(); // Player's Hand size is now 0
			hand = NULL;
			currPlayer->eliminatePlayer();
		}
	}
	currPlayer = NULL;
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
