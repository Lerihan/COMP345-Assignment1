#include <iostream>
#include <algorithm>
#include <string>
#include "Cards.h"
#include "Order.h"
using namespace std;


//CARDS
//default constructor
Cards::Cards() {
	const char *cardsAvailable[] = { "Bomb","Diplomacy","Blockade","Reinforcement","Airlift" };
}

//copy constructor
Cards::Cards(Cards& c) {
	for (int i = 0; i < (sizeof(c.cardsAvailable) / sizeof(c.cardsAvailable[0])) - 1; i++) {
		cardsAvailable[i] = c.cardsAvailable[i];
	}
}

Cards::Cards(char* newCards[5]) {
	for (int i = 0; i < (sizeof(newCards) / sizeof(newCards[0])) - 1; i++) {
		cardsAvailable[i] = newCards[i];
	}
}

//assignment constructor
Cards& Cards::operator = (const Cards& c) {
	return *this;
}

//stream insertion operators
ostream& operator << (ostream& out, const Cards& c) {
	return out;
}
istream& operator << (istream& in, const Cards& c) {
	return in;
}


//HAND
//default constructor
Hand::Hand() = default; 

//copy constructor
Hand::Hand(Hand& player) {
	this->player = player.player;
	for (int i = 0; i < (sizeof(player.cardsInHand) / sizeof(player.cardsInHand[0])) - 1; i++) {
		cardsInHand[i] = player.cardsInHand[i];
	}
}

Hand::Hand(Player* playerName, char* playersCard[5]){
	this->player = playerName;
	for (int i = 0; i < (sizeof(playersCard) / sizeof(playersCard[0])) - 1; i++) {
		cardsInHand[i] = playersCard[i];
	}
}

//assignment constructor
Hand& Hand::operator = (const Hand& h) {
	player = h.player;
	return *this;
}

//stream insertion operators
ostream& operator << (ostream& out, const Hand& h) {
	return out;
}
istream& operator << (istream& in, const Hand& h) {
	return in;
}

void Hand::play(char* cardToPlay, Deck& d, Hand& h) {
	int i;
	int sizeOfHand = (sizeof(h.cardsInHand) / sizeof(h.cardsInHand[0]));
	int sizeOfDeck = (sizeof(d.cardsInDeck) / sizeof(d.cardsInDeck[0]));
	char *bombCard = cardsAvailable[0];
	char* diplomacyCard = cardsAvailable[1];
	char* blockCard = cardsAvailable[2];
	char* reinforcementCard = cardsAvailable[3];
	char* airliftCard = cardsAvailable[4];
	//implement function for the cards played
	if (*cardToPlay == *bombCard){
		//Bomb
		//create new order in orderlist
		//create new bomb order
		Bomb* bombCard;
		OrdersList::add(bombCard);
		cout << "Player used bomb card; created a new order list." << endl;
		//searching for the card in the player's hand.
		for (i = 0; i < sizeOfHand - 1; i++) {
			char* cardSelection = h.cardsInHand[i];
			if (*cardSelection == *cardToPlay)
				break;
		}
		//removing the card from the player's hand.
		if (i < sizeOfHand) {
			sizeOfHand = sizeOfHand - 1;
			for (int j = i; j < sizeOfHand; j++) {
				h.cardsInHand[j] = h.cardsInHand[j + 1];
			}
			//adding the card into the deck
			d.cardsInDeck[sizeOfDeck - 1] = h.cardsInHand[i];
		}
	}
	else if (*cardToPlay == *bombCard) {
		//Diplomacy
		Negotiate* negotiateCard;
		OrdersList::add(negotiateCard);
		cout << "Player used Diplomacy/Negotiate card; created a new order list." << endl;
		//searching for the card in the player's hand.
		for (i = 0; i < sizeOfHand - 1; i++) {
			char* cardSelection = h.cardsInHand[i];
			if (*cardSelection == *cardToPlay)
				break;
		}
		//removing the card from the player's hand.
		if (i < sizeOfHand) {
			sizeOfHand = sizeOfHand - 1;
			for (int j = i; j < sizeOfHand; j++) {
				h.cardsInHand[j] = h.cardsInHand[j + 1];
			}
			//adding the card into the deck
			d.cardsInDeck[sizeOfDeck - 1] = h.cardsInHand[i];
		}
	}
	else if (*cardToPlay == *blockCard) {
		//Blockade
		Blockade* blockCard;
		OrdersList::add(blockCard);
		cout << "Player used Blockade card; created a new order list." << endl;
		//searching for the card in the player's hand.
		for (i = 0; i < sizeOfHand - 1; i++) {
			char* cardSelection = h.cardsInHand[i];
			if (*cardSelection == *cardToPlay)
				break;
		}
		//removing the card from the player's hand.
		if (i < sizeOfHand) {
			sizeOfHand = sizeOfHand - 1;
			for (int j = i; j < sizeOfHand; j++) {
				h.cardsInHand[j] = h.cardsInHand[j + 1];
			}
			//adding the card into the deck
			d.cardsInDeck[sizeOfDeck - 1] = h.cardsInHand[i];
		}
	}
	else if (*cardToPlay == *reinforcementCard) {
		//Reinforcement
		Deploy* reinforcementCard;
		OrdersList::add(reinforcementCard);
		cout << "Player used Reinforcement card; created a new order list." << endl;
		//searching for the card in the player's hand.
		for (i = 0; i < sizeOfHand - 1; i++) {
			char* cardSelection = h.cardsInHand[i];
			if (*cardSelection == *cardToPlay)
				break;
		}
		//removing the card from the player's hand.
		if (i < sizeOfHand) {
			sizeOfHand = sizeOfHand - 1;
			for (int j = i; j < sizeOfHand; j++) {
				h.cardsInHand[j] = h.cardsInHand[j + 1];
			}
			//adding the card into the deck
			d.cardsInDeck[sizeOfDeck - 1] = h.cardsInHand[i];
		}
	}
	else if (*cardToPlay == *airliftCard) {
		//Airlift
		Airlift* airliftCard;
		OrdersList::add(airliftCard);
		cout << "Player used Airlift card; created a new order list." << endl;
		//searching for the card in the player's hand.
		for (i = 0; i < sizeOfHand - 1; i++) {
			char* cardSelection = h.cardsInHand[i];
			if (*cardSelection == *cardToPlay)
				break;
		}
		//removing the card from the player's hand.
		if (i < sizeOfHand) {
			sizeOfHand = sizeOfHand - 1;
			for (int j = i; j < sizeOfHand; j++) {
				h.cardsInHand[j] = h.cardsInHand[j + 1];
			}
			//adding the card into the deck
			d.cardsInDeck[sizeOfDeck - 1] = h.cardsInHand[i];
		}
	}
	cout << "Player has played " << *cardToPlay << "from their hand.\n" << *cardToPlay << " has been added to the deck." << endl;
}
	


//DECK
//default constructor
Deck::Deck(){	
	//a default deck will have 11 of every card type (5), to make a deck of 55
	for (int i = 0; i < (sizeof(cardsInDeck) / sizeof(cardsInDeck[0])); i++) {
		if (i < 11) 
			cardsInDeck[i] = cardsAvailable[0];
		else if (i < 22) 
			cardsInDeck[i] = cardsAvailable[1];
		else if (i < 33) 
			cardsInDeck[i] = cardsAvailable[2];
		else if (i < 44) 
			cardsInDeck[i] = cardsAvailable[3];
		else if (i < 55) 
			cardsInDeck[i] = cardsAvailable[4];
	}
	random_shuffle(&cardsInDeck[0], &cardsInDeck[55]);
	//cout << cardsInDeck[i] << " ";
}

//copy constructor
Deck::Deck(Deck& deck) {
	for (int i = 0; i < (sizeof(deck.cardsInDeck) / sizeof(deck.cardsInDeck[0])) - 1; i++) {
		cardsInDeck[i] = deck.cardsInDeck[i];
	}
}

Deck::Deck(char* newCardsInDeck[52]) {
	for (int i = 0; i < (sizeof(newCardsInDeck) / sizeof(newCardsInDeck[0])) - 1; i++) {
		cardsInDeck[i] = newCardsInDeck[i];
	}
}

//assignment constructor
Deck& Deck::operator = (const Deck& d) {
	cout << "Assignment operator called" << endl;
	return *this;
}

//stream insertion operators
ostream& operator << (ostream& out, const Deck& d) {
	return out;
}
istream& operator << (istream& in, const Deck& d) {
	return in;
}

void  Deck::draw(Deck& d, Hand& h) {	
	//finds the randomCard to be drawn
	int i;
	int sizeOfDeck = (sizeof(d.cardsInDeck) / sizeof(d.cardsInDeck[0]));
	int sizeOfHand = (sizeof(h.cardsInHand) / sizeof(h.cardsInHand[0]));
	int randomCard = rand() % sizeOfDeck + 0; //random number from 0 to size of current deck;
	for (i = 0; i < sizeOfDeck - 1; i++) {
		if (d.cardsInDeck[i] == d.cardsInDeck[randomCard])
			break;
	}
	//want to add the randomCard into the Hand, only if the hand has space. otherwise, remove random card from hand to add new one
	if (sizeOfHand == 5) {
		int x;
		int randomCardToRemove = rand() % sizeOfHand + 0;
		for (x = 0; x < sizeOfHand - 1; x++) {
			if (h.cardsInHand[x] == h.cardsInHand[randomCardToRemove])
			break;
		}
		if (x < sizeOfHand) {
			sizeOfHand = sizeOfHand - 1;
			for (int y = x; y < sizeOfHand; y++) {
				h.cardsInHand[y] = h.cardsInHand[y + 1];
			}			
		}
		h.cardsInHand[sizeOfHand] = d.cardsInDeck[randomCard];
		sizeOfHand++;
	}
	else {
		h.cardsInHand[sizeOfHand] = d.cardsInDeck[randomCard];
		sizeOfHand++;
	}
	//Removes the randomCard from the deck & reduces the deck's size
	if (i < sizeOfDeck) {
		sizeOfDeck = sizeOfDeck - 1;
		for (int j = i; j < sizeOfDeck; j++){
			d.cardsInDeck[j] = d.cardsInDeck[j + 1];
		}
	}
	cout << "Player has added a card into their hand" << endl;
}