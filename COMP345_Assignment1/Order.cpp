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

//define an equal operator that returns true if two orders are by the same player, and are not executed
bool Order::operator==(const Order& other)
{
	return player == other.player && executed == other.executed;
}

const Player* Order::getPlayer() 
{ 
	return player; 
}

void Order::setPlayer(Player* player)
{
	this->player = player;
}

std::ostream& operator<<(std::ostream& o, const Order& order) 
{
	return o << "An order has been created";
}

Deploy::Deploy(): Order()
{
	Territory(0, "current");
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
	if (territory->getOwner() == getPlayer())
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

ostream& operator << (std::ostream& o, const Deploy& deploy)
{
	return o << "A deploy order has been issued";
}

Advance::Advance(): Order()
{
	Territory(0, "current");
	Territory(0, "Next");
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

ostream& operator << (std::ostream& o, const Advance& advance)
{
	return o << "An advance order has been issued";
}

Bomb::Bomb() : Order()
{
	Territory(0, "source");
	Territory(0, "target");
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

ostream& operator << (std::ostream& o, const Bomb& bomb)
{
	return o << "A bomb order has been issued";
}

Blockade::Blockade() : Order()
{
	Territory(0, "target");
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
	if (target->getOwner() == getPlayer())
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

ostream& operator << (std::ostream& o, const Blockade& b)
{
	return o << "A blockade order has been issued";
}

Airlift::Airlift() : Order()
{
	Territory(0, "current");
	Territory(0, "next");
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
	if (current->getOwner() == getPlayer() && this->numOfArmies > 0)
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

ostream& operator << (std::ostream& o, const Airlift& airlift)
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
	if (getPlayer() != enemy)
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

ostream& operator << (std::ostream& o, const Negotiate& negotiate)
{
	return o << "A negotiate order has been issued.";
}

OrdersList::OrdersList()	
{	
	// create empty vector of Order	
	vector<Order*> o;	
	this->ordersList = o;	
}

OrdersList::OrdersList(const OrdersList& oL) 
{
	ordersList = oL.ordersList;
}

OrdersList& OrdersList::operator=(const OrdersList& oL) 
{
	ordersList = oL.ordersList;
	return *this;
}

void OrdersList::add(Order* order) 
{ 
	ordersList.push_back(order); 
}

void OrdersList::remove(Order* order)
{
	for (vector<Order*>::iterator it = ordersList.begin(); it != ordersList.end(); it++)
		if (*order == *(*it))
			ordersList.erase(it);
}

void OrdersList::move(int oldPosition, int newPosition)
{
	Order* toBeMoved = ordersList[oldPosition];

	remove(ordersList[oldPosition]);

	ordersList.insert(ordersList.begin() + newPosition, toBeMoved);
}
