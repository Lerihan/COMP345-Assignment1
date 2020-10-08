//  Player.cpp
//  
//  COMP 345
//  Assignment 1, Part 3
//  Due Date: October 9, 2020
//  Created by Michael Totarella on 2020-09-23.
//

#include <iostream>
#include <vector>
#include <string>
#include "Player.h"
#include "Order.h"
#include "Map.h"
#include "Cards.h"

// Default constructor sets attributes to be empty vectors.
Player::Player()
{
	this->name = "NoName";
	//this->playerNumber = ++playerCount; // increment total number of players and assign a number to this Player
	//this->hand = std::vector<Cards*>;
	//this->orders = std::vector<Order*>;
	//this->territories = std::vector<Territory*>;
}

// Constructor assigns input string to be Player name
Player::Player(string name)
{
	this->name = name;
}

// Copy constructor, creates deep copy of each attribute.
// Assume Cards, Order, Territory classes have correctly implemented assignment operators
Player::Player(Player& p)
{
	// copy orders
	for (int i = 0; i < p.orders.size(); i++)
	{
		this->orders.push_back(p.orders.at(i));
	}
	// copy hand of cards
	for (int i = 0; i < p.hand.size(); i++)
	{
		this->hand.push_back(p.hand.at(i));
	}
	// copy territories
	for (int i = 0; i < p.territories.size(); i++)
	{
		this->territories.push_back(p.territories.at(i));
	}

	this->name = p.name;

}

// Destructor deletes thiss Player object.
// idk if it should also delete all their cards and territories
Player::~Player()
{
	delete this;
}

// Returns vector of Territories.
// Should return a new vector of pointers to the same Territory objects
vector<Territory*> Player::getTerritories()
{
	vector<Territory*> t = this->territories;
	
	return t;
}

// Adds the input Territory pointer this Player's Territories vector.
void Player::addTerritory(Territory* t)
{
	this->territories.push_back(t);
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
// for now just adds a default Deploy order
void Player::issueOrder()
{
	Deploy* d = new Deploy();
	this->orders.push_back(d); // add pointer to new order to end of order list
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
	for (int i = 0; i < player.orders.size(); i++)
	{
		this->orders.push_back(player.orders.at(i));
	}
	// copy hand of cards
	for (int i = 0; i < player.hand.size(); i++)
	{
		this->hand.push_back(player.hand.at(i));
	}
	// copy territories
	for (int i = 0; i < player.territories.size(); i++)
	{
		this->territories.push_back(player.territories.at(i));
	}

	return *this;
}

// Out stream operator prints Player number, next Order, and occupied Territories.
ostream& operator <<(ostream& strm, Player& player)
{
	string s = "";
	// create list of Territory names to output to console
	for (int i = 0; i < player.territories.size(); i++)
	{
		Territory t = *player.territories.at(i); // only works if I make this line separate from the one below for some reason
		string name = t.name;
		s += name;
		s += ", ";
	}
	s += "\b \b.";
	//return strm << "Player " << player.name << "\nNext order: " << player.orders.at(0) << "\nTerritories: " << s << endl;
	return strm << "Player " << player.name << "\nNumber of orders: " << player.orders.size() << "\nTerritories: " << s << endl;
}