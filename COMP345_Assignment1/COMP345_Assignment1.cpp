// COMP345_Assignment1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "MapLoader.h"
#include "Map.h"
#include "Player.h"
#include "Cards.h"
#include "Order.h"

//#include "PlayerDriver.cpp" // I know I'm not supposed to import a cpp file

int main()
{
	Player* p1 = new Player(); // default constructor
	Player* p2 = new Player("Michael"); // parameterized constructor
	Deck* d = new Deck();
	Territory* t1 = new Territory(0, "Canada");
	Territory* t2 = new Territory(0, "USA");
	Territory* t3 = new Territory(1, "Mexico");
	Territory* t4 = new Territory(2, "Guatemala");
	
	p1->addTerritory(t1);
	p1->addTerritory(t2);
	p2->addTerritory(t3);
	p2->addTerritory(t4);

	// draw five cards and add them to Player p1's Hand
	for (int i = 1; i <= 5; i++) {
		(*d).draw(*p1);
	}
	// draw five cards and add them to Player p2's Hand
	for (int i = 1; i <= 5; i++) {
		(*d).draw(*p2);
	}

	//cout << "test 1" << endl;
	p1->issueOrder();
	p2->issueOrder();

	cout << endl;
	cout << *p1 << endl;
	cout << endl;
	cout << *p2 << endl;
	
  cout << endl;

	Player* p3 = new Player(*p2); // copy constructor
	cout << *p3 << endl;

	//
	////Map Loader
	//MapLoader* mapLoader = new MapLoader();
	//Map* map = mapLoader->GetMap("europe.map");
	//std::cout << endl;
 // 
	///*for (int i = 0; i < map->listOfTerritories.size(); i++)
	//{
	//	map->listOfTerritories[i]->printAdjTerritory();
	//}

	//for (int i = 0; i < map->listOfContinents.size();i++) {
	//	map->listOfContinents[i]->printTerritories();
	//}*/


	//std::cout << endl;

	//cout << *map;
	//cout << *map->getContinent(2);
	//cout << *map->getContinent(2)->getTerritory(8);
	////cout << map->isAdjacent(1, 2) << endl;
	////cout << map->validate() << endl;

	//

	return 0;
}