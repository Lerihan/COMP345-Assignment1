#pragma once
#include "Map.h"
#include "Player.h"
#include <iostream>
#include <vector>

using namespace std; 

/**
* Melina Phan
* 40094159
*
* Code borrowed:
*		Copy constructor & Assignment operator: GeeksForGeeks.org
*/

class Player;

class Territory
{
public:
	Territory(); // Default Constructor
	Territory(int id, string n, int continentid); //TODO: ADD CONTINENT INDEX TO CONSTRUCTOR
	Territory(const Territory &t); // Copy Constructor
	~Territory(); // Destructor

	void printAdjTerritory();
	void printAdjTerritoryOwned();
	void printAdjTerritoryNotOwned();
	Territory* getAdjTerritoryByName(string name);
	Player* getOwner(); // get owner of this Territory
	void setOwner(Player* p);
	Player * getOwnerOfAdjacent(string name);
	// set the owner of this Territory
	bool isAdjacent(int id);
	bool isAdjacent(string name);
	bool addTroops(int n);
	bool removeTroops(int n);
	bool containsTerritory(vector<Territory*> territories); // checks if this Territory is contained in the input vector
	static bool compareNumArmiesLessThan(Territory* t1, Territory* t2); // compares input Territories according to their number of armies
	static bool compareNumArmiesGreaterThan(Territory* t1, Territory* t2); // compares input Territories according to their number of armies
	static void sortTerritoriesByArmies(vector<Territory*>& toDefend, int increasing); // sorts the Player's Territories by priority to defend

	friend bool operator ==(const Territory& t1, const Territory& t2);
	friend ostream & operator << (ostream &out, const Territory &c);
	Territory& operator = (const Territory& t); // Assignment operator

	int index;
	int continentIndex;
	int numberOfArmies;
	string name;
	Player* owner; // player that owns this Territory
	vector<Territory*> listOfAdjTerritories;
};





class Continent
{
public:
	Continent(); // Default Constructor
	Continent(int id, string n, int av);
	Continent(const Continent &c); // Copy Constructor
	~Continent(); // Destructor

	void addTerritory(Territory* t);
	void printTerritories();
	void printAdjContinents(); //not being used
	Territory* getTerritory(int id);

	bool controlsContinent(Player* player); // checks if the input Player owns the entire Continent

	friend ostream & operator << (ostream &out, const Continent &c);
	Continent& operator = (const Continent& c); // Assignment operator

	int index;
	string name;
	int armyvalue; // control bonus value of Continent
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
	~Map(); // Destructor


	void addContinent(Continent* c);
	void addTerritory(Territory* t);
	void addAdjContinent(Continent* c1, Continent* c2);
	void addAdjTerritory(Territory* t1, Territory* t2); //TODO: maybe move this in Continent ?
	bool isAdjacent(int id1, int id2);
	void printContinents();
	Continent* getContinent(int id);
	Continent* getContinentByName(string name);
	Territory* getTerritory(int id);
	Territory* getTerritoryByName(string name);

	//TODO: Might delete. Implemented in Continent and Territory class already
	void printAdjContinents(Continent* c);
	void printAdjTerritory(Territory* t);

	friend ostream & operator << (ostream &out, const Map &m);
	Map& operator = (const Map& m); // Assignment operator

	string name;
	vector<Continent*> listOfContinents;
	vector<Territory*> listOfTerritories; //all territories


	bool validate(); // goes through a few checks to validate the map
	void mapTraversal(Territory* current, bool visitedTerritories[], bool visitedContinents[]);
};









