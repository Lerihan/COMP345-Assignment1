//  Player.cpp
//  
//  COMP 345
//  Assignment
//  Due Date: November 18, 2020
//  Created by Michael Totarella on 2020-09-23.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Player.h"
#include "Order.h"
#include "Map.h"
#include "Cards.h"

//class Territory;

int Player::totalPlayers = 1; // start at 0 so playerNumber matches the index of the Player in the GameEngine

// Default constructor sets attributes to be empty vectors.
Player::Player()
{
	this->playerNumber = totalPlayers++;
	this->hand = new Hand();
	this->orders = new OrdersList();

	this->numOfArmies = 0;
	this->reinforcementPool = 0;

	vector<Territory*> terr;
	this->territories = terr; // create empty vector of Territories
}

// Copy constructor, creates deep copy of each attribute.
// Assume Cards, Order, Territory classes have correctly implemented assignment operators
Player::Player(Player& p)
{
	this->playerNumber = p.playerNumber;
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

void Player::setNumOfArmies(int n)
{
	numOfArmies = n;
}

int Player::getNumOfArmies()
{
	return numOfArmies;
}

int Player::getReinforcementPool()
{
	return reinforcementPool;
}

// Adds the input Territory pointer this Player's Territories vector.
void Player::addTerritory(Territory* t)
{
	this->territories.push_back(t);
	t->setOwner(this); // set the owner of the input Territory to be this Player
}

// Removes the input Territory from this Player's list of Territoriess
void Player::removeTerritory(Territory* toRemove)
{
	for (int i = 0; i < this->territories.size(); i++) // loop through each of the Player's Territories
	{
		if (this->territories[i] == toRemove) // remove the one that is the input Territory
			this->territories.erase(this->territories.begin() + i);
	}
}

// Adds the input number of armies to the Player's reinforcement pool
// used in game startup phase
void Player::addReinforcements(int toAdd)
{
	this->reinforcementPool += toAdd;
}

// Removes the input number of reinforcements from this Player's reinforcement pool
// used only for Delpoy()
void Player::removeReinforcements(int toRemove)
{
	this->reinforcementPool -= toRemove;
}

// take specific numOfArmies from pool, if numOfArmies>reinforcementPool, take what's left
int Player::takeArmiesFromReinforcement(int numOfArmies) {

	int taken = std::min(numOfArmies, reinforcementPool);

	reinforcementPool = std::max(0, (reinforcementPool - numOfArmies));

	return taken;
}

// Returns vector of Territories to attack.
// For now, returns a vector of pointers to two default, newly generated Territories.
vector<Territory*> Player::toAttack()
{
	vector<Territory*> attackList;
	for (int i = 0; i < this->territories.size(); i++) // loop through each of this Player's Territories
	{
		for (int j = 0; j < this->territories[i]->listOfAdjTerritories.size(); j++) // loop through each of the Territory's adjacent Territories
		{
			if (this->territories[i]->listOfAdjTerritories[j]->getOwner() != this // if that Territory does not belong to this Player, add it to list
				&& !Territory::containsTerritory(attackList, this->territories[i])) // and Territory is not already in toAttack vector
				attackList.push_back(this->territories[i]);
		}
	}
	return this->sortTerritoriesToAttack(attackList);
}


// Returns vector of Territories to defend.
// For now, returns a vector of pointers to two default, newly generated Territories.
vector<Territory*> Player::toDefend()
{
	this->sortTerritoriesToDefend(); // sort Territories by priority
	return this->territories; // return the sorted vector
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

// Removes the input number of armies from the Player's number of armies
void Player::removeArmies(int toRemove)
{
	this->numOfArmies -= toRemove;
	if (this->numOfArmies < 0) // if it goes below 0 set it back to 0
		this->numOfArmies = 0;
}

// Uses bubble sort to sort the Player's Territories in increasing order of number of armies
void Player::sortTerritoriesToDefend()
{
	Territory* temp = NULL;
	int i, j;
	for (i = 0; i < this->territories.size(); i++) {
		// Last i elements are already in place  
		for (j = 0; j < this->territories.size() - i - 1; j++) {
			if (this->territories[j]->numberOfArmies > this->territories[j + 1]->numberOfArmies)
			{
				temp = this->territories[j + 1];
				this->territories[j + 1] = this->territories[j];
				this->territories[j] = temp;
			}
		}
	}

	temp = NULL;
}

// Sort the input vector of Territories in increasing order of number of armies
// Uses bubble sort
vector<Territory*> Player::sortTerritoriesToAttack(vector<Territory*> toAttack)
{
	Territory* temp = NULL;
	int i, j;
	for (i = 0; i < toAttack.size(); i++) {
		// Last i elements are already in place  
		for (j = 0; j < toAttack.size() - i - 1; j++) {
			if (toAttack[j]->numberOfArmies > toAttack[j + 1]->numberOfArmies) {
				temp = toAttack[j + 1];
				toAttack[j + 1] = this->territories[j];
				toAttack[j] = temp;
			}
		}
	}

	temp = NULL;
	return toAttack;
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
	return strm << "Player: " << player.playerNumber << "\nCards: " << *(player.hand) << "\nTerritories: " << s;
}

// In stream operator, allows user to choose the Player's name.
istream & operator >> (istream& strm,  Player& player)
{
    cout << "Enter Player number: ";
    strm >> player.playerNumber;
    return strm;
}

// Equality operator for two Player objects.
// For now, considers two Players equal if they share the same name. Note this is not enforce
bool operator ==(const Player& p1, const Player& p2)
{
	return (p1.playerNumber == p2.playerNumber);
}

bool operator !=(const Player& p1, const Player& p2)
{
	return !(p1 == p2);
}
