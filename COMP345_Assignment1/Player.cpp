//  Player.cpp
//  
//  COMP 345
//  Assignment
//  Due Date: November 16, 2020
//  Created by Michael Totarella on 2020-09-23.
//

#include <iostream>
#include <vector>
#include <string>
#include "Player.h"
#include "Order.h"
#include "Map.h"
#include "Cards.h"

//class Territory;

int Player::totalPlayers = 1;

// Default constructor sets attributes to be empty vectors.
Player::Player()
{
	this->playerNumber = totalPlayers++;
	this->name = "DefaultPlayer";
	this->hand = new Hand();
	this->orders = new OrdersList();

	vector<Territory*> terr;
	this->territories = terr; // create empty vector of Territories
}

// Constructor assigns input string to be Player name
Player::Player(string name)
{
	this->playerNumber = totalPlayers++;
	this->name = name;
	this->hand = new Hand();
	this->orders = new OrdersList();

	vector<Territory*> terr;
	this->territories = terr; // create empty vector of Territories
}

// Copy constructor, creates deep copy of each attribute.
// Assume Cards, Order, Territory classes have correctly implemented assignment operators
Player::Player(Player& p)
{
	this->playerNumber = p.playerNumber;
	this->name = p.name;
	this->hand = p.hand; // assumes Hand class assignment operator is correctly implemented
	// copy orders
	this->orders = p.orders; // assumes OrdersList = operator is correctly implemented

	// copy territories
	this->territories = p.territories; // assumes Territory = operator is correctly implemented

	this->numOfArmies = p.numOfArmies;
	/*
	// copy territories
	for (int i = 0; i < p.territories.size(); i++)
	{
		this->territories.push_back(p.territories.at(i));
	}
	*/


}

// Destructor deletes thiss Player object.
// idk if it should also delete all their cards and territories
Player::~Player()
{
	delete this->hand; // delete Player's Hand pointer

	for (int i = 0; i < this->territories.size(); i++)
	{
		delete this->territories[i]; // delete pointer for each Territory
		this->territories[i] = NULL; // avoid dangling pointers
	}
	this->territories.clear(); // remove placeholder memory locations

	delete this->orders; // delete pointer to OrdersList
	delete this; // finally delete this pointer
}

// Returns vector of Territories.
// Should return a new vector of pointers to the same Territory objects
vector<Territory*> Player::getTerritories()
{
	vector<Territory*> t = this->territories;
	
	return t;
}

// Returns the Hand object of this Player
Hand* Player::getHand()
{
	return this->hand;
}

// Returns the OrdersList of this Player
OrdersList* Player::getOrdersList()
{
	return this->orders;
}

// Returns the vector of Orders* contained in the OrdersList member of this Player
// Used for testing only
vector<Order*> Player::getOrders()
{
	return orders->getOrdersList();
}

// sets input Hand to be that of this Player
void Player::setHand(Hand* h)
{
	this->hand = h;
}

int Player::getPlayerNumber()
{
	return playerNumber;
}

string Player::getName()
{
	return name;
}

void Player::setNumOfArmies(int n)
{
	numOfArmies = n;
}

int Player::getNumOfArmies()
{
	return numOfArmies;
}

// Adds the input Territory pointer this Player's Territories vector.
void Player::addTerritory(Territory* t)
{
	this->territories.push_back(t);
	(*t).setOwner(this); // set the owner of the input Territory to be this Player
}

// Returns vector of Territories to attack.
// For now, returns a vector of pointers to two default, newly generated Territories.
vector<Territory*> Player::toAttack()
{
	Territory* attackTerritory1 = new Territory(0, "Attack Territory 1");
	Territory* attackTerritory2 = new Territory(0, "Attack Territory 2");

	vector<Territory*> attackList;
	attackList.push_back(attackTerritory1);
	attackList.push_back(attackTerritory2);

	return attackList;
}


// Returns vector of Territories to defend.
// For now, returns a vector of pointers to two default, newly generated Territories.
vector<Territory*> Player::toDefend()
{
	Territory* defendTerritory1 = new Territory(0, "Attack Territory 1");
	Territory* defendTerritory2 = new Territory(0, "Attack Territory 2");

	vector<Territory*> defendList;
	defendList.push_back(defendTerritory1);
	defendList.push_back(defendTerritory2);

	return defendList;
}

// Adds argument Order to the Player's Order vector attribute.
void Player::issueOrder(Order* o)
{
	this->orders->add(o);
}

// Adds the input number to this Player's reinforcement pool
void Player::addArmies(int toAdd)
{
	this->numOfArmies += toAdd;
}

// = operator, performs deep copy.
// Assume Cards, Order, Territory classes have correctly implemented assignment operators
Player& Player::operator =(const Player& player)
{
	/*
	// perform deep copy of each attribute, same as copy constructor
	for (int i = 0; i < p.hand.size(); i++) {
		Cards c = *p.hand.at(i);
		this.hand.push_back(new Cards(*c));
	}

	for (int i = 0; i < p.orders.size(); i++) {
		Order o = *p.orders.at(i);
		this.orders.push_back(new Order(*o));
	}

	for (int i = 0; i < p.territories.size(); i++) {
		Territory t = *p.territories.at(i);
		this.territories.push_back(new Territory(*t));
	}
	*/

	// copy orders
	this->hand = player.hand; // assumes Hand class assignment operator is correctly implemented

	// copy territories
	for (int i = 0; i < player.territories.size(); i++)
	{
		this->territories.push_back(player.territories.at(i));
	}

	this->hand = player.hand; // assumes Hand assignment operator is correctly implemented

	return *this;
}

// Out stream operator prints Player number, next Order, and occupied Territories.
ostream& operator <<(ostream& strm, Player& player)
{
	string s = "";
	for (int i = 0; i < player.territories.size(); i++)
	{
		s += player.territories.at(i)->name;
		s+= ", ";
	}
	s += "\b\b.";
	return strm << "Player: " << player.name << "\nCards: " << *(player.hand) << "\nTerritories: " << s;
}

// In stream operator, allows user to choose the Player's name.
istream & operator >> (istream& strm,  Player& player)
{
    cout << "Enter Player name: ";
    strm >> player.name;
    return strm;
}

// Equality operator for two Player objects.
// For now, considers two Players equal if they share the same name. Note this is not enforce
bool operator ==(const Player& p1, const Player& p2)
{
	return (p1.name == p2.name);
}

bool operator !=(const Player& p1, const Player& p2)
{
	return !(p1 == p2);
}