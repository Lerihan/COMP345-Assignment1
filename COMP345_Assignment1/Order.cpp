
#include<iostream>
#include"Order.h"

using namespace std;

Order::Order() : player()
{
}

Order::Order(Player* player)
{
	this->player = player;
}

Order::Order(const Order& order) {
	player = order.player;
	executed = order.executed;
}

Order& Order::operator=(const Order& order) {
	player = order.player;
	executed = order.executed;
	return *this;
}

std::ostream& operator<<(std::ostream& o, const Order& order) 
{
	return o << "An order has been created";
}

Deploy::Deploy(): Order()
{
	Territory("current");
}

Deploy::Deploy(Player* player, Territory* territory, unsigned int numOfArmies): Order(player)
{
	this->territory = territory;
	this->numOfArmies = numOfArmies;
}

Deploy::Deploy(const Deploy& deploy): Order(deploy)
{
	this->territory = deploy.territory;
	this->numOfArmies = deploy.numOfArmies;
}

Deploy& Deploy::operator=(const Deploy& deploy) 
{
	Order::operator=(deploy);
	territory = deploy.territory;
	numOfArmies = deploy.numOfArmies;
	return *this;
}

bool Deploy::validate()
{
	cout << "If player owns the territory" << endl;
	return true;
}

bool Deploy::execute()
{
	if (validate())
	{ 
		cout << "Deploying " << numOfArmies << " armies.\n";
		executed = true;
		return true;
	}
	return false;
}

std::ostream& operator << (std::ostream& o, const Deploy& deploy)
{
	return o << "A deploy order has been issued";
}

Advance::Advance(): Order()
{
	Territory("current");
	Territory("Next");
}

Advance::Advance(Player* player, Territory* current, Territory* next, unsigned int numOfArmies) : Order(player)
{
	this->current = current;
	this->next = next;
	this->numOfArmies = numOfArmies;
}

Advance::Advance(const Advance& advance) : Order(advance)
{
	this->current = advance.current;
	this->next = advance.next;
}

Advance& Advance::operator=(const Advance& advance)
{
	Order::operator=(advance);
	current = advance.current;
	next = advance.next;
	numOfArmies = advance.numOfArmies;
	return *this;
}

bool Advance::validate()
{
	cout << "If player owns current territory and target territory is neutral(?), AND has numOfArmies > 0" << endl;
	return true;
}

bool Advance::execute()
{
	if (validate())
	{
		cout << "Advancing " << numOfArmies << " armies from " << current << " to " << next << ".\n";
		executed = true;
		return true;
	}
	return false;
}

std::ostream& operator << (std::ostream& o, const Advance& advance)
{
	return o << "An advance order has been issued";
}

Bomb::Bomb() : Order()
{
	Territory("source");
	Territory("target");
}

Bomb::Bomb(Player* player, Territory* source, Territory* target): Order(player)
{
	this->source = source;
	this->target = target;
}

Bomb::Bomb(const Bomb& bomb) : Order(bomb) 
{
	this->source = bomb.source;
	this->target = bomb.target;
}


Bomb& Bomb::operator=(const Bomb& bomb) 
{
	Order::operator=(bomb);
	source = bomb.source;
	target = bomb.target;
	return *this;
}

bool Bomb::validate()
{
	cout << "If enemy target territory is adjacent to ANY of player's current territories" << endl;
	return true;
}

bool Bomb::execute()
{
	if (validate())
	{
		cout << "Bombing " << target << " territory, reducing 1/2 of its forces.\n";
		executed = true;
		return true;
	}
	return false;
}

std::ostream& operator << (std::ostream& o, const Bomb& bomb)
{
	return o << "A bomb order has been issued";
}

Blockade::Blockade() : Order()
{
	Territory("target");
}

Blockade::Blockade(Player* player, Territory* target) : Order(player)
{
	this->target = target;
}

Blockade::Blockade(const Blockade& blockade) : Order(blockade) 
{
	this->target = blockade.target;
}

Blockade& Blockade::operator=(const Blockade& blockade) 
{
	Order::operator=(blockade);
	target = blockade.target;
	return *this;
}

bool Blockade::validate()
{
	cout << "If player owns target territory" << endl;
	return true;
}

bool Blockade::execute()
{
	if (validate())
	{
		cout << "Blockading " << target << " territory, tripling its forces.\n";
		executed = true;
		return true;
	}
	return false;
}

std::ostream& operator << (std::ostream& o, const Blockade& b)
{
	return o << "A blockade order has been issued";
}

Airlift::Airlift() : Order()
{
	Territory("current");
	Territory("next");
}

Airlift::Airlift(Player* player, Territory* current, Territory* next, unsigned int numOfArmies) : Order(player)
{
	this->current = current;
	this->next = next;
	this->numOfArmies = numOfArmies;
}

Airlift::Airlift(const Airlift& airlift) : Order(airlift) 
{
	this->current = airlift.current;
	this->next = airlift.next;
}

Airlift& Airlift::operator=(const Airlift& airlift) 
{
	Order::operator=(airlift);
	current = airlift.current;
	next = airlift.next;
	return *this;
}

bool Airlift::validate()
{
	cout << "If player owns current territory, AND current territory has more armies than numOfArmies to be airlifted " << endl;
	return true;
}

bool Airlift::execute()
{
	if (validate())
	{
		cout << "Airlifting " << numOfArmies << " armies from " << current << " to " << next << " territory.\n";
		executed = true;
		return true;
	}
	return false;
}

std::ostream& operator << (std::ostream& o, const Airlift& airlift)
{
	return o << "An airlift order has been issued.";
}

Negotiate::Negotiate() : Order()
{
}

Negotiate::Negotiate(Player* current, Player* enemy) : Order(current)
{
	this->enemy = enemy;
}

Negotiate::Negotiate(const Negotiate& negotiate) : Order(negotiate) 
{
	this->enemy = negotiate.enemy;
}

Negotiate& Negotiate::operator=(const Negotiate& negotiate) 
{
	Order::operator=(negotiate);
	this->enemy = negotiate.enemy;
	return *this;
}


bool Negotiate::validate()
{
	cout << "If ??" << endl;
	return true;
}

bool Negotiate::execute()
{
	if (validate())
	{
		cout << "Negotiating.. No attack is being performed this turn.\n";
		executed = true;
		return true;
	}
	return false;
}

std::ostream& operator << (std::ostream& o, const Negotiate& negotiate)
{
	return o << "A negotiate order has been issued.";
}



