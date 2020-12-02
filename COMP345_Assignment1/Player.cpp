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
	this->hand = new Hand(this);
	this->orders = new OrdersList();

	this->numOfArmies = 0;
	this->reinforcementPool = 0;
	this->eliminated = false;
	this->wonAttack = false;

	vector<Territory*> terr;
	this->territories = terr; // create empty vector of Territories
}

Player::Player(string strategy) : Player()
{
	if (strategy == "aggressive")
		this->strategy = new AggressivePlayerStrategy();
	else if (strategy == "human")
		this->strategy = new HumanPlayerStrategy();
	else if (strategy == "benevolent")
		this->strategy = new BenevolentPlayerStrategy();
	else if (strategy == "neutral")
		this->strategy = new NeutralPlayerStrategy();
}

// Copy constructor, creates shallow copy of each attribute.
// Assume Cards, Order, Territory classes have correctly implemented assignment operators
Player::Player(Player& p)
{
	this->playerNumber = p.playerNumber;
	this->hand = p.hand;
	this->orders = p.orders;
	this->territories = p.territories;
	this->numOfArmies = p.numOfArmies;
	this->eliminated = p.eliminated;
	this->wonAttack = p.wonAttack;
	this->reinforcementPool = p.reinforcementPool;
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
			hand->getCardsInHand()[i] = nullptr;
		}
		hand->getCardsInHand().clear(); // Player's Hand size is now 0
		hand = nullptr;

		delete this->hand; // delete Player's Hand pointer
	}

	for (int i = 0; i < this->territories.size(); i++)
	{
		//delete this->territories[i]; // delete pointer for each Territory
		this->territories[i] = nullptr; // avoid dangling pointers
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

Card * Player::getCard(string type)
{
	for (int i = 0; i < this->hand->cardsInHand.size(); i++)
	{
		if (this->hand->getCardsInHand().at(i)->getType() == type)
		{
			return this->hand->getCardsInHand().at(i);
		}
	}
	return NULL;
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

void Player::setStrategy(PlayerStrategy* strategy)
{
	this->strategy = strategy;
}

bool Player::hasNegotiationWith(Player * enemy)
{
	for (int i = 0; i < orders->getOrdersList().size(); i++)
	{
		if (orders->getOrdersList().at(i)->getPlayer()->playerNumber == enemy->playerNumber && this != enemy)
			return true;
	}
	return false;
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
			toRemove->setOwner(nullptr); // this should be changed to a new Player when it is reassigned
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

// Adds argument Order to the Player's Order vector attribute. Calls issueOrder method of Player's strategy class.
void Player::issueOrder()
{
	this->strategy->issueOrder(this);
}

// Creates a list of all enemy Territories adjacent to all of this Player's Territories and passes it to its
// PlayerStrategy subclass toDefend method.
vector<Territory*> Player::toAttack()
{
	vector<Territory*> attack;
	Territory* t = nullptr; // for readability
	for (int i = 0; i < this->territories.size(); i++) // for each of this Player's Territories
	{
		t = this->territories.at(i);
		for (int j = 0; j < t->listOfAdjTerritories.size(); j++) // for each of that Territories asjacent Territories
		{
			if (t->listOfAdjTerritories.at(j)->getOwner() != this) // if this Player does not own that Territory
			{
				if (!(t->listOfAdjTerritories.at(j)->containsTerritory(attack))) // if Territory is not alredy in list
				{
					attack.push_back(t->listOfAdjTerritories.at(j));
				}
			}
		}
	}

	return this->strategy->toAttack(attack);
}

// Creates a list of all this Player's Territories as a list of Territrories to defend and passes it to its
// PlayerStrategy subclass toDefend method.
vector<Territory*> Player::toDefend()
{
	vector<Territory*> defend;
	for (int i = 0; i < this->territories.size(); i++)
	{
		defend.push_back(this->territories.at(i));
	}

	return this->strategy->toDefend(defend);
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

bool Player::hasWonAttack() {
	return this->wonAttack;
}

void Player::setWonAttack(bool b) {
	this->wonAttack = b;
}

// Resets the total number of Players to 0.
// needed if creating 2 GameEngines in one mian()
// used for part 3 driver only
void Player::resetTotalPlayers()
{
	this->totalPlayers = 1;
}

// Assignment operator, performs shallow copy only.
// Assume Cards, Order, Territory classes have correctly implemented assignment operators
Player& Player::operator =(const Player& player)
{
	if (&player != this)
	{
		// assign new values
		this->hand = player.hand;
		this->territories = player.territories;
		this->hand = player.hand;
		this->orders = player.orders;
		this->playerNumber = player.playerNumber;
		this->numOfArmies = player.numOfArmies;
		this->reinforcementPool = player.reinforcementPool;
		this->eliminated = player.eliminated;
		this->wonAttack = player.wonAttack;
	}

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