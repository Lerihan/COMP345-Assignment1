//COMP 345
//Assignment 1, part 5
//Due Date: October 9th, 2020
//

#pragma once

#include <iostream>
#include <string>
#include "Player.h"
#include "Order.h"

using namespace std;


class Player;

class Deck;

class Cards {	
protected:
	static char *cardsAvailable[5];
public:
	Cards();
	Cards(Cards& c);
	Cards(char* newCards[5]);
	//we are using 5 different types of cards
	Cards& operator = (const Cards &c);
	friend ostream& operator << (ostream& out, const Cards& c);
	friend istream& operator << (istream& in, const Cards& c);
};

class Hand : public Cards{
friend class Deck;
protected:
	Player* player;
	char*cardsInHand[5];
	//a standard game of risk, which is what warzone is based of off, has 5 cards in the hand
public:
	Hand();
	Hand(Hand& player);
	Hand(Player* player, char* cardsInHand[5]);
	Hand& operator = (const Hand &h);
	friend ostream& operator << (ostream& out, const Hand& h);
	friend istream& operator << (istream& in, const Hand& h);
	static void play(char* cardToPlay, Deck& d, Hand& h);
};

class Deck : public Cards{
friend class Hand;
protected:
	char* cardsInDeck[55];
	//a standard game of risk, which is what warzone is based of off, has 55 cards in the deck
public:
	Deck();
	Deck(Deck& d);
	Deck(char* cardsInDeck[55]);
	Deck& operator = (const Deck &d);
	friend ostream& operator << (ostream& out, const Deck& d);
	friend istream& operator << (istream& in, const Deck& d);
	static void draw(Deck& d, Hand& h);
};