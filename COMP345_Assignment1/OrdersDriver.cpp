#include "Map.h"
#include "Order.h"
#include "Player.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	Player* p1 = new Player("Michael");
	Player* p2 = new Player("Nuo");
	Player* p3 = new Player("Melina");

	Territory* t1 = new Territory(1, "Canada");
	Territory* t2 = new Territory(2, "United States");
	Territory* t3 = new Territory(3, "Mexico");
	Territory* t4 = new Territory(4, "Vietnam");
	Territory* t5 = new Territory(5, "Japan");
	Territory* t6 = new Territory(6, "Phillipines");

	t1->setOwner(p1);
	t2->setOwner(p2);
	t3->setOwner(p3);

	Deploy* d1 = new Deploy(p1, t1, 1000);
	Advance* a1 = new Advance(p2, t2, t1, 5000);
	Bomb* b1 = new Bomb(p3, t3, t2);
	Blockade* blck1 = new Blockade(p1, t1);
	Airlift* air1 = new Airlift(p1, t2, t4, 100);
	Negotiate* n1 = new Negotiate(p2, p3);

	cout << *d1 << endl;
	cout << *a1 << endl;
	cout << *b1 << endl;
	cout << *blck1 << endl;
	cout << *air1 << endl;
	cout << *n1 << endl << endl;

	cout << endl << "==============================" << endl;

	cout << "Testing validate() and execute() methods..." << endl << endl;

	cout << "validate() method of Deploy class: " << d1->validate() << endl;
	d1->execute();

	cout << "validate() method of Advance class: " << a1->validate() << endl;
	a1->execute();

	cout << "validate() method of Bomb class: " << b1->validate() << endl;
	b1->execute();

	cout << "validate() method of Blockade class: " << blck1->validate() << endl;
	blck1->execute();

	cout << "validate() method of Airlift class: " << air1->validate() << endl;
	air1->execute();

	cout << "validate() method of Negotiate class: " << n1->validate() << endl;
	n1->execute();

	cout << endl << "==============================" << endl;

	cout << "Testing OrdersList......" << endl;
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