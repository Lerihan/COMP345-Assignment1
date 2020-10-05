
#include<iostream>
#include"Order.h"

using namespace std;

Order::Order(Player* player)
{
	this->player = player;
}

Deploy::Deploy(Player* player, Territory* territory, unsigned int numOfArmies) : Order(player)
{
	this->territory = territory;
	this->numOfArmies = numOfArmies;

	std::ostream& operator << (std::ostream & o, const Deploy & d)
		return o << "Deploy " << d.numOfArmies << " armies to " << d.player << "'s " << d.territory << " territory." << endl;
}

bool Deploy::validate()
{
	cout << "If player owns the territory" << endl;
	return true;
}

bool Deploy::execute()
{
	if (validate())
		return true;
}

Advance::Advance(Player* player, Territory* current, Territory* next, unsigned int numOfArmies) : Order(player)
{
	this->current = current;
	this->next = next;
	this->numOfArmies = numOfArmies;

	std::ostream& operator << (std::ostream & o, const Advance & a)
		return o << "Player " << a.player << " advances " << a.numOfArmies << " armies from " << a.current << " to " << a.next << endl;
}

bool Advance::validate()
{
	cout << "If player owns current territory and target territory is neutral(?), AND has numOfArmies > 0" << endl;
	return true;
}

bool Advance::execute()
{
	if (validate())
		return true;
}

Bomb::Bomb(Player* player, Territory* target) : Order(player)
{
	this->target = target;

	std::ostream& operator << (std::ostream & o, const Bomb & b)
		return o << "Player " << b.player << " bombs " << b.target << " enemy territory, destroying half of its troops." << endl;
}

bool Bomb::validate()
{
	cout << "If enemy target territory is adjacent to ANY of player's current territories" << endl;
	return true;
}

bool Bomb::execute()
{
	if (validate())
		return true;
}

Blockade::Blockade(Player* player, Territory* target) : Order(player)
{
	this->target = target;

	std::ostream& operator << (std::ostream & o, const Blockade & blck)
		return o << "Player " << blck.player << " triples its number of troops on " << blck.target << endl;
}

bool Blockade::validate()
{
	cout << "If player owns target territory" << endl;
	return true;
}

bool Blockade::execute()
{
	if (validate())
		return true;
}

Airlift::Airlift(Player* player, Territory* current, Territory* next, unsigned int numOfArmies) : Order(player)
{
	this->current = current;
	this->next = next;
	this->numOfArmies = numOfArmies;

	std::ostream& operator << (std::ostream & o, const Airlift & air)
		return o << "Player " << air.player << " airlifts " << air.numOfArmies << " armies from " << air.current << " to " << air.next << endl;
}

bool Airlift::validate()
{
	cout << "If player owns current territory, AND current territory has more armies than numOfArmies to be airlifted " << endl;
	return true;
}

bool Airlift::execute()
{
	if (validate())
		return true;
}

Negotiate::Negotiate(Player* current, Player* enemy) : Order(current)
{
	this->enemy = enemy;

	std::ostream& operator << (std::ostream & o, const Negotiate & n)
		return o << "Player " << n.current << " negotiates with " << n.enemy << endl;
}

bool Negotiate::validate()
{
	cout << "If ??" << endl;
	return true;
}

bool Negotiate::execute()
{
	if (validate())
		return true;
}



















