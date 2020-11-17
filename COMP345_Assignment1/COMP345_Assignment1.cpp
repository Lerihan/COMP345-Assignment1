// COMP345_Assignment1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "MapLoader.h"
#include "Map.h"
#include "Player.h"
#include "Cards.h"
#include "Order.h"

#include "GameEngine.h"

/*
* We can keep this file to test out things here and there
*/

// Forward declarations of driver programs
void driverPart3(); // call for driver program for part 3

int main()
{
	// DRIVER PART 1
	// -------------
  
	driverPart3();
  
	/*
	(1) different valid maps can be loaded and their validity is verified (i.e. it is a connected graph, etc.), and invalid maps are gracefully rejected; 
	(2) the right number of players is created, a deck with the right number of cards is created; 
	(3) the observers can be turned on/off during the game start phase */
	cout << "Starting driver for Part 1" << endl;
	cout << "--------------------------" << endl;
	GameEngine g;
	g.startGame();

	// DRIVER PART 2
	// -------------
	/*
	(1) all territories in the map have been assigned to one and only one player; 
	(2) Players are given a number of armies which is put in their reinforcement pool */
	cout << "Starting driver for Part 2" << endl;
	cout << "--------------------------" << endl;

	cout << "Check that territories have been assigned one and only one player: " << endl << endl;
	Map* m = g.getMap();
	for (int i = 0; i < m->listOfTerritories.size(); i++)
	{
		cout << "The owner of Territory '" << m->listOfTerritories[i]->name << "' is Player " << m->listOfTerritories[i]->owner->getPlayerNumber() << endl;
	}

	cout << endl;
	cout << "Check that players are given an inital number of armies" << endl << endl;
	vector<Player*> players = g.getPlayers();
	for (int i = 0; i < players.size(); i++)
	{
		cout << "The number of initial armies in the reinforcement pool is " << players[i]->getNumOfReinforcement() << endl;
	}

	//Order* o = new Deploy;
	//cout << o->getType();


	/**
	Territory* t1 = new Territory(0, "Canada");
	Territory* t2 = new Territory(0, "USA");
	Territory* t3 = new Territory(0, "Mexico");

	std::vector<Territory*> t;
	t.push_back(t1);
	t.push_back(t2);
	t.push_back(t3);
	t.push_back(t3);

	for (int i = 0; i < t.size(); i++)
	{
		cout << *t[i] << endl;
	}

	delete t1;
	delete t2;
	delete t3;
	t1, t2, t3 = NULL;
	t.clear();
	*/

	return 0;
}

void driverPart3()
{
	cout << "###########################################" << endl;
	cout << "Part 3: Game play: main game loop -- Driver" << endl;
	cout << "###########################################" << endl;

}