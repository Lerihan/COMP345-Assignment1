//
//  Player.cpp
//  
//  COMP 345
//  Assignment 1, Part 3
//  Due Date: October 9, 2020
//  Created by Michael Totarella on 2020-09-23.
//

#pragma once

#include <iostream>
#include <vector>
#include "Player.h"
#include "Order.h"
#include "Map.h"
#include "Cards.h"

// Default constructor sets attributes to be empty vectors.
Player::Player()
{
	this->playerNumber = ++playerCount; // increment total number of players and assign a number to this Player
	//this->hand = std::vector<Cards*>;
	//this->orders = std::vector<Order*>;
	//this->territories = std::vector<Territory*>;
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

// Returns vector of Territories to attack.
// For now, returns a vector of pointers to two default, newly generated Territories.
vector<Territory*> Player::toAttack()
{
	Territory* attackTerritory1 = new Territory("Attack Territory 1");
	Territory* attackTerritory2 = new Territory("Attack Territory 2");

	vector<Territory*> attackList;
	attackList.push_back(attackTerritory1);
	attackList.push_back(attackTerritory2);

	return attackList;
}

// Returns vector of Territories to defend.
// For now, returns a vector of pointers to two default, newly generated Territories.
vector<Territory*> Player::toDefend()
{
	Territory* defendTerritory1 = new Territory("Attack Territory 1");
	Territory* defendTerritory2 = new Territory("Attack Territory 2");

	vector<Territory*> defendList;
	defendList.push_back(defendTerritory1);
	defendList.push_back(defendTerritory2);

	return defendList;
}

// Adds argument Order to the Player's Order vector attribute.
void Player::issueOrder(string orderType)
{
	//this->orders.push_back(); // add pointer to new order to end of order list
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
		s += player.territories.at(i).name;
		s += ", ";
	}
	s += "\b \b.";
	return strm << "Player " << player.playerNumber << "\nNext order: " << player.orders.at(0) << "\nTerritories: " << s << endl;
}
