#pragma once
#include "Map.h"
#include <iostream>
#include <vector>

using namespace std;

/**
* Melina Phan
* 40094159
*
* Code borrowed:
*		Copy constructor & Assignment operator: GeeksForGeeks.org
*		Graph Code from Moodle
*/

class Territory
{
public:
	Territory(); // Default Constructor
	Territory(string n);
	Territory(const Territory &t); // Copy Constructor
	Territory& operator = (const Territory &t); // Assignment operator
	
	void printAdjTerritory();

	string name;
	vector<Territory*> listOfAdjTerritories;
	int numberOfArmies;
};





class Continent
{
public:
	Continent(); // Default Constructor
	Continent(string name); 
	Continent(const Continent &c); // Copy Constructor
	Continent& operator = (const Continent &c); // Assignment operator
	friend ostream & operator << (ostream &out, const Continent &c);
	friend istream & operator >> (istream &in, Continent &c);

	void addTerritory(Territory* t);
	void printTerritories();
	void printAdjContinents();

	string name;
	vector<Territory*> listOfTerritories;
	vector<Continent*> listOfAdjContinents;
};





// Only 1 map per game, I'm guessing :)
class Map
{
public:
	Map(); // Default Constructor
	Map(const Map &m); // Copy Constructor
	Map& operator = (const Map &m); // Assignment operator
	friend ostream & operator << (ostream &out, const Map &m);
	friend istream & operator >> (istream &in, Map &c);

	void addContinent(Continent* c);
	void addAdjContinent(Continent* c1, Continent* c2);
	void addAdjTerritory(Territory* t1, Territory* t2); //TODO: maybe move this in Continent ?

	void printContinents();

	//TODO: Might delete. Implemented in Continent and Territory class already
	void printAdjContinents(Continent* c);
	void printAdjTerritory(Territory* t);

	string* name;
	vector<Continent*> listOfContinents;
	

	bool validate(); // goes through a few points to validate the map
};









