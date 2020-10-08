#include "Map.h"
#include <string>

/*
* TODO: structure better......
*/
void Map::addAdjContinent(Continent * c1, Continent * c2)
{
	c1->listOfAdjContinents.push_back(c2);
}

void Map::addAdjTerritory(Territory * t1, Territory * t2)
{
	t1->listOfAdjTerritories.push_back(t2);
}

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
}

Map::Map(string n)
{
	name = n;
}

// Map Copy Constructor
Map::Map(const Map &m)
{
	name = m.name;
	listOfContinents = m.listOfContinents;
}

// Map Assignment Operator
Map& Map::operator = (const Map &m)
{
	name = m.name;
	listOfContinents = m.listOfContinents;
	return *this;
}

//Map::~Map()
//{
//	delete this;
//}

ostream& operator << (ostream &out, const Map &m)
{
	out << m.name << endl;

	return out;
}

istream & operator >> (istream &in, Map &m)
{
	/*cout << "Enter Real Part ";
	in >> c.real;
	cout << "Enter Imaginary Part ";
	in >> c.imag;*/
	return in;
}

void Map::addContinent(Continent * c)
{
	listOfContinents.push_back(c);
}

void Map::addTerritory(Territory * t)
{
	listOfTerritories.push_back(t);
}



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
void Map::printAdjContinents(Continent* c)
{
	cout << "Adjacent Continents of Continent '" << c->name << "'" << endl;
	for (int i = 0; i < c->listOfAdjContinents.size(); i++)
	{
		cout << c->listOfAdjContinents.at(i)->name << " -> ";
	}
	cout << endl << endl;
}

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
* Continent Class Functions
*/

// Continent Default Constructor

Continent::Continent()
{
}

//TODO: Add player
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

//Continent::~Continent()
//{
//	delete this;
//}

ostream& operator << (ostream &out, const Continent &c)
{
	//out << c.name << endl;

	return out;
}

istream & operator >> (istream &in, Continent &c)
{
	/*cout << "Enter Real Part ";
	in >> c.real;
	cout << "Enter Imaginary Part ";
	in >> c.imag;*/
	return in;
}

void Continent::addTerritory(Territory * t)
{
	listOfTerritories.push_back(t);
}

void Continent::printTerritories()
{
	cout << "List of Territories of Continent '" << this->name << "'" << endl;
	for (int i = 0; i < this->listOfTerritories.size(); i++)
	{
		cout << i + 1 << ". " << this->listOfTerritories.at(i)->index << " " << this->listOfTerritories.at(i)->name << endl;
	}
	cout << endl;
}

void Continent::printAdjContinents()
{
	cout << "Adjacent Continents of '" << this->name << "'" << endl;
	for (int i = 0; i < this->listOfAdjContinents.size(); i++)
	{
		cout << this->listOfAdjContinents.at(i)->name << " -> ";
	}
	cout << endl << endl;
}

Continent* Map::getContinent(int id)
{
	return listOfContinents[id - 1]; //indices start at 1
}

Territory* Map::getTerritory(int id)
{
	return listOfTerritories[id - 1];
	/*for (int i = 0; i < listOfContinents.size(); i++)
	{
		Continent* c = listOfContinents[i];
		cout << "checking territory #" << c->listOfTerritories.size() << endl;
		for (int j = 0; j < c->listOfTerritories.size(); j++)
		{
			if(c->getTerritory(id) != NULL)
				return c->getTerritory(id);
		}
	}
	return NULL;*/
}






/*
* Territory Class Functions
*/

// Territory Default Constructor
Territory::Territory()
{
}

Territory::Territory(int id, string n)
{
	index = id;
	name = n;
	numberOfArmies = 0;
}

// Territory Copy Constructor
Territory::Territory(const Territory &t)
{
	index = t.index;
	name = t.name;
	listOfAdjTerritories = t.listOfAdjTerritories;
	numberOfArmies = t.numberOfArmies;
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

//Territory::~Territory()
//{
//	delete this;
//}

void Territory::printAdjTerritory()
{
	cout << "Adjacent Territories of '" << this->name << "'" << endl;
	for (int i = 0; i < this->listOfAdjTerritories.size(); i++)
	{
		cout << this->listOfAdjTerritories.at(i)->name << " -> ";
	}
	cout << endl << endl;
}

Territory* Continent::getTerritory(int id)
{
	for (int i = 0; i < listOfTerritories.size(); i++)
	{
		if (listOfTerritories[i]->index == id)
			return listOfTerritories[i];
	}

	return NULL;
}





