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
	driverPart3();

	/*
	GameEngine g;
	g.startGame();
	
	Map* m = g.getMap();
	for (Territory* t : m->listOfTerritories)
	{
		//m->printAdjTerritory(t);
		//cout << t->index << endl;
	}

	//cout << m->traverse();

	
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

	GameEngine g;
	g.startGame();

	for (int i = 0; i < g.getPlayers().size(); i++)
	{
		cout << *g.getPlayers()[i] << endl;
	}

	g.mainGameLoop();

	// (1) a player receives the correct number of armies in the reinforcement phase (showing different cases)


	// (2) a player will only issue deploy orders and no other kind of orders if they still have armies in their reinforcement pool

	// (3) the game engine will only execute non-deploy orders when all the deploy orders of all players have been executed

	// (4) a player can issue advance orders to either defend or attack, based on the toAttack() and toDefend() lists

	// (5) a player can play cards to issue orders

	// (6) a player that does not control any territory is removed from the game

	// (7) the game ends when a single player controls all the territories

}