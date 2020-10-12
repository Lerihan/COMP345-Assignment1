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
	cout << "test 1" << endl;
	p1->issueOrder();
	p2->issueOrder();
	cout << "test 2" << endl;
	cout << endl;
	cout << *p1 << endl; // problem with OrdersList default constructor, throws seg fault
	cout << endl;
	cout << *p2 << endl;


	/*

	//Map
	//TODO:
	// * Clean up stream override functions (+add it for Territory)
	// * Constructors (Destructors ?)
	Map m;

	//////create continents
	Continent c1(0, "North America", 0);
	Continent c2(1, "Asia", 0);
	Continent c3(2, "Europe", 0);
	Continent c4(3, "Australia", 0);
	m.addContinent(&c1);
	m.addContinent(&c2);
	m.addContinent(&c3);
	m.addContinent(&c4);

	//m.addAdjContinent(&c1, &c2);
	//m.addAdjContinent(&c1, &c3);
	//m.addAdjContinent(&c1, &c4);
	//m.addAdjContinent(&c2, &c4);
	//m.addAdjContinent(&c3, &c4);

	//

	////create territories
	Territory t1(1, "Canada");
	Territory t2(2, "United States");
	Territory t3(3, "Mexico");
	c1.addTerritory(&t1);
	c1.addTerritory(&t2);
	c1.addTerritory(&t3);

	//Territory t4("Vietnam");
	//Territory t5("Japan");
	//Territory t6("Phillipines");
	//c2.addTerritory(&t4);
	//c2.addTerritory(&t5);
	//c2.addTerritory(&t6);

	//Territory t7("France");
	//Territory t8("United Kingdom");
	//c3.addTerritory(&t7);
	//c3.addTerritory(&t8);

	//Territory t9("Australia");
	//c4.addTerritory(&t9);
	//
	//m.addAdjTerritory(&t1, &t2);
	//m.addAdjTerritory(&t1, &t3);
	//m.addAdjTerritory(&t1, &t7);
	//m.addAdjTerritory(&t1, &t9);
	//m.addAdjTerritory(&t2, &t3);
	//m.addAdjTerritory(&t2, &t4);
	//m.addAdjTerritory(&t2, &t6);
	//m.addAdjTerritory(&t3, &t4);
	//m.addAdjTerritory(&t4, &t5);
	//m.addAdjTerritory(&t4, &t6);
	//m.addAdjTerritory(&t5, &t6);
	//m.addAdjTerritory(&t6, &t9);
	//m.addAdjTerritory(&t7, &t8);
	//m.addAdjTerritory(&t7, &t9);
	//m.addAdjTerritory(&t8, &t9);



	//m.printContinents();
	//c1.printAdjContinents();
	//c3.printTerritories();
	//t4.printAdjTerritory();

	//Map Loader
	MapLoader* mapLoader = new MapLoader();
	Map* map = mapLoader->GetMap("europe.map");
	std::cout << endl;
  
	for (int i = 0; i < map->listOfTerritories.size(); i++)
	{
		map->listOfTerritories[i]->printAdjTerritory();
	}

	for (int i = 0; i < map->listOfContinents.size();i++) {
		map->listOfContinents[i]->printTerritories();
	}


	std::cout << endl;

	cout << *map;
	cout << *map->getContinent(2);
	cout << *map->getContinent(2)->getTerritory(8);
	//cout << map->isAdjacent(1, 2) << endl;
	//cout << map->validate() << endl;

//Todo List:
// * Fix map constructor (missing something, might give errors to others)
// * Make Driver!
	*/

	return 0;
}