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



/*
* Map Class Functions
*/

// Map Default Constructor
Map::Map()
{
}

// Map Copy Constructor
Map::Map(const Map &m)
{
	cout << "Copy constructor called " << endl;
}

// Map Assignment Operator
Map& Map::operator = (const Map &m)
{
	cout << "Assignment operator called " << endl;
	return *this;
}

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
Continent::Continent(string n)
{
	name = n;
}

// Continent Copy Constructor
Continent::Continent(const Continent &c)
{
	cout << "Copy constructor called " << endl;
}

// Continent Assignment Operator
Continent& Continent::operator = (const Continent &c)
{
	cout << "Assignment operator called " << endl;
	return *this;
}

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
		cout << i + 1 << ". " << this->listOfTerritories.at(i)->name << endl;
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





/*
* Territory Class Functions
*/

// Territory Default Constructor
Territory::Territory()
{
}

Territory::Territory(string n)
{
	name = n;
	numberOfArmies = 0;
}

// Territory Copy Constructor
Territory::Territory(const Territory &t)
{
	cout << "Copy constructor called " << endl;
}

// Territory Assignment Operator
Territory& Territory::operator = (const Territory &t)
{
	cout << "Assignment operator called " << endl;
	return *this;
}

void Territory::printAdjTerritory()
{
	cout << "Adjacent Territories of '" << this->name << "'" << endl;
	for (int i = 0; i < this->listOfAdjTerritories.size(); i++)
	{
		cout << this->listOfAdjTerritories.at(i)->name << " -> ";
	}
	cout << endl << endl;
}

