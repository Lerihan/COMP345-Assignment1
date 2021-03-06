// COMP345_Assignment1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#include <ctime> // for testing -Michael

#include "MapLoader.h"
#include "Map.h"
#include "Player.h"
#include "Cards.h"
#include "Order.h"
#include "GameEngine.h"
#include "PlayerStrategies.h"

/*
* We can keep this file to test out things here and there
*/

// Forward declarations of driver programs
void driverPart1(); // call for driver program for part 1
void driverPart2(); // call for driver program for part 2
void driverPart3(); // call for driver program for part 3
void driverPart4(); // call for driver program for part 3

int main()
{
	// ASSIGNMENT 2
	// ============
	//driverPart1();
	//driverPart2();
	//driverPart3();
	//driverPart4();
	
	// ASSIGNMENT 3
	// ============
	GameEngine* g = new GameEngine();
	g->startGame();
	g->mainGameLoop();

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
	GameEngine g;
	g.startGame();
	//g.startupPhase();
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
		cout << "The number of initial armies in the reinforcement pool is " << players[i]->getReinforcementPool() << endl;
	}
}

void driverPart3()
{
	cout << "###########################################" << endl;
	cout << "Part 3: Game play: main game loop -- Driver" << endl;
	cout << "###########################################" << endl << endl;

	// (1) a player receives the correct number of armies in the reinforcement phase (showing different cases)
	cout << "Start the game twice using different maps/number of players to show that initial reinforcement pool is correct:" << endl
		<< "---------------------------------------------------------------------------------------------------------------" << endl;
	// run startup phase twice to see how reinforcement pool changes with number of players
	GameEngine* g = new GameEngine;
	g->startGame();
	Player* p = g->getPlayers()[0];

	cout << *p << endl;

	g->reinforcementPhase(p);
	cout << *p << endl;

	p->resetTotalPlayers();
	delete g;
	//delete p;

	// create new GameEngine
	g = new GameEngine;
	g->startGame();
	p = g->getPlayers()[0];

	cout << *p << endl;

	g->reinforcementPhase(p);
	cout << *p << endl << endl;

	// test bonus reinforcements
	cout << "Give the player all territories of a continent to show they get the bonus army value of reinforcements:" << endl
		<< "------------------------------------------------------------------------------------------------------" << endl;
	Player* pTemp = nullptr;
	Territory* tTemp = nullptr;
	for (int i = 0; i < g->getPlayers().size(); i++)
	{
		pTemp = g->getPlayers()[i];
		for (int j = 0; j < pTemp->getTerritories().size(); j++)
		{
			tTemp = pTemp->getTerritories()[j];
			if (tTemp->continentIndex == 1)
			{
				pTemp->removeTerritory(tTemp);
				p->addTerritory(tTemp);
			}
		}
	}
	pTemp = nullptr;
	tTemp = nullptr;
	
	g->reinforcementPhase(p);
	cout << *p << endl;

	// (2) a player will only issue deploy orders and no other kind of orders if they still have armies in their reinforcement pool
	cout << "Player will issue deploy orders until their reinforcement pool is emptied:" << endl
		<< "--------------------------------------------------------------------------" << endl;
	g->issueOrdersPhase(p);

	// (3) the game engine will only execute non-deploy orders when all the deploy orders of all players have been executed
	g->executeOrdersPhase(p);

	for (int i = 0; i < g->getPlayers().size(); i++)
	{
		cout << *g->getPlayers()[i] << endl;
	}

	// (4) a player can issue advance orders to either defend or attack, based on the toAttack() and toDefend() lists


	// (5) a player can play cards to issue orders
	// should see this above when issueOrdersPhase() is called

	// (6) a player that does not control any territory is removed from the game
	//g->mainGameLoop();

	// (7) the game ends when a single player controls all the territories
	// give our Player all Territories so he can win the game
	Territory* t = nullptr; // for readability
	for (int i = 0; i < g->getMap()->listOfTerritories.size(); i++)
	{
		t = g->getMap()->listOfTerritories.at(i);
		if (t->getOwner() != p)
		{
			t->getOwner()->removeTerritory(t);
			p->addTerritory(t);
		}
	}
	t = nullptr;

	cout << "Print Players to show their Territories, and call the mainGameLoop() to kick the eliminated Player and declare the winner:" << endl
		<< "--------------------------------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < g->getPlayers().size(); i++)
	{
		cout << *g->getPlayers().at(i) << endl;
	}

	g->mainGameLoop();
	

}

void driverPart4()
{
	Player* p1 = new Player();
	Player* p2 = new Player();
	Player* p3 = new Player();

	Map m;
	m.name = "World_Map";

	Territory* t1 = new Territory(1, "Canada", 0);
	Territory* t2 = new Territory(2, "United States", 0);
	Territory* t3 = new Territory(3, "Mexico", 0);
	Territory* t4 = new Territory(4, "Vietnam", 1);
	Territory* t5 = new Territory(5, "Japan", 1);
	Territory* t6 = new Territory(6, "Phillipines", 1);

	t3->addTroops(100);
	t1->addTroops(50);
	t2->addTroops(20);

	t1->listOfAdjTerritories.push_back(t2);
	t2->listOfAdjTerritories.push_back(t1);
	t2->listOfAdjTerritories.push_back(t3);
	t3->listOfAdjTerritories.push_back(t2);

	t1->setOwner(p1);
	t2->setOwner(p2);
	t3->setOwner(p3);
	t4->setOwner(p3);
	t5->setOwner(p2);

	Deploy* d1 = new Deploy(p1, t1, 10);
	Advance* a1 = new Advance(p2, t2, t1, 20);
	Bomb* b1 = new Bomb(p3, t2);
	Blockade* blck1 = new Blockade(p2, t5);
	Airlift* air1 = new Airlift(p3, t3, t4, 15);
	Negotiate* n1 = new Negotiate(p2, p3);

	cout << *d1 << endl;
	cout << *a1 << endl;
	cout << *b1 << endl;
	cout << *blck1 << endl;
	cout << *air1 << endl;
	cout << *n1 << endl << endl;

	cout << "===========================================" << endl;
	cout << "Testing validate() and execute() methods..." << endl;
	cout << "===========================================" << endl << endl;

	p1->addReinforcements(20);
	cout << "Deploy class:\n" << endl;
	cout << "Initially, territory has " << t1->numberOfArmies << " armies and its owner has " << p1->getReinforcementPool() << " reinforcements.\n" << endl;
	d1->execute();
	cout << "\nAfter, territory has " << t1->numberOfArmies << " armies and its owner has " << p1->getReinforcementPool() << " reinforcements." << endl;

	cout << endl << endl;

	cout << "Advance class:\n" << endl;
	a1->execute();

	cout << endl << endl;

	cout << "Bomb class:\n" << endl;
	b1->execute();

	cout << endl << endl;

	cout << "Blockade class:\n" << endl;
	blck1->execute();

	cout << endl << endl;

	cout << "Airlift class:\n" << endl;
	air1->execute();

	cout << endl << endl;

	cout << "Negotiate class:\n" << endl;
	n1->execute();

	cout << endl << endl;

	cout << "==============================" << endl;
	cout << "Testing OrdersList......" << endl;
	cout << "==============================" << endl << endl;

	OrdersList* ol = new OrdersList();
	ol->add(d1);
	ol->add(a1);
	ol->add(b1);
	ol->add(blck1);
	ol->add(air1);
	ol->add(n1);

	cout << *ol << endl;

	cout << "Testing moving and removing methods......" << endl;
	cout << "removing Advance order object and Airlift order object......\n" << endl;

	ol->remove(1);
	ol->remove(3);

	cout << *ol << endl;

	cout << "moving the positions of Bomb order object(index=1) to index 2......\n" << endl;

	ol->move(1, 2);

	cout << *ol << endl;

	cout << "moving the positions of Deploy order object(index=0) to index 3......\n" << endl;

	ol->move(0, 3);

	cout << *ol << endl;

	cout << "removing Blockade order object at index 0......\n" << endl;

	ol->remove(0);

	cout << *ol << endl;
}