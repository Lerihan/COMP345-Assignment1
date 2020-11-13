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

	//selectPlayers();
	cout << endl;

	//setObservers();
	cout << endl;

	//start up phase
	//startupPhase();

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

Map * GameEngine::getMap()
{
	return map;
}

void GameEngine::selectMap()
{
	string dominationMap;
	MapLoader* mapLoader = new MapLoader();

	//do
	//{
		cout << "Select the map to play with: ";
		cin >> dominationMap;
		map = mapLoader->GetMap(dominationMap);

		/*if (map == NULL)
		{
			cout << "Map is invalid." << endl;
		}*/
	//} while (map == NULL);

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
		players.at(i)->setNumOfArmies(numOfArmies);
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
	// Reinforcement phase
	for (int i = 0; i < numOfPlayers; i++)
	{
		reinforcementPhase(players[i]);
	}

	// Issuing Orders phase
	for (int i = 0; i < numOfPlayers; i++) // loop through each Player
	{
		// issue Deploy orders
		int totalArmiesDeployed = 0; // continue to prompt user until they have deployed all their armies
		while (totalArmiesDeployed <= this->players[i]->getNumOfArmies()) { // if all Territories have already been looped through then keep
																			// loop until all armies have been deployed
			for (int j = 0; this->players[i]->getTerritories().size(); j++) // loop through each of the Player's Territories
			{
				int armiesToDeploy = 0;
				cout << "How many armies would you like to deploy to " << this->players[i]->getTerritories()[j]->name << "? ";
				cin >> armiesToDeploy;
				this->players[i]->issueOrder(new Deploy(this->players[i], this->players[i]->getTerritories()[j], armiesToDeploy)); // issue the order
				totalArmiesDeployed += armiesToDeploy;
			}
		}

		// issue Advance orders
	}

	// Orders execution phase

	// check if a Player owns no Territories; if yes, kick them from the game
	
}

// Determines how many armies to add to the input Player's reinforcement pool at the start of each reinforcement phase
void GameEngine::reinforcementPhase(Player* p)
{
	int newArmies = 3; // minimum number of new armies to assign to Player
	// check if Player owns whole Continent
	// ...

	// Player gets number of armies equal to their number of Territories / 3, unless this number is less than 3
	if ((p->getTerritories().size() / 3) < newArmies)
		newArmies = p->getTerritories().size() / 3;

	p->addArmies(newArmies); // add armiesPicking 
}

// Prompts user for Order to be issued and calls issueOrder()
int GameEngine::issueOrdersPhase(Player* currPlayer) {
	return 0;
}