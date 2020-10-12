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

	Territory t4(4, "Vietnam");
	Territory t5(5, "Japan");
	Territory t6(6, "Phillipines");
	c2.addTerritory(&t4);
	c2.addTerritory(&t5);
	c2.addTerritory(&t6);

	Territory t7(7, "France");
	Territory t8(8, "United Kingdom");
	c3.addTerritory(&t7);
	c3.addTerritory(&t8);

	Territory t9(9, "Australia");
	c4.addTerritory(&t9);
	
	m.addAdjTerritory(&t1, &t2);
	m.addAdjTerritory(&t1, &t3);
	m.addAdjTerritory(&t1, &t7);
	m.addAdjTerritory(&t1, &t9);
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

	cout << m;
	m.getContinent(1)->getTerritory(1)->printAdjTerritory();

	if (m.validate())
	{
		cout << "Map is Valid";
	}
	else
	{
		cout << "Map is not Valid";
	}

	cout << endl;




	//m.printContinents();
	//c1.printAdjContinents();
	//c3.printTerritories();
	//t4.printAdjTerritory();

	////Todo List:
//// * Fix map constructor (missing something, might give errors to others)
//// * Make Driver!
}
