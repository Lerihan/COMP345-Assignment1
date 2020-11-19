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
	this->eliminated = false;

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
	this->eliminated = p.eliminated;

	/*
	// copy territories
	for (int i = 0; i < p.territories.size(); i++)
	{
		this->territories.push_back(p.territories.at(i));
	}
	*/


}

// Destructor deletes thiss Player object.
// Note that this depends on the destructors of the Player's data members. The Player destructor is not responsible for deleting the 
// data members of ITS data members.
// this will NOT delete the Territories of the Player (just the vector that stores the pointers)
// it will delete their Orders and OrdersList
// also when this destructor is called it is assumed that the Player lost the game and their Cards have already been put back in the Deck,
// so we can simply delete the Hand
Player::~Player()
{
	// if the Player is not eliminated when the game is over their Hand has not already been cleared
	if (!this->eliminated)
	{
		// clear the Player's Hand
		Hand* hand = this->getHand(); // for readability
		for (int i = 0; i < this->hand->getCardsInHand().size(); i++)
		{
			delete hand->getCardsInHand()[i];
			hand->getCardsInHand()[i] = NULL;
		}
		hand->getCardsInHand().clear(); // Player's Hand size is now 0
		hand = NULL;

		delete this->hand; // delete Player's Hand pointer
	}

	for (int i = 0; i < this->territories.size(); i++)
	{
		//delete this->territories[i]; // delete pointer for each Territory
		this->territories[i] = NULL; // avoid dangling pointers
	}
	this->territories.clear(); // remove placeholder memory locations

	delete this->orders; // delete to OrdersList
}

// Returns vector of Territories.
// Should return a new vector of pointers to the same Territory objects
vector<Territory*> Player::getTerritories()
{
	vector<Territory*> t = this->territories;
	
	return t;
}

// Set the input vector to be this Player's list of Territories.
// used in driver part 3 only
void Player::setTerritories(vector<Territory*> t)
{
	this->territories = t;
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
			toRemove->setOwner(NULL); // this should be changed to a new Player when it is reassigned
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

	this->reinforcementPool = std::max(0, (reinforcementPool - numOfArmies));

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
			if ((this->territories[i]->listOfAdjTerritories[j]->getOwner() != this) // if that Territory does not belong to this Player, add it to list
				&& !(this->territories[i]->listOfAdjTerritories[j]->containsTerritory(attackList)))  // and Territory is not already in toAttack vector
			{
				attackList.push_back(this->territories[i]->listOfAdjTerritories[j]);
			}
		}
	}
	if (attackList.size() == 0)
		return attackList;
	this->sortTerritoriesToAttack(attackList);
	return attackList;
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
void Player::sortTerritoriesToAttack(vector<Territory*> toAttack)
{
	sort(toAttack.begin(), toAttack.end(), compareByNumArmies);
}

// Returns whether this Player is eliminated or not.
bool Player::isEliminated()
{
	return this->eliminated;
}

// Sets this Player's eliminated data member to true.
void Player::eliminatePlayer()
{
	this->eliminated = true;
}

// Resets the total number of Players to 0.
// needed if creating 2 GameEngines in one mian()
// used for part 3 driver only
void Player::resetTotalPlayers()
{
	this->totalPlayers = 1;
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

	string o = "";
	for (int i = 0; i < player.getOrders().size(); i++)
	{
		if (!player.getOrders().at(i)->isExecuted())
		{
			o += player.getOrders().at(i)->getType();
			o += ", ";
		}
	}
	o += "\b\b.";

	return strm << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl
		<< "Player: " << player.playerNumber 
		<< "\nCards: " << *(player.hand)
		<< "Territories: " << s 
		<< "\nReinforcement pool: " << player.reinforcementPool 
		<< "\nOrders: " << o << endl
		<< "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl;
}

/*
// In stream operator, allows user to choose the Player's name.
istream & operator >> (istream& strm,  Player& player)
{
    cout << "Enter Player number: ";
    strm >> player.playerNumber;
    return strm;
}
*/

// Equality operator for two Player objects.
// For now, considers two Players equal if they share the same number
// this should only be true if the Player's copy constructor was used
bool operator ==(const Player& p1, const Player& p2)
{
	return (p1.playerNumber == p2.playerNumber);
}

bool operator !=(const Player& p1, const Player& p2)
{
	return !(p1 == p2);
}

// Compares the two input Territories according to their number of armies.
// returns true if t1 has more armies, returns false otherwise
// used in sorting methods for toAttack() and toDefend()
bool compareByNumArmies(Territory* t1, Territory* t2)
{
	return (t1->numberOfArmies > t2->numberOfArmies);
}