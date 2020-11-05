//  Player.h
//  
//  COMP 345
//  Assignment 1, Part 3
//  Due Date: October 12, 2020
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
	static int playerNumber; // assign each player a number to keep track of which player is playing
	int numOfArmies;
	OrdersList* orders; // player's list of orders to be carried out
	Hand* hand; // player's hand of cards
	std::vector<Territory*> territories; // territories belonging to the player

	string name; // name of player


public:
	Player(); // default constructor
	Player(string name); // for now take string as name to differentiate players
	Player(Player& p); // copy constructor
	~Player(); // destructor
	vector<Territory*> getTerritories();
	void addTerritory(Territory* r); // add input Territory pointer to data member vector
	OrdersList* getOrdersList(); // returns this Player's OrdersList member
	vector<Order*> getOrders(); // returns vector of Orders from the OrdersList member
	Hand* getHand(); // returns Hand of this Player
	void issueOrder(); // for now just adds default Deploy order
	vector<Territory*> toDefend(); // returns vector of arbitrary Territories
	vector<Territory*> toAttack(); // returns vector of arbitrary Territories
	void setHand(Hand* h); // sets input Hand to be that of this Player

	int getPlayerNumber();
	string getName();
	void setArmyNumber(int n);
	int getArmyNumber();

	Player& operator =(const Player& player);
	friend ostream& operator <<(ostream &strm, Player &player);
	friend istream & operator >>(istream& strm,  Player& player);
	friend bool operator ==(const Player &p1, const Player &p2);
	friend bool operator !=(const Player &p1, const Player &p2);
};