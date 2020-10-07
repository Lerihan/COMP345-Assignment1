////
////  Player.hpp
////  
////  COMP 345
////  Assignment 1, Part 3
////  Due Date: October 9, 2020
////  Created by Michael Totarella on 2020-09-23.
////
//
//#pragma once
//
//#include <stdio.h>
//#include <list>
//#include "Map.h"
//#include "Cards.h"
//#include "Order.h"
//
//
//class Player
//{
//private:
//	static int playerCount = 0; // to keep count of number of players, also needed to initialize playerNumber member
//	int playerNumber; // assign each player a number to keep track of which player is playing
//	std::vector<Order*> orders; // player's list of orders to be carried out
//	std::vector<Cards*> hand; // player's hand of cards
//	std::vector<Territory*> territories; // territories belonging to the player
//
//public:
//	Player(); // default constructor
//	Player(Player& p); // copy constructor
//	~Player(); // destructor
//	Order* getNextOrder(); // returns next order to be executed (first order in attribute vector)
//	void issueOrder(Order order);
//	Territory* toDefend();
//	Territory* toAttack();
//	Player& operator =(const Player& player);
//	friend ostream& operator <<(ostream &strm, Player &player);
//};
