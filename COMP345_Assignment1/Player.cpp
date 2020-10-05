//
//  Player.cpp
//  
//  COMP 345
//  Assignment 1, Part 3
//  Due Date: October 9, 2020
//  Created by Michael Totarella on 2020-09-23.
//

#include <iostream>
#include "Player.h"
#include "Order.h"
#include "Map.h"

// Default constructor sets attributes to be empty vectors.
Player::Player()
{
	this->playerNumber = ++playerCount; // increment total number of players and assign a number to this Player
	this->hand = std::vector<Cards*>;
	this->orders = std::vector<Order*>;
	this->territories = std::vector<Territory*>;
}

// Copy constructor, creates deep copy of each attribute.
// change deep copy method if other classes have assignment operator
Player::Player(Player& p)
{
	Player::Player(); // call default constructor to create empty attribute vectors

	// then populate them
	for (int i = 0; i < p.hand.size(); i++) {
		Card c = *p.hand.at(i);
		this.hand.push_back(new Card(*c));
	}

	for (int i = 0; i < p.orders.size(); i++) {
		Order o = *p.orders.at(i);
		this.orders.push_back(new Order(*o));
	}

	for (int i = 0; i < p.territories.size(); i++) {
		Territory t = *p.territories.at(i);
		this.territories.push_back(new Territory(*t));
	}
}

// Destructor deletes thiss Player object.
// idk if it should also delete all their cards and territories
Player::~Player()
{
	delete this;
}

// Returns vector of Territories to attack.
list<Territory*> Player::toAttack()
{
	return list<Territory*>;
}

// Returns vector of Territories to defend.
list<Territory*> Player::toDefend()
{
	return list<Territory*>;
}

// Adds argument Order to the Player's Order vector attribute.
void Player::issueOrder(Order order)
{
	this->orders.push_back(order); // add pointer to new order to end of order list
}

// = operator, performs deep copy.
// change deep copy method if other classes have assignment operator
Player::Player& operator =(const Player& player);
{
	// perform deep copy of each attribute, same as copy constructor
	for (int i = 0; i < p.hand.size(); i++) {
		Card c = *p.hand.at(i);
		this.hand.push_back(new Card(*c));
	}

	for (int i = 0; i < p.orders.size(); i++) {
		Order o = *p.orders.at(i);
		this.orders.push_back(new Order(*o));
	}

	for (int i = 0; i < p.territories.size(); i++) {
		Territory t = *p.territories.at(i);
		this.territories.push_back(new Territory(*t));
	}

	return *this;
}

// Out stream operator prints Player number, next Order, and occupied Territories.
ostream& operator <<(ostream &strm, Player &player)
{
	string s = "";
	// create list of Territory names to output to console
	for (Territory t : player.territories)
	{
		s += *t.name;
		s += ", ";
	}
	t += "\b \b.";
	return (strm << "Player " << player.playerNumber << "\nNext order: " << player.orders.at(0) << "\nTerritories: " << t << endl;
}


int main()
{
	return 0;
}
