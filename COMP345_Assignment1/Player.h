//  Player.h
//  
//  COMP 345
//  Assignment 2
//  Due Date: November 18, 2020
//  Created by Michael Totarella on 2020-09-23.
//

#pragma once

#include <iostream>
//#include <vector>
#include "Map.h"
#include "Cards.h"
#include "Order.h"

class Order;
class Cards;
class OrdersList;
class Hand;

class Player
{
private:
	//static int playerCount; // to keep count of number of players, also needed to initialize playerNumber member
	static int totalPlayers; // keep track of number of Players created, assign number to each Player
	int playerNumber; // number unique to each Player
	int numOfArmies; // armies that are placed on territories
	int reinforcementPool; // Player's reinforcement pool, where armies for Deploy orders are taken
	OrdersList* orders; // player's list of orders to be carried out
	Hand* hand; // player's hand of cards
	std::vector<Territory*> territories; // territories belonging to the player

	string name; // name of player


public:
	// constructors and destructors
	Player(); // default constructor
	Player(string name); // for now take string as name to differentiate players
	Player(Player& p); // copy constructor
	~Player(); // destructor

	// other methods
	void addTerritory(Territory* r); // add input Territory pointer to data member vector
	void removeTerritory(Territory* toRemove); // removes Territory from the Player's list of Territories
	void issueOrder(Order* o); // for now just adds default Deploy order
	vector<Territory*> toDefend(); // returns vector of arbitrary Territories
	vector<Territory*> toAttack(); // returns vector of arbitrary Territories
	void addArmies(int toAdd); // adds the input number of armies to the Player's reinforcement pool
	void removeArmies(int toRemove); // removes input number of armies from the Player's number of armies
	void addReinforcements(int toAdd); // adds input number of armies to reinforcement pool
	void removeReinforcements(int toRemove); // removes the input number of armies from the Player's reinforcement pool
	int takeArmiesFromReinforcement(int numOfArmies); // take specific numOfArmies from pool, if numOfArmies>reinforcementPool, take what's left
	void sortTerritoriesToDefend(); // sorts the Player's Territories by priority to defend
	vector<Territory*> sortTerritoriesToAttack(vector<Territory*> toAttack); // sorts enemy Territories adjacent to Player's by priority to attack

	// accessors and mutators
	void setHand(Hand* h); // sets input Hand to be that of this Player
	int getPlayerNumber();
	string getName();
	void setNumOfArmies(int n);
	int getNumOfArmies();
	int getReinforcementPool();
	vector<Territory*> getTerritories();
	OrdersList* getOrdersList(); // returns this Player's OrdersList member
	vector<Order*> getOrders(); // returns vector of Orders from the OrdersList member
	Hand* getHand(); // returns Hand of this Player

	// operators
	Player& operator =(const Player& player);
	friend ostream& operator <<(ostream &strm, Player &player);
	friend istream & operator >>(istream& strm,  Player& player);
	friend bool operator ==(const Player &p1, const Player &p2);
	friend bool operator !=(const Player &p1, const Player &p2);
};