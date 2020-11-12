#include "Map.h"
#include <string>

/*
* Function that connects continent 2 to continent 1 (adjacency) by adding it to a listOfAdjContinents vector
* c1 is first continent, c2 is second continent
*/
void Map::addAdjContinent(Continent * c1, Continent * c2)
{
	c1->listOfAdjContinents.push_back(c2);
}

/*
* Function that connects territory 2 to territory 1 (adjacency) by adding it to a listOfAdjTerritories vector
* t1 is first territory, t2 is second territory
*/
void Map::addAdjTerritory(Territory * t1, Territory * t2)
{
	t1->listOfAdjTerritories.push_back(t2);
}

/*
* Function that checks if 2 territories are adjacent
* id1 is id of first territory, id2 is id of second territory
*/
bool Map::isAdjacent(int id1, int id2)
{
	Territory* t1 = getTerritory(id1);
	Territory* t2 = getTerritory(id2);

	for (int i = 0; i < t1->listOfAdjTerritories.size(); i++)
	{
		if (t1->listOfAdjTerritories.at(i)->index == t2->index)
			return true;
	}

	return false;
}



/*
* Map Class Functions
*/

// Map Default Constructor
Map::Map()
{
	name = "";
}

/*
* Constructor of Map
* n is the name of Map
*/
Map::Map(string n)
{
	name = n;
}

/*
*  Copy Constructor of Map
*/
Map::Map(const Map &m)
{
	name = m.name;
	listOfContinents = m.listOfContinents;
}

/*
* Assignment Operator override of map
*/
Map& Map::operator = (const Map &m)
{
	name = m.name;
	listOfContinents = m.listOfContinents;
	listOfTerritories = m.listOfTerritories;
	return *this;
}

/*
* Destructor
*/
Map::~Map()
{
}


/*
* Add a continent to listOfContinents vector
*/
void Map::addContinent(Continent * c)
{
	listOfContinents.push_back(c);
}

/*
* Add a territory to listOfTerritories vector
*/
void Map::addTerritory(Territory * t)
{
	listOfTerritories.push_back(t);
}

/*
* Print all continents of map
*/
void Map::printContinents()
{
	cout << "List of Continents of Map:" << endl;
	for (int i = 0; i < this->listOfContinents.size(); i++)
	{
		cout << i + 1 << ". " << this->listOfContinents.at(i)->name << endl;
	}
	cout << endl;
}

//Might delete these 2
/*
* Prints all adjacent continents of given continent (c param)
*/
void Map::printAdjContinents(Continent* c)
{
	cout << "Adjacent Continents of Continent '" << c->name << "'" << endl;
	for (int i = 0; i < c->listOfAdjContinents.size(); i++)
	{
		cout << c->listOfAdjContinents.at(i)->name << " -> ";
	}
	cout << endl << endl;
}

/*
* Prints all adjacent territories of given territory (t param)
*/
void Map::printAdjTerritory(Territory* t)
{
	cout << "Adjacent Territories of Territory '" << t->name << "'" << endl;
	for (int i = 0; i < t->listOfAdjTerritories.size(); i++)
	{
		cout << t->listOfAdjTerritories.at(i)->name << " -> ";
	}
	cout << endl << endl;
}

/*
* Function that validates a map
* Checks if connected graph, continents are connected subgraphs, and that each territory has only one continent !
*/
bool Map::validate()
{
	bool b = true;
	//check if map is a connected graph (every territory has adjacent territories)
	//check if continents are connected subgraphs (check if continents have adj cont ???) *** this is not implemented but i dont think theres a need for it
	//check if each territory has one continent
	for (int i = 0; i < listOfTerritories.size(); i++)
	{
		if (listOfTerritories[i]->listOfAdjTerritories.empty() || listOfTerritories[i]->continentIndex != NULL)
		{
			b = false;
		}
	}

	return b;
}

/*
* Stream override
* cout << MapOBJ; will print the following
*/
ostream& operator << (ostream &out, const Map &m)
{
	out << endl;
	out << "--------------------------------------" << endl;
	cout << endl;
	out << "The map name is '" << m.name << "'" << endl;
	out << endl;

	out << "List of Continents of '" << m.name << "' and their Territories (id, name)" << endl;
	out << endl;
	for (int i = 0; i < m.listOfContinents.size(); i++)
	{
		out << m.listOfContinents.at(i)->index << " " << m.listOfContinents.at(i)->name << endl;

		out << "List of Territories of '" << m.listOfContinents.at(i)->name << "'" << endl;
		for (int j = 0; j < m.listOfContinents.at(i)->listOfTerritories.size(); j++)
		{
			out << "   " << j + 1 << ". " << m.listOfContinents.at(i)->listOfTerritories.at(j)->index << " " <<
				m.listOfContinents.at(i)->listOfTerritories.at(j)->name << endl;
		}
		out << endl;
	}

	out << "--------------------------------------" << endl;
	out << endl;

	return out;
}

//istream & operator >> (istream &in, Map &m)
//{
//	string input;
//	cout << "--------------------------------------" << endl;
//	cout << "Map Creation ! Enter 'e' to end." << endl;
//	cout << endl;
//
//	cout << "Enter map name: ";
//	in >> m.name;
//
//	cout << "Enter continent name (make sure you have created a continent first!):";
//	in >> input;
//	
//
//	return in;
//}


/*
* Continent Class Functions
*/

// Continent Default Constructor
Continent::Continent()
{
	index = 0;
	name = "";
	int armyvalue = 0;
}

//TODO: Add player
/*
* Constructor of Continent
* id is index, n is name, av is armyvalue
*/
Continent::Continent(int id, string n, int av)
{
	index = id;
	name = n;
	armyvalue = av;
}

// Continent Copy Constructor
Continent::Continent(const Continent &c)
{
	index = c.index;
	name = c.name;
	armyvalue = c.armyvalue;
	listOfAdjContinents = c.listOfAdjContinents;
	listOfTerritories = c.listOfTerritories;
}

// Continent Assignment Operator
Continent& Continent::operator = (const Continent &c)
{
	index = c.index;
	name = c.name;
	armyvalue = c.armyvalue;
	listOfAdjContinents = c.listOfAdjContinents;
	listOfTerritories = c.listOfTerritories;

	return *this;
}

/*
* Destructor
*/
Continent::~Continent()
{
}

//Stream override
//cout << ContinentOBJ; will print the following
ostream& operator << (ostream &out, const Continent &c)
{
	out << endl;
	out << "--------------------------------------" << endl;
	cout << endl;
	out << "The continent name is '" << c.name << "'" << endl;
	out << endl;

	out << "List of Territories of '" << c.name << "' (id, name)" << endl;
	out << endl;
	for (int i = 0; i < c.listOfTerritories.size(); i++)
	{
		out << i + 1 << ". " << c.listOfTerritories.at(i)->index << " " << c.listOfTerritories.at(i)->name << endl;
	}
	out << endl;
	out << "--------------------------------------" << endl;
	out << endl;

	return out;
}

/*
* Adds a territory (t) to a continent
*/
void Continent::addTerritory(Territory * t)
{
	listOfTerritories.push_back(t);
}

/*
* Prints all territories of a continent
*/
void Continent::printTerritories()
{
	cout << "List of Territories of Continent '" << this->name << "'" << endl;
	for (int i = 0; i < this->listOfTerritories.size(); i++)
	{
		cout << i + 1 << ". " << this->listOfTerritories.at(i)->index << " " << this->listOfTerritories.at(i)->name << endl;
	}
	cout << endl;
}

/*
* Prints all adjacent continents of continent obj.
*/
void Continent::printAdjContinents()
{
	cout << "Adjacent Continents of '" << this->name << "'" << endl;
	for (int i = 0; i < this->listOfAdjContinents.size(); i++)
	{
		cout << this->listOfAdjContinents.at(i)->name << " -> ";
	}
	cout << endl << endl;
}

/*
* Returns a continent object
* id is index of that continent (assigned in maploader from file) and NOT the vector id
*/
Continent* Map::getContinent(int id)
{
	return listOfContinents[id - 1]; //indices start at 1
}

/*
* Returns a territory object
* id is index of that territory (assigned in maploader from file) and NOT the vector id
*/
Territory* Map::getTerritory(int id)
{
	return listOfTerritories[id - 1];
}



/*
* Territory Class Functions
*/

// Territory Default Constructor
Territory::Territory()
{
	index = 0;
	name = "";
	continentIndex = 0;
	numberOfArmies = 0;
	this->owner = NULL;
}

// Constructor for Territory
// id is index, n is name
Territory::Territory(int id, string n)
{
	index = id;
	name = n;
	continentIndex = 0;
	numberOfArmies = 0;

	this->owner = NULL;
}

// Territory Copy Constructor
Territory::Territory(const Territory &t)
{
	index = t.index;
	name = t.name;
	listOfAdjTerritories = t.listOfAdjTerritories;
	continentIndex = t.continentIndex;
	numberOfArmies = t.numberOfArmies;

	this->owner = t.owner;
}

// Territory Assignment Operator
Territory& Territory::operator = (const Territory &t)
{
	index = t.index;
	name = t.name;
	listOfAdjTerritories = t.listOfAdjTerritories;
	numberOfArmies = t.numberOfArmies;
	return *this;
}

// Destructor
Territory::~Territory()
{
	delete owner;
}

/*
* Prints all adjacent territories of current territory obj
*/
void Territory::printAdjTerritory()
{
	cout << "Adjacent Territories of '" << this->name << "'" << endl;
	for (int i = 0; i < this->listOfAdjTerritories.size(); i++)
	{
		cout << this->listOfAdjTerritories.at(i)->name << " -> ";
	}
	cout << endl << endl;
}

/*
* Get territory by id
* Id is the index of that territory and NOT the id of the vector
*/
Territory* Continent::getTerritory(int id)
{
	for (int i = 0; i < listOfTerritories.size(); i++)
	{
		if (listOfTerritories[i]->index == id)
			return listOfTerritories[i];
	}

	return NULL;
}

/*
* Get the owner of the territory
*/
Player* Territory::getOwner()
{
	return this->owner;
}

/*
* Set the owner of the territory
*/
void Territory::setOwner(Player* p)
{
	this->owner = p;
}

bool Territory::isAdjacent(int id)
{
	for (int i = 0; i < listOfAdjTerritories.size(); i++)
	{
		if (listOfAdjTerritories.at(i)->index == id)
			return true;
	}

	return false;
}


bool Territory::addTroops(int n)
{
	if (n > 0)
	{
		numberOfArmies += n;
    return true;
  }
	  return false;
}

// Checks if the input Territory is contained in the input vector
// used for sortTerritoriesToAttack(0
bool Territory::containsTerritory(vector<Territory*> territories, Territory* t)
{
	for (int i = 0; i < territories.size(); i++)
	{
		if (territories[i] == t)
			return true;
  }
  return false;
}
	

// Stream Override for territory
// cout << TerritoryOBJ will print the following
ostream& operator << (ostream &out, const Territory &t)
{
	out << endl;
	out << "--------------------------------------" << endl;
	out << "The Territory name is '" << t.name << "'" << endl;
	out << endl;

	cout << "Adjacent Territories of '" << t.name << "':";
	for (int i = 0; i < t.listOfAdjTerritories.size(); i++)
	{
		cout << t.listOfAdjTerritories.at(i)->name << " -> ";
	}

	cout << endl;
	out << "--------------------------------------" << endl;

	return out;
}

bool operator ==(const Territory& t1, const Territory& t2)
{
	return (t1.index == t2.index && t1.continentIndex == t2.continentIndex && t1.name == t2.name);
}

bool operator !=(const Territory& t1, const Territory& t2)
{
	return !(t1 == t2);
}




