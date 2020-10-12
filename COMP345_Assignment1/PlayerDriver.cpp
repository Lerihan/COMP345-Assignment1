//  PlayerDriver.cpp
//  
//  COMP 345
//  Assignment 1, Part 3
//  Due Date: October 12, 2020
//  Created by Michael Totarella on 2020-10-09.
//

#include "Player.h"

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
    
}