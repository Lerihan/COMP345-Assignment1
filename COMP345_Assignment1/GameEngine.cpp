#include <iostream>
#include <string>
#include "GameEngine.h"
#include "MapLoader.h"

void GameEngine::startGame()
{
	cout << "Welcome!" << endl; //TODO: change to better message later
	selectMap();
	selectPlayers();
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

	cout << "Select the number of players (2-5): ";
	cin >> playernum; //TODO: add check for playernum

	string playername;
	for (int i = 0; i < playernum; i++)
	{
		cout << "What is the name of player " << (i + 1) << " ?: ";
		cin >> playername;
		Player* p = new Player(playername);
		players.push_back(p);
	}
}


