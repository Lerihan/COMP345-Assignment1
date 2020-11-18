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
	this->cardHolder = NULL;
	this->d = NULL;
}

//assignment constructor
Card& Card::operator = (const Card& c) {
	return *this;
}
/*
//stream insertion operators
ostream& operator << (ostream& out, const Card& c) {
	return out << "card ";
}*/

istream& operator >> (istream& in, const Card& c) {
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

Hand::Hand(Player* playerName, std::vector<Card*> playersCards) {
	//creates a new hand with a player and a set of cards
	this->player = playerName;
	this->player->setHand(this);
	this->cardsInHand = playersCards;
}

// If we delete the Hand, it is because its Player has been eliminated.
// Its Cards have thus been put back into the Deck so we do not delete them.
Hand::~Hand() {
	this->player = NULL;
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
	for (Card* c : h.cardsInHand)
	{
		out << c->getType() << ", ";
	}
	out << "\b\b.";

	return out << endl;
}
istream& operator >> (istream& in, const Hand& h) {
	return in;
}

void Hand::play() {
	//plays the first card of the player's hand automatically
	this->cardsInHand.at(0)->play();
	//deletes the card from the player's hand by placing it at the end and then erasing it.
	auto cardToMove = find(this->cardsInHand.begin(), this->cardsInHand.end(), this->cardsInHand.at(0));
	this->cardsInHand.erase(cardToMove);
}

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

		cardsInDeck[i]->d = this;
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

// If we are deleting the Deck it is because the game is over, so we can delete all the Cards;
Deck::~Deck()
{
	for (int i = 0; i < this->cardsInDeck.size(); i++)
	{
		delete this->cardsInDeck[i];
		this->cardsInDeck[i] = NULL;
	}
	this->cardsInDeck.clear();
}

//assignment constructor
Deck& Deck::operator = (const Deck& d) {
	cardsInDeck = d.cardsInDeck;
	return *this;
}

//stream insertion operators
ostream& operator << (ostream& out, const Deck& d) {
	for (Card* c : d.cardsInDeck)
	{
		out << c->getType() << ", ";
	}
	out << "\b\b.";
	return out;
}
istream& operator >> (istream& in, const Deck& d) {
	return in;
}

void Deck::draw(Player* p) {	
	//getting player's hand
	Hand* h = p->getHand();
	//random number from 0 to size of current deck;
	srand(time(NULL));
	int randomCardIndex = rand() % (this->cardsInDeck.size()-1) + 0; 
	//simply add the card to the end of the player's hand
	Card* c = this->cardsInDeck.at(randomCardIndex); // for readability
	c->cardHolder = p;
	h->cardsInHand.push_back(c); // put the Card in the Player's Hand
	//Removes the randomCard from the deck & reduces the deck's size
	this->cardsInDeck.erase(this->cardsInDeck.begin()+randomCardIndex);

	h = NULL;
	c = NULL;
	//cout << "Player " << p->getPlayerNumber() << " has added a card into their hand" << endl;
}

void Deck::insertBackToDeck(Card* c) {
	//adding the card to the end of the deck
	this->cardsInDeck.push_back(c);
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
	this->target = NULL;
}

void BombCard::setTarget(Territory* target) {
	this->target = target;
}

Territory* BombCard::getTarget() {
	return this->target;
}

void BombCard::play() {
	Player* p = this->cardHolder;
	//creates new bomb order
	Bomb* bombOrder = new Bomb();
	//adds new bomb order to the player's orderlist
	p->issueOrder(bombOrder);
	cout << "Player has played a Bomb Card from their hand.\n" << endl;
	//adds the bomb card to the end of the deck
	this->cardHolder = NULL;
	this->d->insertBackToDeck(this);
	cout << "Bomb Card has been added to the deck." << endl;

	bombOrder = NULL;
	p = NULL;
}

ostream& operator << (ostream& out, const BombCard& c) {
	out << "BombCard";
	return out;
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
}

void ReinforcementCard::setNumArmies(int numArmies) {
	this->numArmies = numArmies;
}

int ReinforcementCard::getNumArmies() {
	return this->numArmies;
}

// TODO: what is this supposed to be doing?
void ReinforcementCard::play() {

}

ostream& operator << (ostream& out, const ReinforcementCard& c) {
	out << "ReinforcementCard";
	return out;
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
	this->target = NULL;
}

void BlockadeCard::setTarget(Territory* target) {
	this->target = target;
}

Territory* BlockadeCard::getTarget() {
	return this->target;
}

void BlockadeCard::play() {
	//creates new block order
	Blockade* blockOrder = new Blockade();
	//adds new block order to the player's orderlist
	Player* p = this->cardHolder;
	p->issueOrder(blockOrder);
	cout << "Player has played a Blockade Card from their hand.\n" << endl;
	//adds the block card to the end of the deck
	this->cardHolder = NULL;

	this->d->insertBackToDeck(this);
	cout << "Block Card has been added to the deck." << endl;

	blockOrder = NULL;
	p = NULL;
}

ostream& operator << (ostream& out, const BlockadeCard& c) {
	out << "BlockadeCard";
	return out;
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

AirliftCard::~AirliftCard()
{
	this->current = NULL;
	this->target = NULL;
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

void AirliftCard::play() {
	//creates new airlift order
	Airlift* airliftOrder = new Airlift();
	//adds new airlift order to the player's orderlist
	Player* p = this->cardHolder;
	p->issueOrder(airliftOrder);
	cout << "Player has played a Airlift Card from their hand.\n" << endl;
	//adds the airlift card to the end of the deck
	this->cardHolder = NULL;

	this->d->insertBackToDeck(this);
	cout << "Airlift Card has been added to the deck." << endl;

	airliftOrder = NULL;
	p = NULL;
}

ostream& operator << (ostream& out, const AirliftCard& c) {
	out << "AirliftCard";
	return out;
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
	this->enemy= NULL;
}

void DiplomacyCard::setEnemy(Player* enemy) {
	this->enemy = enemy;
}

Player* DiplomacyCard::getEnemy() {
	return this->enemy;
}

void DiplomacyCard::play() {
	//creates new diplomacy order
	Negotiate* diplomacyOrder = new Negotiate();
	//adds new diplomacy order to the player's orderlist
	Player* p = this->cardHolder;
	p->issueOrder(diplomacyOrder);
	cout << "Player has played a Diplomacy Card from their hand.\n" << endl;
	//adds the diplomacy card to the end of the deck
	this->cardHolder = NULL;

	this->d->insertBackToDeck(this);
	cout << "Diplomacy Card has been added to the deck." << endl;

	diplomacyOrder = NULL;
	p = NULL;
}


ostream& operator << (ostream& out, DiplomacyCard& c) {
	 return out << "DiplomacyCard";
}

string BombCard::getType() { return "BombCard"; }
string ReinforcementCard::getType() { return "ReinforcementCard"; }
string BlockadeCard::getType() { return "BlockadeCard"; }
string AirliftCard::getType() { return "AirliftCard"; }
string DiplomacyCard::getType() { return "DiplomacyCard"; }
