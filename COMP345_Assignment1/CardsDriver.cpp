#include <iostream>
#include <string>
#include "Cards.h"



int main() {
	//create default cards
	Cards* cards = new Cards();
	//create default deck
	Deck* deck = new Deck();
	//create random player
	Player* player = new Player();
	//create empty hand
	std::vector<string> cardsInHand;
	//create player's hand
	Hand* hand = new Hand(player, cardsInHand);
	//draws a card and plays it immediately
	for (int i = 0; i < 5; i++){
		deck->draw(*player);
		Hand::play(cardsInHand.at(i),*deck, *player);
	}
}