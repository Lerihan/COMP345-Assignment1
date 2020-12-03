#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <time.h>
#include "Cards.h"
#include "Order.h"
using namespace std;

// ######################################
// Card
// ######################################
//default constructor
Card::Card() {
}

Card::~Card() {
	this->cardHolder = nullptr;
	this->d = nullptr;
}

// Assignment operator, performs shallow copy only.
Card& Card::operator = (const Card& c) {
	if (&c != this)
	{
		this->cardHolder = c.cardHolder;
		this->d = c.d;
	}

	return *this;
}

// ######################################
// Hand
// ######################################
//default constructor
Hand::Hand() {
	std::vector<Card*> cardsInHand;
}

Hand::Hand(Player* player)
{
	std::vector<Card*> cardsInHand;
	this->player = player;
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
	this->player = nullptr;
}

// Assignment operator, performs shallow copy only.
Hand& Hand::operator = (const Hand& h) {
	if (&h != this)
	{
		this->player = h.player;
		for (Card* c : h.cardsInHand)
		{
			this->cardsInHand.push_back(c);
		}
	}
	return *this;
}

//returns the cards in the player's hands.
vector<Card*> Hand::getCardsInHand() {
	return this->cardsInHand;
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

void Hand::deleteFirstCard() {
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
		this->cardsInDeck[i] = nullptr;
	}
	this->cardsInDeck.clear();
}

// Assignment operator, performs shallow copy only.
Deck& Deck::operator = (const Deck& d) {
	if (&d != this)
	{
		this->cardsInDeck = d.cardsInDeck;
	}
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
	srand(time(nullptr));
	int randomCardIndex = rand() % (this->cardsInDeck.size()-1) + 0; 
	//simply add the card to the end of the player's hand
	Card* c = this->cardsInDeck.at(randomCardIndex); // for readability
	c->cardHolder = p;
	h->cardsInHand.push_back(c); // put the Card in the Player's Hand
	//Removes the randomCard from the deck & reduces the deck's size
	this->cardsInDeck.erase(this->cardsInDeck.begin()+randomCardIndex);

	h = nullptr;
	c = nullptr;
	//cout << "Player " << p->getPlayerNumber() << " has added a card into their hand" << endl;
}

void Deck::insertBackToDeck(Card* c) {
	//adding the card to the end of the deck
	c->cardHolder = NULL;
	this->cardsInDeck.push_back(c);
}

// ######################################
// BombCard
// ######################################
BombCard::BombCard() {
	this->target = nullptr;
}

BombCard::BombCard(Territory* target) {
	this->target = target;
}

BombCard::~BombCard() {
	this->target = nullptr;
}

void BombCard::setTarget(Territory* target) {
	this->target = target;
}

Territory* BombCard::getTarget() {
	return this->target;
}

void BombCard::play() {
	Player* p = this->cardHolder;
	//creates new bomb order where player bombs the highest priority territory toAttack from the player's territory that has the largest army
	Bomb* bombOrder = new Bomb(p, p->toAttack().at(0));
	//adds new bomb order to the player's orderlist
	p->getOrdersList()->add(bombOrder);
	cout << "Player " << p->getPlayerNumber() << " has played a Bomb Card from their hand.\n" << endl;
	//adds the bomb card to the end of the deck
	this->d->insertBackToDeck(this);
	cout << "Bomb Card has been added to the deck." << endl;

	//bombOrder = nullptr;
	p = nullptr;
	this->cardHolder = nullptr;
}

ostream& operator << (ostream& out, const BombCard& c) {
	out << "BombCard";
	return out;
}

// Assignment operator, performs shallow copy only.
BombCard& BombCard::operator =(const BombCard& c)
{
	if (&c != this)
	{
		Card::operator=(c);
		this->target = c.target;
	}
	return *this;
}


// ######################################
// ReinforcementCard
// ######################################
ReinforcementCard::ReinforcementCard() {
}

ReinforcementCard::~ReinforcementCard() {
}

void ReinforcementCard::play() {
	Player* p = this->cardHolder;
	//creates new reinforcement order where player reinforcementss are increased by 5
	p->addReinforcements(5);
	cout << "Player " << p->getPlayerNumber() << " has played a Reinforcement Card from their hand.\n" << endl;
	//adds the reinforcement card to the end of the deck
	this->d->insertBackToDeck(this);
	cout << "Reinforcement Card has been added to the deck." << endl;

	p = nullptr;
	this->cardHolder = nullptr;
}

ostream& operator << (ostream& out, const ReinforcementCard& c) {
	out << "ReinforcementCard";
	return out;
}

// Assignment operator, performs shallow copy only.
ReinforcementCard& ReinforcementCard::operator =(const ReinforcementCard& c)
{
	if (&c != this)
	{
		Card::operator=(c);
	}
	return *this;
}


// ######################################
// BlockadeCard
// ######################################
BlockadeCard::BlockadeCard() {
	this->target = nullptr;
}

BlockadeCard::BlockadeCard(Territory* target) {
	this->target = target;
}

BlockadeCard::~BlockadeCard() {
	this->target = nullptr;
}

void BlockadeCard::setTarget(Territory* target) {
	this->target = target;
}

Territory* BlockadeCard::getTarget() {
	return this->target;
}

void BlockadeCard::play() {
	Player* p = this->cardHolder;
	//creates new block order where player's territory becomes neutral and the number of armies on that territory is multiplied
	Blockade* blockOrder = new Blockade(p, p->toDefend().at(0));
	//adds new block order to the player's orderlist
	p->getOrdersList()->add(blockOrder);
	cout << "Player " << p->getPlayerNumber() << " has played a Blockade Card from their hand.\n" << endl;
	//adds the block card to the end of the deck

	this->d->insertBackToDeck(this);
	cout << "Blockade Card has been added to the deck." << endl;

	//blockOrder = nullptr;
	p = nullptr;
	this->cardHolder = nullptr;
}

ostream& operator << (ostream& out, const BlockadeCard& c) {
	out << "BlockadeCard";
	return out;
}

// Assignment operator, performs shallow copy only.
BlockadeCard& BlockadeCard::operator =(const BlockadeCard& c)
{
	if (&c != this)
	{
		Card::operator=(c);
		this->target = c.target;
	}
	return *this;
}


// ######################################
// AirliftCard
// ######################################
AirliftCard::AirliftCard() {
	this->current = nullptr;
	this->target = nullptr;
	this->numArmies = 0;
}

AirliftCard::AirliftCard(Territory* current, Territory* target, int numArmies) {
	this->current = current;
	this->target = target;
	this->numArmies = numArmies;
}

AirliftCard::~AirliftCard()
{
	this->current = nullptr;
	this->target = nullptr;
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
	Player* p = this->cardHolder;

	//cout << "toAttack: " << p->toAttack().size() << " toDefend: " << p->toDefend().size() << " terr: " << p->getTerritories().size() << endl;

	// creates new airlift order where Player airlifts from his Territory with the most armies, to his Territory with the least
	// TODO later: if target is enemy Territory, initiate attack
	Airlift* airliftOrder = new Airlift(p, p->toDefend().back(), p->toDefend().at(0), p->toDefend().back()->numberOfArmies);
	//adds new airlift order to the player's orderlist
	p->getOrdersList()->add(airliftOrder);
	cout << "Player " << p->getPlayerNumber() << " has played a Airlift Card from their hand.\n" << endl;
	//adds the airlift card to the end of the deck

	this->d->insertBackToDeck(this);
	cout << "Airlift Card has been added to the deck." << endl;

	//airliftOrder = nullptr;
	p = nullptr;
	this->cardHolder = nullptr;
}

ostream& operator << (ostream& out, const AirliftCard& c) {
	out << "AirliftCard";
	return out;
}

// Assignment operator, performs shallow copy only.
AirliftCard& AirliftCard::operator =(const AirliftCard& c)
{
	if (&c != this)
	{
		Card::operator=(c);
		this->current = c.current;
		this->target = c.target;
		this->numArmies = c.numArmies;
	}
	return *this;
}

// ######################################
// DiplomacyCard
// ######################################
DiplomacyCard::DiplomacyCard() {
	this->enemy = nullptr;
}

DiplomacyCard::DiplomacyCard(Player* enemy) {
	this->enemy = enemy;
}

DiplomacyCard::~DiplomacyCard() {
	this->enemy= nullptr;
}

void DiplomacyCard::setEnemy(Player* enemy) {
	this->enemy = enemy;
}

Player* DiplomacyCard::getEnemy() {
	return this->enemy;
}

void DiplomacyCard::play() {
	Player* p = this->cardHolder;
	//creates new diplomacy order where player negotiates witht the owner of the territory with the highest toAttack priority
	// if there are no adjacent enemy Territories then negotiate with himself (this will create an invalid order though)
	Player* enemy = p;
	if (p->toAttack().size() != 0)
		enemy = p->toAttack().at(0)->getOwner();
	Negotiate* diplomacyOrder = new Negotiate(p, enemy);
	//adds new diplomacy order to the player's orderlist
	p->getOrdersList()->add(diplomacyOrder);
	cout << "Player " << p->getPlayerNumber() << " has played a Diplomacy Card from their hand.\n" << endl;
	//adds the diplomacy card to the end of the deck

	this->d->insertBackToDeck(this);
	cout << "Diplomacy Card has been added to the deck." << endl;

	//diplomacyOrder = nullptr;
	p = nullptr;
	this->cardHolder = nullptr;
}


ostream& operator << (ostream& out, DiplomacyCard& c) {
	 return out << "DiplomacyCard";
}

// Assignment operator, performs shallow copy only.
DiplomacyCard& DiplomacyCard::operator =(const DiplomacyCard& c)
{
	if (&c != this)
	{
		Card::operator=(c);
		this->enemy = c.enemy;
	}
	return *this;
}


string BombCard::getType() { return "BombCard"; }
string ReinforcementCard::getType() { return "ReinforcementCard"; }
string BlockadeCard::getType() { return "BlockadeCard"; }
string AirliftCard::getType() { return "AirliftCard"; }
string DiplomacyCard::getType() { return "DiplomacyCard"; }
