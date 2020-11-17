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

int main()
{
	//Order* o = new Deploy;
	//cout << o->getType();

	
	GameEngine g;
	g.startGame();
	Map* m = g.getMap();

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