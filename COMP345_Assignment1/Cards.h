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

// needed Order subclasses
//class Airlift;
//class Bomb;
//class Blockade;
//class Negotiate;

class Deck;

class Card {	
	public:
		Player* cardHolder;
		Deck* d;

		Card();
		virtual ~Card();

		virtual void play() = 0;
		virtual string getType() = 0;

		Card& operator = (const Card& c);
		//friend ostream& operator << (ostream& out, const Card& c);
		friend istream& operator >> (istream& in, const Card& c);
};

class BombCard : public Card {
	private:
		Territory* target; // target that gets bombed
	public:
		BombCard();
		BombCard(Territory* target);
		~BombCard();

		void play();
		string getType();

		void setTarget(Territory* target);
		Territory* getTarget();
		friend ostream& operator << (ostream& out, const BombCard& c);

};

class ReinforcementCard : public Card {
	private:
		int numArmies; // number of armies to add to Player

	public:
		ReinforcementCard();
		ReinforcementCard(int numArmies);
		~ReinforcementCard();

		void play();
		string getType();

		void setNumArmies(int numArmies);
		int getNumArmies();
		friend ostream& operator << (ostream& out, const ReinforcementCard& c);
};

class BlockadeCard : public Card {
private:
	Territory* target;

public:
	BlockadeCard();
	BlockadeCard(Territory* targe);
	~BlockadeCard();

	void play();
	string getType();

	void setTarget(Territory* target);
	Territory* getTarget();
	friend ostream& operator << (ostream& out, const BlockadeCard& c);
};

class AirliftCard : public Card {
private:
	Territory* current;
	Territory* target;
	int numArmies;

public:
	AirliftCard();
	AirliftCard(Territory* current, Territory* target, int numArmies);
	~AirliftCard();

	void play();
	string getType();

	void setCurrent(Territory* current);
	Territory* getCurrent();
	void setTarget(Territory* target);
	Territory* getTarget();
	void setNumArmies();
	int getNumArmies(int numArmies);
	friend ostream& operator << (ostream& out, const AirliftCard& c);
};

class DiplomacyCard : public Card {
private:
	Player* enemy;

public:
	DiplomacyCard();
	DiplomacyCard(Player* enemy);
	~DiplomacyCard();

	void play();
	string getType();

	void setEnemy(Player* enemy);
	Player* getEnemy();
	friend ostream& operator << (ostream& out, const DiplomacyCard& c);
};

class Hand {
friend class Deck;
protected:
	Player* player;	
public:
	std::vector<Card*> cardsInHand;
	Hand();
	Hand(Hand& player);
	Hand(Player* playerName, std::vector<Card*> playersCards);
	~Hand();
	Hand& operator = (const Hand &h);
	std::vector<Card*> getCardsInHand();
	void play();
	friend ostream& operator << (ostream& out, const Hand& h);
	friend istream& operator >> (istream& in, const Hand& h);
};

class Deck{
protected:
public:
	std::vector<Card*> cardsInDeck;
	Deck();
	Deck(Deck& d);
	Deck(std::vector<Card*> cardsInDeck);
	~Deck();
	Deck& operator = (const Deck &d);
	friend ostream& operator << (ostream& out, const Deck& d);
	friend istream& operator >> (istream& in, const Deck& d);
	void draw(Player* p);
	void insertBackToDeck(Card* c);
};