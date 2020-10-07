//COMP 345
//Assignment 1, part 5
//Due Date: October 9th, 2020
//

#pragma once

#include <iostream>
#include <string>
using namespace std;


class Player;

class Cards {
protected:
	char *cardsAvailable[5];
public:
	Cards();
	Cards(Cards& c);
	Cards(char* newCards[5]);
	//must be able to change array size somehow
};

class Hand : public Cards {
	friend class Deck;
protected:
	Player* player;
	string cardsInHand[5];
	//must be able to change array size somehowpublic:
public:
	Hand();
	Hand(Hand& player);
	Hand(Player* player, char* cardsInHand[5]);
	void play(Hand& h, Deck& d);
};

class Deck : public Cards {
	friend class Hand;
protected:
	char* cardsInDeck[52];
	//must be able to change array size somehow
public:
	Deck();
	Deck(Deck& d);
	Deck(char* cardsInDeck[52]);
	void draw(Deck& d, Hand& h);
};