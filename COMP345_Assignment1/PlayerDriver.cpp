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
    // ####################################################
	// Test Player constructors
    // ####################################################
    cout << "####################################################\n";
	cout << "Test Player constructors\n";
    cout << "####################################################\n\n";

    Player* p1 = new Player(); // default constructor
	cout << "Default Constructor Player\n";
	cout << "==========================\n";
	cout << *p1 << endl << endl;

	Player* p2 = new Player("ParameterizedPlayer"); // parameterized constructor
	cout << "Parameterized Constructor Player\n";
	cout << "================================\n";
	cout << *p2 << "\n" << endl;

	Player* p3 = new Player(*p2); // copy constructor
	cout << "Copy Constructor Player (copy of parameterized Player)\n";
	cout << "======================================================\n";
	cout << *p3 << endl << endl;


	// ####################################################
	// Test Player member functions
    // ####################################################
    cout << "\n####################################################\n";
	cout << "Test Player members\n";
    cout << "####################################################\n\n";

	// create a Deck and some Territories to use in functions test
	Deck* d = new Deck();
	Territory* t1 = new Territory(0, "Canada", 0); // create Canada, part of continent 0
	Territory* t2 = new Territory(0, "USA", 1); // create USA, part of continent 0
	Territory* t3 = new Territory(1, "Mexico", 0); // create Mexico, part of continent 1
	Territory* t4 = new Territory(2, "Guatemala", 0); // create Guatemla, part of continent 2
	
	// check that added Territories appear in Player member
	p1->addTerritory(t1);
	p1->addTerritory(t2);
	cout << "Added 2 Territories to Default Constructor Player\n";
	cout << "=================================================\n";
	cout << *p1 << endl << endl;

	p2->addTerritory(t3);
	p2->addTerritory(t4);
	cout << "Added 2 Territories to Parameterized Constructor Player\n";
	cout << "=======================================================\n";
	cout << *p2 << endl << endl;

	// draw five cards and add them to Player p1's Hand
	cout << "Default Player will draw 5 Cards:\n";
	for (int i = 1; i <= 5; i++) {
		(*d).draw(p1);
	}
	cout << "=======================================\n";
	cout << *p1 << endl << endl;

	// draw five cards and add them to Player p2's Hand
	cout << "Parameterized Player will draw 5 Cards:\n";
	for (int i = 1; i <= 5; i++) {
		(*d).draw(p2);
	}
	cout << "=======================================\n";
	cout << *p2 << endl << endl;

	// test issueOrder()
	p1->setStrategy(new AggressivePlayerStrategy());
	p1->issueOrder();
	cout << "Default Constructor Player has issued 1 Order:\n";
	cout << "==============================================\n";
	for (int i = 0; i < (*p1).getOrders().size(); i++)
	{
		cout << typeid(*(*p1).getOrders().at(i)).name() << " ";
	}

	p1->issueOrder();
	cout << endl << endl;
	cout << "Default Constructor Player has issued another Order. There should now be 2:\n";
	cout << "===========================================================================\n";
	for (int i = 0; i < (*p1).getOrders().size(); i++)
	{
		cout << typeid(*(*p1).getOrders().at(i)).name();
		cout << " ";
	}

	p2->setStrategy(new BenevolentPlayerStrategy());
	p2->issueOrder();
	cout << endl << endl;
	cout << "Parameterized Constructor Player has issued an Order. There should now be 1:\n";
	cout << "===========================================================================\n";
	for (int i = 0; i < (*p2).getOrders().size(); i++)
	{
		cout << typeid(*(*p2).getOrders().at(i)).name();
		cout << " ";
	}
	cout << *p2 << endl << endl;
	p2->issueOrder();
	cout << endl << endl;
	cout << "Parameterized Constructor Player has issued an Order. There should now be 2:\n";
	cout << "===========================================================================\n";
	for (int i = 0; i < (*p2).getOrders().size(); i++)
	{
		cout << typeid(*(*p2).getOrders().at(i)).name();
		cout << " ";
	}
	cout << *p2 << endl << endl;
	p2->issueOrder();
	cout << endl << endl;
	cout << "Parameterized Constructor Player has issued an Order. There should now be 3:\n";
	cout << "===========================================================================\n";
	for (int i = 0; i < (*p2).getOrders().size(); i++)
	{
		cout << typeid(*(*p2).getOrders().at(i)).name();
		cout << " ";
	}
	cout << *p2 << endl << endl;
	p2->issueOrder();
	cout << endl << endl;
	cout << "Parameterized Constructor Player has issued an Order. There should now be 4:\n";
	cout << "===========================================================================\n";
	for (int i = 0; i < (*p2).getOrders().size(); i++)
	{
		cout << typeid(*(*p2).getOrders().at(i)).name();
		cout << " ";
	}
	cout << *p2 << endl << endl;
	p2->issueOrder();
	cout << endl << endl;
	cout << "Parameterized Constructor Player has issued an Order. There should now be 5:\n";
	cout << "===========================================================================\n";
	for (int i = 0; i < (*p2).getOrders().size(); i++)
	{
		cout << typeid(*(*p2).getOrders().at(i)).name();
		cout << " ";
	}
	cout << *p2 << endl << endl;

	cout << endl << endl;
	cout << "Parameterized Constructor Player will now call toDefend(). Note this returns a list of arbitrary (newly-created) Territories.\n";
	cout << "The returned Territories will NOT be those owned by the Player.\n";
	cout << "=============================================================================================================================\n";
	vector<Territory*> toDefend = p2->toDefend(); // return vector of arbitrary Territories
	for (int i = 0; i < toDefend.size(); i++) // print them out using the output stream of Territory class
	{
		cout << *(toDefend.at(i)); // dereference pointer and print Territory
	}

	cout << endl;
	cout << "Parameterized Constructor Player will now call toAttack(). Note this returns a list of arbitrary (newly-created) Territories.\n";
	cout << "The returned Territories will NOT be those owned by the Player.\n";
	cout << "=============================================================================================================================\n";
	vector<Territory*> toAttack = p2->toAttack(); // return vector of arbitrary Territories
	for (int i = 0; i < toAttack.size(); i++) // print them out using the output stream of Territory class
	{
		cout << *(toAttack.at(i)); // dereference pointer and print Territory
	}

	// ####################################################
	// Additional Copy Player Constructor test
    // ####################################################
    cout << "\n####################################################\n";
	cout << "Additional Copy Constructor Player test\n";
    cout << "####################################################\n\n";

	cout << "Recall the Parameterized Constructor Player\n";
	cout << "===========================================\n";
	cout << *p2 << endl << endl;

	Player* p4 = new Player(*p2); // create another copy of parameterized Player 2
	cout << "Create another copy of the Parameterized Constructor Player\n";
	cout << "===========================================================\n";
	cout << *p4 << endl << endl;

	Territory* t5 = new Territory(3, "Mongolia", 0);
	p4->addTerritory(t5);
	cout << "Will add the following Territory to the copy of the Parameterized Constructor Player and show it doesn't affect the\n";
	cout << "original Parameterized Constructor Player\n";
	cout << "===================================================================================================================\n";
	cout << *t5 << endl;

	cout << "Original Parameterized Constructor Player SHOULD NOT have Mongolia in their Territories\n";
	cout << "=======================================================================================\n";
	cout << *p2 << endl << endl;

	cout << "New copy of Parameterized Constructor Player SHOULD have Mongolia in their Territories\n";
	cout << "======================================================================================\n";
	cout << *p4 << endl << endl;

	return 0;
}