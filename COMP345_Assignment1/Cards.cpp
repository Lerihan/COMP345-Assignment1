#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <time.h>
#include "Cards.h"
#include "Order.h"
using namespace std;

//CARDS
//default constructor
Card::Card() {
}

Card::~Card() {
	delete this;
}

//assignment constructor
Card& Card::operator = (const Card& c) {
	return *this;
}

//stream insertion operators
ostream& operator << (ostream& out, const Card& c) {
	return out;
}
istream& operator << (istream& in, const Card& c) {
	return in;
}


// ######################################
// BombCard
// ######################################
BombCard::BombCard() {
	this->target = NULL;
}

BombCard::BombCard(Territory* target) {
	this->target = target;
}

BombCard::~BombCard() {
	delete this->target;
	delete this;
}

void BombCard::setTarget(Territory* target) {
	this->target = target;
}

Territory* BombCard::getTarget() {
	return this->target;
}

Bomb* BombCard::play() {
	//creates new bomb order
	Bomb* bombOrder = new Bomb();
	//adds new bomb order to the player's orderlist
	Player* p = this->cardHolder;
	(p->getOrdersList())->add(bombOrder);
	cout << "Player has played a Bomb Card from their hand.\n" << endl;
	//adds the bomb card to the end of the deck
	Deck* d = this->d;
	d->insertBackToDeck(this);
	cout << "Bomb Card has been added to the deck." << endl;
}

ostream& operator << (ostream& out, const BombCard& c) {
	cout << "BombCard";
}


// ######################################
// ReinforcementCard
// ######################################
ReinforcementCard::ReinforcementCard() {
	this->numArmies = 0;
}

ReinforcementCard::ReinforcementCard(int numArmies) {
	this->numArmies = numArmies;
}

ReinforcementCard::~ReinforcementCard() {
	delete this;
}

void ReinforcementCard::setNumArmies(int numArmies) {
	this->numArmies = numArmies;
}

int ReinforcementCard::getNumArmies() {
	return this->numArmies;
}

void ReinforcementCard::play() {
	//creates new reinforcement order
	Deploy* reinforcementCard = new Deploy();
	//adds new reinforcement order to the player's orderlist
	Player* p = this->cardHolder;
	(p->getOrdersList())->add(reinforcementCard);
	cout << "Player has played a Reinforcement Card from their hand.\n" << endl;
	//adds the reinforcement card to the end of the deck
	Deck* d = this->d;
	d->insertBackToDeck(this);
	cout << "Reinforcement Card has been added to the deck." << endl;
}

ostream& operator << (ostream& out, const ReinforcementCard& c) {
	cout << "ReinforcementCard";
}

// ######################################
// BlockadeCard
// ######################################
BlockadeCard::BlockadeCard() {
	this->target = NULL;
}

BlockadeCard::BlockadeCard(Territory* target) {
	this->target = target;
}

BlockadeCard::~BlockadeCard() {
	delete this->target;
	delete this;
}

void BlockadeCard::setTarget(Territory* target) {
	this->target = target;
}

Territory* BlockadeCard::getTarget() {
	return this->target;
}

Blockade* BlockadeCard::play() {
	//creates new block order
	Blockade* blockCard = new Blockade();
	//adds new block order to the player's orderlist
	Player* p = this->cardHolder;
	(p->getOrdersList())->add(blockCard);
	cout << "Player has played a Block Card from their hand.\n" << endl;
	//adds the block card to the end of the deck
	Deck* d = this->d;
	d->insertBackToDeck(this);
	cout << "Block Card has been added to the deck." << endl;
}

ostream& operator << (ostream& out, const BlockadeCard& c) {
	cout << "BlockadeCard";
}

// ######################################
// AirliftCard
// ######################################
AirliftCard::AirliftCard() {
	this->current = NULL;
	this->target = NULL;
	this->numArmies = 0;
}

AirliftCard::AirliftCard(Territory* current, Territory* target, int numArmies) {
	this->current = current;
	this->target = target;
	this->numArmies = numArmies;
}

void AirliftCard::setCurrent(Territory* current) {
	this->current = current;
}

Territory* AirliftCard::getCurrent() {
	return this->current;
}

void AirliftCard::setTarget(Territory* target) {
	this->target = target;
}

Territory* AirliftCard::getTarget() {
	return this->target;
}

void AirliftCard::setNumArmies() {
	this->numArmies = numArmies;
}

int AirliftCard::getNumArmies(int numArmies) {
	return this->numArmies;
}

Airlift* AirliftCard::play() {
	//creates new airlift order
	Airlift* airliftCard = new Airlift();
	//adds new airlift order to the player's orderlist
	Player* p = this->cardHolder;
	(p->getOrdersList())->add(airliftCard);
	cout << "Player has played a Airlift Card from their hand.\n" << endl;
	//adds the airlift card to the end of the deck
	Deck* d = this->d;
	d->insertBackToDeck(this);
	cout << "Airlift Card has been added to the deck." << endl;
}

ostream& operator << (ostream& out, const AirliftCard& c) {
	cout << "AirliftCard";
}

// ######################################
// DiplomacyCard
// ######################################
DiplomacyCard::DiplomacyCard() {
	this->enemy = NULL;
}

DiplomacyCard::DiplomacyCard(Player* enemy) {
	this->enemy = enemy;
}

DiplomacyCard::~DiplomacyCard() {
	delete this->enemy;
	delete this;
}

void DiplomacyCard::setEnemy(Player* enemy) {
	this->enemy = enemy;
}

Player* DiplomacyCard::getEnemy() {
	return this->enemy;
}

Negotiate* DiplomacyCard::play() {
	//creates new diplomacy order
	Negotiate* diplomacyCard = new Negotiate();
	//adds new diplomacy order to the player's orderlist
	Player* p = this->cardHolder;
	(p->getOrdersList())->add(diplomacyCard);
	cout << "Player has played a Diplomacy Card from their hand.\n" << endl;
	//adds the diplomacy card to the end of the deck
	Deck* d = this->d;
	d->insertBackToDeck(this);
	cout << "Diplomacy Card has been added to the deck." << endl;
}

ostream& operator << (ostream& out, const DiplomacyCard& c) {
	cout << "DiplomacyCard";
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

Hand::Hand(Player* playerName, std::vector<Card*> playersCards) {
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
vector<Card*> Hand::getCardsInHand() {
	vector<Card*> h;
	for (int i = 0; i < this->cardsInHand.size(); i++) {
		h.push_back(this->cardsInHand.at(i));
	}
	return h;
}

//stream insertion operators
// Returns a string of all the cards in the input Hand.
ostream& operator << (ostream& out, const Hand& h) {
	for (int i = 0; i < h.cardsInHand.size(); i++)
	{
		Card* c = h.cardsInHand.at(i); // only works if I make this line separate from the one below for some reason
		out << *c << ", ";
	}
	out << "\b\b.";

	return out << endl;
}
istream& operator << (istream& in, const Hand& h) {
	return in;
}

void Hand::play() {
	Player* p = this->player;
	Hand* h = p->getHand();
	//display player's cards in hand
	cout << "Current cards in player's hand: " << endl;
	int i;
	for (i = 0; i < h->cardsInHand.size(); i++) {
		cout << h->cardsInHand.at(i) << " (" << i << ") " << endl;
	}
	//player selects which card they want to play
	cout << "Select a card in your hand to play, by index." << endl;
	int input;
	cin >> input;
	//verify that input is proper
	while (input < 0 || input > h->cardsInHand.size()) {
		cout << "Invalid input. Please try again." << endl;
		cin >> input;
	}
	//selected card is played
	h->cardsInHand.at(input)->play();	
	//deletes the card chosen from the player's hand by placing it at the end and then erasing it.
	auto cardToMove = find(h->cardsInHand.begin(), h->cardsInHand.end(), h->cardsInHand.at(input));
	h->cardsInHand.erase(cardToMove);
}

// make it call play() of the Card subclass
/*
void Hand::play(Card* cardToPlay, Deck* d) {
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
		d->cardsInDeck.push_back(cardsAvailable[0]);
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
*/

//DECK
//default constructor
Deck::Deck() {	
	int deckSize = 55;
	// determine how many cards to max out
	for (int i = 0; i < deckSize; i++) {
		if (i < 11)
			cardsInDeck.push_back(new BombCard());
		else if (i < 22) 
			cardsInDeck.push_back(new ReinforcementCard());
		else if (i < 33) 
			cardsInDeck.push_back(new BlockadeCard());
		else if (i < 44) 
			cardsInDeck.push_back(new AirliftCard());
		else if (i < 55) 
			cardsInDeck.push_back(new DiplomacyCard());
	}
	random_shuffle(&cardsInDeck.at(0), &cardsInDeck.at(deckSize - 1));
}

//copy constructor
Deck::Deck(Deck& deck) {
	//copies the cards of another deck
	this->cardsInDeck = deck.cardsInDeck;
}

Deck::Deck(std::vector<Card*> newCardsInDeck) {
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

//receives a card & puts it at the end of the deck
void Deck::insertBackToDeck(Card* c) {		
	//adding the card at the end of the deck
	this->cardsInDeck.push_back(c);
}

ostream& operator << (ostream& out, const Card& c) {
	return out << "Card";
}

