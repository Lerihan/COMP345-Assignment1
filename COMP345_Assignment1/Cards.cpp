#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <time.h>
#include "Cards.h"
#include "Order.h"
using namespace std;

string Cards::cardsAvailable[5] = { "Bomb", "Diplomacy", "Blockade", "Reinforcement","Airlift" };

//CARDS
//default constructor
Cards::Cards() {
}

//copy constructor
Cards::Cards(const Cards& c) {
	int sizeOfNewArray = sizeof(c.cardsAvailable) / sizeof(*c.cardsAvailable);
	string *newCardsAvailable = new string[sizeOfNewArray];
	for (int i = 0; i < sizeOfNewArray; i++) {
		newCardsAvailable[i] = c.cardsAvailable[i];
	}
}

Cards::Cards(string newCards[5]) {
	//creates a new assortment of cards from a specific list
	for (int i = 0; i < (*(&cardsAvailable + 1) - cardsAvailable); i++) {
		cardsAvailable[i] = newCards[i];
	}
}

Cards::~Cards() {
	delete this;
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
Hand::Hand() {
}

//copy constructor
Hand::Hand(Hand& player) {
	//copies hand of a  player
	this->player = player.player;
	this->cardsInHand = player.cardsInHand;
}

Hand::Hand(Player* playerName, std::vector<string> playersCards) {
	//creates a new hand with a player and a set of cards
	this->player = playerName;
	this->player->setHand(this);
	//this->cardsInHand = playersCards;

	/*for (int i = 0; i < (playersCards).size() - 1; i++) {
		cardsInHand[i] = playersCards[i];
	}*/
	this->cardsInHand = playersCards;
}

Hand::~Hand() {
	delete this->player;
	delete this;
}

//assignment constructor
Hand& Hand::operator = (const Hand& h) {
	player = h.player;
	cardsInHand = h.cardsInHand;
	return *this;
}

//returns the cards in the player's hands.
vector<string> Hand::getCardsInHand() {
	vector<string> h;
	for (int i = 0; i < this->cardsInHand.size(); i++) {
		h.push_back(this->cardsInHand.at(i));
	}
	return h;
}

//stream insertion operators
// Returns a string of all the cards in the input Hand.
ostream& operator << (ostream& out, const Hand& h) {
	string s = "";
	for (int i = 0; i < h.cardsInHand.size(); i++)
	{
		string c = h.cardsInHand.at(i); // only works if I make this line separate from the one below for some reason
		s += c;
		s += ", ";
	}
	s += "\b\b.";

	return out << s;
}
istream& operator << (istream& in, const Hand& h) {
	return in;
}

void Hand::play(string cardToPlay, Deck& d) {
	//getting player's hand
	Player* p = this->player;
	Hand* h = p->getHand();
	//implement function for the cards played
	//checks desired card to be played, creates a new order in the player's orderlist & "plays" the card
	if (cardToPlay == cardsAvailable[0]){
		//Bomb
		//create new order in orderlist
		//create new bomb order
		Bomb* bombCard = new Bomb();
		(p->getOrdersList())->add(bombCard);
		cout << "Player used bomb card; created a new order list." << endl;
		//deletes the card chosen from the player's hand by placing it at the end and then erasing it.
		auto cardToMove = find(h->cardsInHand.begin(), h->cardsInHand.end(), cardsAvailable[0]);
		h->cardsInHand.erase(cardToMove);
		//adding the card at the end of the deck
		d.cardsInDeck.push_back(cardsAvailable[0]);
		cout << "Player has played " << cardToPlay << "from their hand.\n" << cardToPlay << " has been added to the deck." << endl;
	}
	else if (cardToPlay == cardsAvailable[1]) {
		//Diplomacy
		Negotiate* negotiateCard = new Negotiate();
		(p->getOrdersList())->add(negotiateCard);
		cout << "Player used Diplomacy/Negotiate card; created a new order list." << endl;
		//deletes the card chosen from the player's hand by placing it at the end and then erasing it.
		auto cardToMove = find(h->cardsInHand.begin(), h->cardsInHand.end(), cardsAvailable[1]);
		h->cardsInHand.erase(cardToMove);	
		//adding the card at the end of the deck
		d.cardsInDeck.push_back(cardsAvailable[1]);
		cout << "Player has played " << cardToPlay << "from their hand.\n" << cardToPlay << " has been added to the deck." << endl;
	}
	else if (cardToPlay == cardsAvailable[2]) {
		//Blockade
		Blockade* blockCard = new Blockade();
		(p->getOrdersList())->add(blockCard);
		cout << "Player used Blockade card; created a new order list." << endl;
		//deletes the card chosen from the player's hand by placing it at the end and then erasing it.
		auto cardToMove = find(h->cardsInHand.begin(), h->cardsInHand.end(), cardsAvailable[2]);
		h->cardsInHand.erase(cardToMove);		
		//adding the card at the end of the deck
		d.cardsInDeck.push_back(cardsAvailable[2]);
		cout << "Player has played " << cardToPlay << "from their hand.\n" << cardToPlay << " has been added to the deck." << endl;
	}
	else if (cardToPlay == cardsAvailable[3]) {
		//Reinforcement
		Deploy* reinforcementCard = new Deploy();
		(p->getOrdersList())->add(reinforcementCard);
		cout << "Player used Reinforcement card; created a new order list." << endl;
		//deletes the card chosen from the player's hand by placing it at the end and then erasing it.
		auto cardToMove = find(h->cardsInHand.begin(), h->cardsInHand.end(), cardsAvailable[3]);
		h->cardsInHand.erase(cardToMove);		
		//adding the card at the end of the deck
		d.cardsInDeck.push_back(cardsAvailable[3]);
		cout << "Player has played " << cardToPlay << "from their hand.\n" << cardToPlay << " has been added to the deck." << endl;
	}
	else if (cardToPlay == cardsAvailable[4]) {
		//Airlift
		Airlift* airliftCard = new Airlift();
		(p->getOrdersList())->add(airliftCard);
		cout << "Player used Airlift card; created a new order list." << endl;
		//deletes the card chosen from the player's hand by placing it at the end and then erasing it.
		auto cardToMove = find(h->cardsInHand.begin(), h->cardsInHand.end(), cardsAvailable[4]);
		h->cardsInHand.erase(cardToMove);
		//adding the card at the end of the deck
		d.cardsInDeck.push_back(cardsAvailable[4]);
		cout << "Player has played " << cardToPlay << "from their hand.\n" << cardToPlay << " has been added to the deck." << endl;
	}
	else 
	cout << "Player chose a card that they do not possess." << endl;
}


//DECK
//default constructor
Deck::Deck(){	
	int deckSize = 55;
	// determine how many cards to max out
	for (int i = 0; i < deckSize; i++) {
		if (i < 11) 
			cardsInDeck.push_back(cardsAvailable[0]);
		else if (i < 22) 
			cardsInDeck.push_back(cardsAvailable[1]);
		else if (i < 33) 
			cardsInDeck.push_back(cardsAvailable[2]);
		else if (i < 44) 
			cardsInDeck.push_back(cardsAvailable[3]);
		else if (i < 55) 
			cardsInDeck.push_back(cardsAvailable[4]);
	}
	random_shuffle(&cardsInDeck.at(0), &cardsInDeck.at(deckSize - 1));
}

//copy constructor
Deck::Deck(Deck& deck) {
	//copies the cards of another deck
	this->cardsInDeck = deck.cardsInDeck;
}

Deck::Deck(std::vector<string> newCardsInDeck) {
	//creates a deck of 55 cards, by taking another card set
	this->cardsInDeck = newCardsInDeck;
}

Deck::~Deck() {
	delete this;
}

//assignment constructor
Deck& Deck::operator = (const Deck& d) {
	cardsInDeck = d.cardsInDeck;
	return *this;
}

//stream insertion operators
ostream& operator << (ostream& out, const Deck& d) {
	return out;
}
istream& operator << (istream& in, const Deck& d) {
	return in;
}

void Deck::draw(Player* p) {	
	//getting player's hand
	Hand* h = p->getHand();

	//random number from 0 to size of current deck;
	srand(time(NULL));
	int randomCardIndex = rand() % (this->cardsInDeck.size()-1) + 0; 
	//simply add the card to the end of the player's hand
	h->cardsInHand.push_back(this->cardsInDeck.at(randomCardIndex));
	//Removes the randomCard from the deck & reduces the deck's size
	this->cardsInDeck.erase(this->cardsInDeck.begin()+randomCardIndex);
	cout << "Player has added a card into their hand" << endl;
}