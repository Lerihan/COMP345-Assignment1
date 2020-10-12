#include <iostream>
#include "Map.h"

int main()
{
	Map m;
	m.name = "Imaginary_Map";

	//create continents
	Continent c1(1, "North_America", 0);
	Continent c2(2, "Asia", 0);
	Continent c3(3, "Europe", 0);
	Continent c4(4, "Australia", 0);
	m.addContinent(&c1);
	m.addContinent(&c2);
	m.addContinent(&c3);
	m.addContinent(&c4);

	m.addAdjContinent(&c1, &c2);
	m.addAdjContinent(&c1, &c3);
	m.addAdjContinent(&c1, &c4);
	m.addAdjContinent(&c2, &c4);
	m.addAdjContinent(&c3, &c4);

	//create territories
	Territory t1(1, "Canada");
	Territory t2(2, "United States");
	Territory t3(3, "Mexico");
	c1.addTerritory(&t1);
	c1.addTerritory(&t2);
	c1.addTerritory(&t3);
	m.addTerritory(&t1);
	m.addTerritory(&t2);
	m.addTerritory(&t3);

	Territory t4(4, "Vietnam");
	Territory t5(5, "Japan");
	Territory t6(6, "Phillipines");
	c2.addTerritory(&t4);
	c2.addTerritory(&t5);
	c2.addTerritory(&t6);
	m.addTerritory(&t4);
	m.addTerritory(&t5);
	m.addTerritory(&t6);

	Territory t7(7, "France");
	Territory t8(8, "United Kingdom");
	c3.addTerritory(&t7);
	c3.addTerritory(&t8);
	m.addTerritory(&t7);
	m.addTerritory(&t8);

	Territory t9(9, "Australia");
	c4.addTerritory(&t9);
	m.addTerritory(&t9);
	
	m.addAdjTerritory(&t1, &t2);
	m.addAdjTerritory(&t1, &t7);
	m.addAdjTerritory(&t1, &t9);
	m.addAdjTerritory(&t1, &t6);
	m.addAdjTerritory(&t2, &t3);
	m.addAdjTerritory(&t2, &t4);
	m.addAdjTerritory(&t2, &t6);
	m.addAdjTerritory(&t3, &t4);
	m.addAdjTerritory(&t4, &t5);
	m.addAdjTerritory(&t4, &t6);
	m.addAdjTerritory(&t5, &t6);
	m.addAdjTerritory(&t6, &t9);
	m.addAdjTerritory(&t7, &t8);
	m.addAdjTerritory(&t7, &t9);
	m.addAdjTerritory(&t8, &t9);

	m.addAdjTerritory(&t2, &t1);
	m.addAdjTerritory(&t7, &t1);
	m.addAdjTerritory(&t9, &t1);
	m.addAdjTerritory(&t6, &t1);
	m.addAdjTerritory(&t3, &t2);
	m.addAdjTerritory(&t4, &t2);
	m.addAdjTerritory(&t6, &t2);
	m.addAdjTerritory(&t4, &t3);
	m.addAdjTerritory(&t5, &t4);
	m.addAdjTerritory(&t6, &t4);
	m.addAdjTerritory(&t6, &t5);
	m.addAdjTerritory(&t9, &t6);
	m.addAdjTerritory(&t8, &t7);
	m.addAdjTerritory(&t9, &t7);
	m.addAdjTerritory(&t9, &t8);

	cout << m;
	m.getContinent(1)->getTerritory(1)->printAdjTerritory();
	m.getContinent(1)->getTerritory(2)->printAdjTerritory();
	m.getContinent(1)->getTerritory(3)->printAdjTerritory();

	m.getContinent(2)->getTerritory(4)->printAdjTerritory();
	m.getContinent(2)->getTerritory(5)->printAdjTerritory();
	m.getContinent(2)->getTerritory(6)->printAdjTerritory();

	m.getContinent(3)->getTerritory(7)->printAdjTerritory();
	m.getContinent(3)->getTerritory(8)->printAdjTerritory();

	m.getContinent(4)->getTerritory(9)->printAdjTerritory();


	cout << "Calling validate function .................." << endl;
	cout << "It checks if every territory has at least 1 adjacent territory" << endl;
	cout << "It also checks if every territory has a continentIndex" << endl;
	cout << "..." << endl;
	cout << endl;

	if (m.validate())
	{
		cout << "Map is valid" << endl;
	}
	else
	{
		cout << "Map is not valid" << endl;
	}

	cout << endl;

	////Todo List:
//// * Fix map constructor (missing something, might give errors to others)
}
