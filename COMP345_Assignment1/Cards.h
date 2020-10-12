//COMP 345
//Assignment 1, part 5
//Due Date: October 9th, 2020
//

#pragma once

#include <iostream>
#include <string>
#include "Player.h"
#include "Order.h"

class Player;
class Deck;

class Cards {	
protected:
	static string cardsAvailable[5];
public:
	Cards();
	Cards(Cards& c);
	Cards(string newCards[5]);
	//we are using 5 different types of cards
	Cards& operator = (const Cards &c);
	friend ostream& operator << (ostream& out, const Cards& c);
	friend istream& operator << (istream& in, const Cards& c);
};

class Hand : public Cards{
friend class Deck;
protected:
	Player* player;
	std::vector<string> cardsInHand;
public:
	Hand();
	Hand(Hand& player);
	Hand(Player* playerName, std::vector<string> playersCards);
	Hand& operator = (const Hand &h);
	std::vector<string> getCardsInHand();
	friend ostream& operator << (ostream& out, const Hand& h);
	friend istream& operator << (istream& in, const Hand& h);
	static void play(string cardToPlay, Deck& d, Player& p);
};

class Deck : public Cards{
friend class Hand;
protected:
	std::vector<string> cardsInDeck;
public:
	Deck();
	Deck(Deck& d);
	Deck(std::vector<string> cardsInDeck);
	Deck& operator = (const Deck &d);
	friend ostream& operator << (ostream& out, const Deck& d);
	friend istream& operator << (istream& in, const Deck& d);
	void draw(Player& p);
};