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

void GameEngine::selectMap()
{
	//mapLoader->ValidateConnectedGraph(map); //call this somewhere else
	// (1) Select a map from a list of map files as stored in a directory
	string dominationMap;
	MapLoader* mapLoader = new MapLoader();

		cout << "Select the map to play with: ";
		cin >> dominationMap;
		map = mapLoader->GetMap(dominationMap);
	//TODO: check if map is valid
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
		players.at(i)->setArmyNumber(numOfArmies);
	}
}

void GameEngine::chooseFirstPlayer()
{
	int first = randomNumber(0, numOfPlayers - 1);
	firstPlayer = players.at(first);
	cout << *firstPlayer;
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




