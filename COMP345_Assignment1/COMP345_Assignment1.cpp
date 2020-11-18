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
void driverPart1(); // call for driver program for part 1
void driverPart2(); // call for driver program for part 2
void driverPart3(); // call for driver program for part 3

int main()
{
	//driverPart1();
	//driverPart2();
	driverPart3();

	return 0;
}

void driverPart1()
{
	// DRIVER PART 1
	// -------------

	/*
	(1) different valid maps can be loaded and their validity is verified (i.e. it is a connected graph, etc.), and invalid maps are gracefully rejected;
	(2) the right number of players is created, a deck with the right number of cards is created;
	(3) the observers can be turned on/off during the game start phase */
	cout << "Starting driver for Part 1" << endl;
	cout << "--------------------------" << endl;
	GameEngine g;
	g.startGame();
}

void driverPart2()
{
	// DRIVER PART 2
	// -------------
	/*
	(1) all territories in the map have been assigned to one and only one player;
	(2) Players are given a number of armies which is put in their reinforcement pool */
	cout << "Starting driver for Part 2" << endl;
	cout << "--------------------------" << endl;

	cout << "Check that territories have been assigned one and only one player: " << endl << endl;
	GameEngine g;
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
		cout << "The number of initial armies in the reinforcement pool is " << players[i]->getReinforcementPool() << endl;
	}
}

void driverPart3()
{
	cout << "###########################################" << endl;
	cout << "Part 3: Game play: main game loop -- Driver" << endl;
	cout << "###########################################" << endl;

	/*
	Deck deck;
	/*
	OrdersList o;
	o.add(new Airlift);
	o.add(new Bomb);
	o.add(new Advance);

	for (int i = 0; i < o.getOrdersList().size(); i++)
	{
		cout << o << " " ;
	}
	
	cout << deck.cardsInDeck.size() << endl;
	cout << deck << endl;

	/**/
	GameEngine g;
	g.startGame();

	
	for (int i = 0; i < g.getPlayers().size(); i++)
	{
		cout << *g.getPlayers()[i] << endl;
	}

	/*
	// print toAttack
	Territory* t = NULL;
	for (int i = 0; i < g.getPlayers()[0]->toAttack().size(); i++)
	{
		t = g.getPlayers()[0]->toAttack()[i];
		cout << t->name << " ";
	}
	cout << endl;

	//print toDefend
	for (int i = 0; i < g.getPlayers()[0]->toDefend().size(); i++)
	{
		cout << g.getPlayers()[0]->toDefend()[i]->name << " ";
	}
	*/

	g.mainGameLoop();
	
	// (1) a player receives the correct number of armies in the reinforcement phase (showing different cases)


	// (2) a player will only issue deploy orders and no other kind of orders if they still have armies in their reinforcement pool

	// (3) the game engine will only execute non-deploy orders when all the deploy orders of all players have been executed

	// (4) a player can issue advance orders to either defend or attack, based on the toAttack() and toDefend() lists

	// (5) a player can play cards to issue orders

	// (6) a player that does not control any territory is removed from the game

	// (7) the game ends when a single player controls all the territories

}