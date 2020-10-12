#include <iostream>
#include <string>
#include "Cards.h"

using namespace std;


int main() {
	Cards* cards = new Cards();
	Deck* deck = new Deck();
	Player* player = new Player();
	char* cardsInHand[5];
	Hand* hand = new Hand(player, cardsInHand);
	for (int i = 0; i < 5; i++){
		Deck::draw(*deck, *hand);
		Hand::play(cardsInHand[i],*deck, *hand);
	}


}