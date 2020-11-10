#include <iostream>
#include <string>
#include "Cards.h"



int main() {
	//create default deck
	Deck* deck = new Deck();
	cout << "Creation of the default Deck: " << endl << endl;
	for (int i = 0; i < deck->cardsInDeck.size(); i++) {
		cout << deck->cardsInDeck.at(i) << " ";
		if (i == 22)		//line seperation in the output for clarity
			cout << endl;
	}
	cout << endl << endl;
	//create another deck to showcase randomized deck creation
	cout << "Second Deck created, to demonstrate the random deck creation" << endl << endl;
	Deck* deck2 = new Deck();
	for (int i = 0; i < deck2->cardsInDeck.size(); i++) {
		cout << deck2->cardsInDeck.at(i) << " ";
		if (i == 22)		//line seperation in the output for clarity
			cout << endl;
	}
	cout << endl << endl;
	//create random player
	Player* player = new Player();
	//create empty hand
	Hand *h = player->getHand();
	//player's hand is currently empty, show player's hand
	cout << "Player's Hand:" << endl;
	for (int i = 0; i < h->cardsInHand.size(); i++) {
		cout << h->cardsInHand.at(i) << " " << endl;
	}
	cout << endl << h->getCardsInHand().size() << endl << endl;

	//draws a card and plays it immediately
	for (int i = 0; i < 5; i++) {
		deck->draw(player);
	}

	cout << endl << "Player's Hand:" << endl;
	for (int i = 0; i < h->cardsInHand.size(); i++) {
		cout << h->cardsInHand.at(i) << " " << endl;
	}
	cout << endl << h->getCardsInHand().size() << endl << endl;

	while (h->getCardsInHand().size() > 0)
	{		
		h->cardsInHand.at(i)->play(deck);
		//show size of deck differences & player's hand
		cout << "Current size of deck " << deck->cardsInDeck.size() << endl;
		cout << "Current cards in hand: " << endl;
		for (int i = 0; i < h->cardsInHand.size(); i++) {
			cout << h->cardsInHand.at(i) << " " << endl;
		}
		cout << "Player's current Orderlist: " << endl << *player->getOrdersList() << endl;
		cout << endl;
	}
}