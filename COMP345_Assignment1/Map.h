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
	Territory(int id, string n);
	Territory(const Territory &t); // Copy Constructor
	Territory& operator = (const Territory &t); // Assignment operator
	//~Territory(); // Destructor
	
	void printAdjTerritory();

	int index;
	string name;
	vector<Territory*> listOfAdjTerritories;
	int continentIndex;
	int numberOfArmies;
};





class Continent
{
public:
	Continent(); // Default Constructor
	Continent(int id, string n, int av); 
	Continent(const Continent &c); // Copy Constructor
	Continent& operator = (const Continent &c); // Assignment operator
	//~Continent(); // Destructor
	friend ostream & operator << (ostream &out, const Continent &c);
	friend istream & operator >> (istream &in, Continent &c);

	void addTerritory(Territory* t);
	void printTerritories();
	void printAdjContinents(); //not being used
	Territory* getTerritory(int id);

	int index;
	string name;
	int armyvalue;
	vector<Territory*> listOfTerritories; // per continent
	vector<Continent*> listOfAdjContinents; //Not used ATM
};





// Only 1 map per game, I'm guessing :)
class Map
{
public:
	Map(); // Default Constructor
	Map(string n);
	Map(const Map &m); // Copy Constructor
	Map& operator = (const Map &m); // Assignment operator
	//~Map(); // Destructor
	friend ostream & operator << (ostream &out, const Map &m);
	friend istream & operator >> (istream &in, Map &c);

	void addContinent(Continent* c);
	void addTerritory(Territory* t);
	void addAdjContinent(Continent* c1, Continent* c2);
	void addAdjTerritory(Territory* t1, Territory* t2); //TODO: maybe move this in Continent ?
	bool isAdjacent(int id1, int id2);
	void printContinents();
	Continent* getContinent(int id);
	Territory* getTerritory(int id);

	//TODO: Might delete. Implemented in Continent and Territory class already
	void printAdjContinents(Continent* c);
	void printAdjTerritory(Territory* t);

	string name;
	vector<Continent*> listOfContinents;
	vector<Territory*> listOfTerritories; //all territories
	

	bool validate(); // goes through a few points to validate the map
};









