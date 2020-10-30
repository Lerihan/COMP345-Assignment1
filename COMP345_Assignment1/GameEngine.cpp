#include <iostream>
#include <string>
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

	/*You must deliver a driver that demonstrates that
	(1) different valid maps can be loaded and
		their validity is verified(i.e.it is a connected graph, etc.), and invalid maps are gracefully rejected; 
	(2) the right number of players is created, a deck with the right number of cards is created; 
	(3) the observers can be turned on / off during the game start phase*/
}

void GameEngine::selectMap()
{
	//CAN PUT THIS INTO MAPLAODER.CPP LATER WHEN REFACTORING
	//mapLoader->ValidateConnectedGraph(map); //call this somewhere else
	// (1) Select a map from a list of map files as stored in a directory
	string dominationMap;
	MapLoader* mapLoader = new MapLoader();

	cout << "Select the map to play with: ";
	cin >> dominationMap;
	map = mapLoader->GetMap(dominationMap);

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




