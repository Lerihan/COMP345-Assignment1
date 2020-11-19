#include "Map.h"
#include "Order.h"
#include "Player.h"
#include <iostream>
#include <string>

using namespace std;

int main()
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
	Bomb* b1 = new Bomb(p3, t3, t2);
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

	return 0;
}