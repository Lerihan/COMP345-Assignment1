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
#include "PlayerStrategies.h"

class Order;
class Card;
class OrdersList;
class Hand;
class PlayerStrategy;

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
	bool eliminated; // will store whether the Player has been eliminated from the game or not

	PlayerStrategy* strategy;

public:
	std::vector<Territory*> territories; // territories belonging to the player

	// constructors and destructors
	Player(); // default constructor
	Player(string strategy);
	Player(Player& p); // copy constructor
	~Player(); // destructor

	// other methods
	void addTerritory(Territory* r); // add input Territory pointer to data member vector
	void removeTerritory(Territory* toRemove); // removes Territory from the Player's list of Territories
	void issueOrder(); // calls issueOrder of the Player's strategy class
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
	void addArmies(int toAdd); // adds the input number of armies to the Player's reinforcement pool
	void removeArmies(int toRemove); // removes input number of armies from the Player's number of armies
	void addReinforcements(int toAdd); // adds input number of armies to reinforcement pool
	void removeReinforcements(int toRemove); // removes the input number of armies from the Player's reinforcement pool
	int takeArmiesFromReinforcement(int numOfArmies); // take specific numOfArmies from pool, if numOfArmies>reinforcementPool, take what's left
	bool isEliminated(); // return whether the Player is eliminated or not
	void eliminatePlayer(); // sets the Player's eliminated data member to true
	void resetTotalPlayers(); // needed to reset total number of players to 0; needed for part 3 driver

	// accessors and mutators
	void setHand(Hand* h); // sets input Hand to be that of this Player
	int getPlayerNumber();
	void setNumOfArmies(int n);
	int getNumOfArmies();
	int getReinforcementPool();
	vector<Territory*> getTerritories();
	void setTerritories(vector<Territory*> t); // sets the input vector to be the Player's territories; used in driver part 3
	OrdersList* getOrdersList(); // returns this Player's OrdersList member
	vector<Order*> getOrders(); // returns vector of Orders from the OrdersList member
	Hand* getHand(); // returns Hand of this Player
	Card* getCard(string type);
	void setStrategy(PlayerStrategy* strategy); // to change Player strategy during game

	// operators
	Player& operator =(const Player& player);
	friend ostream& operator <<(ostream &strm, Player &player);
	friend bool operator ==(const Player &p1, const Player &p2);
	friend bool operator !=(const Player &p1, const Player &p2);
};