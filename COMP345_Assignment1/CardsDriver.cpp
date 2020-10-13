#include <iostream>
#include <string>
#include "Cards.h"



int main() {
	//create default cards
	Cards* cards;
	//create default deck
	Deck* deck = new Deck();
	cout << "Creation of the default Deck: " << endl;
	for (int i = 0; i < deck->cardsInDeck.size(); i++) {
		cout << deck->cardsInDeck.at(i) << " ";
		if (i == 22)		//line seperation in the output for clarity
			cout << endl;
	}
	//create another deck to showcase randomized deck creation
	cout << "Second Deck created, to demonstrate the random deck creation" << endl;
	Deck* deck2 = new Deck();
	for (int i = 0; i < deck2->cardsInDeck.size(); i++) {
		cout << deck2->cardsInDeck.at(i) << " ";
		if (i == 22)		//line seperation in the output for clarity
			cout << endl;
	}
	//create random player
	Player* player = new Player();
	//create empty hand
	Hand *h = player->getHand();
	//player's hand is currently empty, show player's hand
	cout << "Player's Hand:" << endl;
	for (int i = 0; i < h->cardsInHand.size(); i++) {
		cout << h->cardsInHand.at(i) << " " << endl;
	}
	//draws a card and plays it immediately
	for (int i = 0; i < 5; i++) {
		deck->draw(*player);
<<<<<<< Updated upstream
	}

	cout << cardsInHand.size() << endl;

	for (int i = 0; i < cardsInHand.size(); i++){
		//deck->draw(*player);
		hand->play(cardsInHand.at(i),*deck, *player);
=======
		//show size of deck differences & player's hand
		cout << "Current size of deck " << deck->cardsInDeck.size() << endl
			 << "Current cards in hand " << endl << h->cardsInHand.at(i) << endl;
	}
	const int sizeOfHand = h->cardsInHand.size();
	for (int i = 0; i < sizeOfHand; i++) {
		h->play(h->cardsInHand.back(), *deck, *player);
		//show size of deck differences & player's hand & player's orderlist
		cout << "Current size of deck " << deck->cardsInDeck.size() << endl
			<< "Current cards in hand " << endl << h->cardsInHand.at(i) << endl
			<< "Player's current Orderlist: " << endl << player->getOrdersList() << endl;
>>>>>>> Stashed changes
	}
}