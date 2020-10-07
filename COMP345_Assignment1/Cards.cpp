#include <iostream>
#include "Cards.h"
using namespace std;


//CARDS
//default constructor
Cards::Cards() {
	const char* cardsAvailable[] = { "Bomb","Diplomacy","Blockade","Reinforcement","Airlift" };
}

//copy constructor
Cards::Cards(Cards& c) {
	for (int i = 0; i < (sizeof(c.cardsAvailable) / sizeof(c.cardsAvailable[0])) - 1; i++) {
		cardsAvailable[i] = c.cardsAvailable[i];
		cout << cardsAvailable[i] << " ";
	}
}

//assignment constructor
Cards::Cards(char* newCards[5]) {
	for (int i = 0; i < (sizeof(newCards) / sizeof(newCards[0])) - 1; i++) {
		cardsAvailable[i] = newCards[i];
		cout << cardsAvailable[i] << " ";
	}
}


//HAND
//default constructor
Hand::Hand() = default;

//copy constructor
Hand::Hand(Hand& player) {
	this->player = player.player;
	for (int i = 0; i < (sizeof(player.cardsInHand) / sizeof(player.cardsInHand[0])) - 1; i++) {
		cardsInHand[i] = player.cardsInHand[i];
		cout << cardsInHand[i] << " ";
	}
}

//assignment constructor
Hand::Hand(Player* playerName, char* playersCard[5]) {
	this->player = playerName;
	for (int i = 0; i < (sizeof(playersCard) / sizeof(playersCard[0])) - 1; i++) {
		cardsInHand[i] = playersCard[i];
		cout << cardsInHand[i] << " ";
	}
}

void Hand::play(Hand& h, Deck& d) {

}


//DECK
//default constructor
Deck::Deck() {
	for (int i = 0; i < (sizeof(cardsInDeck) / sizeof(cardsInDeck[0])); i++) {
		int randomNumber = rand() % 4 + 0;
		cardsInDeck[i] = cardsAvailable[randomNumber];
		cout << cardsInDeck[i] << " ";
	}
}

//copy constructor
Deck::Deck(Deck& deck) {
	for (int i = 0; i < (sizeof(deck.cardsInDeck) / sizeof(deck.cardsInDeck[0])) - 1; i++) {
		cardsInDeck[i] = deck.cardsInDeck[i];
		cout << cardsInDeck[i] << " ";
	}
}

//assignment constructor
Deck::Deck(char* newCardsInDeck[52]) {
	for (int i = 0; i < (sizeof(newCardsInDeck) / sizeof(newCardsInDeck[0])) - 1; i++) {
		cardsInDeck[i] = newCardsInDeck[i];
		cout << cardsInDeck[i] << " ";
	}
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
		for (int j = i; j < sizeOfDeck; j++) {
			d.cardsInDeck[j] = d.cardsInDeck[j + 1];
		}
	}
}