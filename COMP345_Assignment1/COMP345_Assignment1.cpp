// COMP345_Assignment1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "MapLoader.h"
#include "Map.h"
#include "Player.h"
#include "Cards.h"
#include "Order.h"

int main()
{

	/*
	Player* p = new Player("Michael"); // create player
	Territory* t = new Territory(1, "Territory 1"); // create Territory
	//Deck* d = new Deck();
	
	p->addTerritory(t); // add territory to player's data member which also sets the player as the territory's owner member
	p->issueOrder();
	cout << *p << endl; // this should print the player p that was created above
	*/


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
	//map->printContinents();
	//map->getContinent(2)->printTerritories();
	//map->getContinent(2)->getTerritory(8)->printAdjTerritory();

	for (int i = 0; i < map->listOfTerritories.size(); i++)
	{
		map->listOfTerritories[i]->printAdjTerritory();
	}


	std::cout << endl;

	cout << map->isAdjacent(1, 2) << endl;
	cout << map->validate() << endl;

	*/

	return 0;
}