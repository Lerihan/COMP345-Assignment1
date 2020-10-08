//  Player.h
//  
//  COMP 345
//  Assignment 1, Part 3
//  Due Date: October 9, 2020
//  Created by Michael Totarella on 2020-09-23.
//

#pragma once

#include <iostream>
#include <vector>
#include "Map.h"
#include "Cards.h"
#include "Order.h"

class Order;
class Cards;

class Player
/*
Leaving input parameter of issueOrder() to be string of specific Order type for now. This should be changed to accept
an actual order object I think, but Order class is abstract. I imagine this temporary method definition will become a problem
depending on how the final game is implemented.

Also, issueOrder() will need different parameters depending on the order type. This will also have to be solved later. For now 
I am giving all default parameters.

Copy constructor and = assignment operator assumes all other class assignment operators are correctly implemented.
*/

{
private:
	//static int playerCount; // to keep count of number of players, also needed to initialize playerNumber member
	int playerNumber; // assign each player a number to keep track of which player is playing
	std::vector<Order*> orders; // player's list of orders to be carried out
	std::vector<Cards*> hand; // player's hand of cards
	std::vector<Territory*> territories; // territories belonging to the player

	string name; // name of player

public:
	Player(); // default constructor
	Player(string name); // for now take string as name to differentiate players
	Player(Player& p); // copy constructor
	~Player(); // destructor
	vector<Territory*> getTerritories();
	void addTerritory(Territory* r); // add input Territory pointer to data member vector
	Order* getNextOrder(); // returns next order to be executed (first order in attribute vector)
	void issueOrder(); // for now just adds default Deploy order
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();

	Player& operator =(const Player& player);
	friend ostream& operator <<(ostream &strm, Player &player);
};