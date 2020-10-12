//  Player.cpp
//  
//  COMP 345
//  Assignment 1, Part 3
//  Due Date: October 12, 2020
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

// Default constructor sets attributes to be empty vectors.
Player::Player()
{
	this->name = "NoName";
	this->hand = new Hand();
	this->orders = new OrdersList();

	vector<Territory*> terr;
	this->territories = terr; // create empty vector of Territories
}

// Constructor assigns input string to be Player name
Player::Player(string name)
{
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
	// copy orders
	this->orders = p.orders; // assumes OrdersList = operator is correctly implemented

	// copy territories
	this->territories = p.territories; // assumes Territory = operator is correctly implemented

	/*
	// copy territories
	for (int i = 0; i < p.territories.size(); i++)
	{
		this->territories.push_back(p.territories.at(i));
	}
	*/

	this->name = p.name;
	this->hand = p.hand; // assumes Hand class assignment operator is correctly implemented

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

// Returns the Hand object of this Player
Hand* Player::getHand()
{
	return this->hand;
}

// Returns the OrdersList of this Player
OrdersList* Player::getOrders()
{
	return this->orders;
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
// for now just adds a default Deploy order
void Player::issueOrder()
{
	//Deploy* d = new Deploy();
	Negotiate* d = new Negotiate(); // this is the only one that does not throw a segmentation fault
	//Bomb* d = new Bomb();
	//Advance* d = new Advance();
	//Blockade* d = new Blockade();
	//Airlift* d = new Airlift();
	this->orders->add(d);
	//d.setPlayer(this);
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

bool operator ==(const Player& p1, const Player& p2)
{
	return (p1.name == p2.name);
}

bool operator !=(const Player& p1, const Player& p2)
{
	return !(p1 == p2);
}