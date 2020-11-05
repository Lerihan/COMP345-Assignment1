#define NOMINMAX
#include <algorithm>
#include<iostream>
#include <sstream>
#include <vector>
#include"Order.h"

using namespace std;

/*Default constructor for the Order base class
*/
Order::Order() : player()
{
}

/*Parametrized constructor for the Order base class
*/
Order::Order(Player* player)
{
	this->player = player;
}

/*Copy constructor for the Order base class
*/
Order::Order(const Order& order) {
	player = order.player;
	executed = order.executed;
}

Order::~Order()
{
	delete this->player;
	delete this;
}

/*Assignment operator for the Order base class
*/
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

/*Get the player that executes a particular order
*/
const Player* Order::getPlayer() 
{ 
	return player; 
}

/*Set the player executing a particular order
*/
void Order::setPlayer(Player* player)
{
	this->player = player;
}

/*Stream insertion operator for the base Order class
*/
std::ostream& operator<<(std::ostream& o, const Order& order) 
{
	return o << "An order is in the list";
}

/*Default constructor for the Deploy class
*/
Deploy::Deploy(): Order()
{
	Territory(0, "current");
}

/*Parametrized constructor for the Deploy class
*/
Deploy::Deploy(Player* player, Territory* territory, unsigned int numOfArmies): Order(player)
{
	this->territory = territory;
	this->numOfArmies = numOfArmies;
}

/*Copy constructor for the Deploy class
*/
Deploy::Deploy(const Deploy& deploy): Order(deploy)
{
	this->territory = deploy.territory;
	this->numOfArmies = deploy.numOfArmies;
}

Deploy::~Deploy()
{
	delete this->territory;
	delete this;
}

/*Assignment operator for the Deploy class
*/
Deploy& Deploy::operator=(const Deploy& deploy) 
{
	Order::operator=(deploy);
	territory = deploy.territory;
	numOfArmies = deploy.numOfArmies;
	return *this;
}

/*Validate method for Deploy class, validating the owner of the current territory and the numOfArmies is positive
*/
bool Deploy::validate()
{
	if (territory->getOwner() == getPlayer() && this->numOfArmies > 0)
		return true;
	return false;
}

/*Execute method if validate() returns true
*/
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

/*Stream insertion operator for Deploy class order
*/
ostream& operator << (std::ostream& o, const Deploy& deploy)
{
	return o << "A deploy order has been issued";
}

/*Default constructor for the Advance class
*/
Advance::Advance(): Order()
{
	Territory(0, "current");
	Territory(0, "Next");
}

/*Parametrized constructor for the Advance class
*/
Advance::Advance(Player* player, Territory* current, Territory* next, unsigned int numOfArmies) : Order(player)
{
	this->current = current;
	this->next = next;
	this->numOfArmies = numOfArmies;
}

/*Copy constructor for the Advance class
*/
Advance::Advance(const Advance& advance) : Order(advance)
{
	this->current = advance.current;
	this->next = advance.next;
}

Advance::~Advance()
{
	delete this->current;
	delete this->next;
	delete this;
}

/*Assignment operator for the Advance class
*/
Advance& Advance::operator=(const Advance& advance)
{
	Order::operator=(advance);
	current = advance.current;
	next = advance.next;
	numOfArmies = advance.numOfArmies;
	return *this;
}

/*Validate method for Advance class, validating the current and next territories are adjacent
*/
bool Advance::validate()
{
	if (current->isAdjacent(next->index))
		return true;
	return false;
}

/*Execute method if validate() returns true
*/
bool Advance::execute()
{
	if (validate())
	{
		cout << "Advancing " << numOfArmies << " armies from " << current->name << " to " << next->name << ".\n";
		executed = true;
		return true;
	}
	return false;
}

/*Stream insertion operator for Advance class order
*/
ostream& operator << (std::ostream& o, const Advance& advance)
{
	return o << "An advance order has been issued";
}

/*Default constructor for the Bomb class
*/
Bomb::Bomb() : Order()
{
	Territory(0, "source");
	Territory(0, "target");
}

/*Parametrized constructor for the Bomb class
*/
Bomb::Bomb(Player* player, Territory* source, Territory* target): Order(player)
{
	this->source = source;
	this->target = target;
}

/*Copy constructor for the Bomb class
*/
Bomb::Bomb(const Bomb& bomb) : Order(bomb) 
{
	this->source = bomb.source;
	this->target = bomb.target;
}

Bomb::~Bomb()
{
	delete this->source;
	delete this->target;
	delete this;
}

/*Assignment operator for the Bomb class
*/
Bomb& Bomb::operator=(const Bomb& bomb) 
{
	Order::operator=(bomb);
	source = bomb.source;
	target = bomb.target;
	return *this;
}

/*Validate method for Bomb class, validating the current and next territories are adjacent
*/
bool Bomb::validate()
{
	if (source->isAdjacent(target->index))
		return true;
	return false;
}

/*Execute method if validate() returns true
*/
bool Bomb::execute()
{
	if (validate())
	{
		cout << "Bombing " << target->name << " territory, reducing 1/2 of its forces.\n";
		executed = true;
		return true;
	}
	return false;
}

/*Stream insertion operator for Bomb class order
*/
ostream& operator << (std::ostream& o, const Bomb& bomb)
{
	return o << "A bomb order has been issued";
}

/*Default constructor for the Blockade class
*/
Blockade::Blockade() : Order()
{
	Territory(0, "target");
}

/*Parametrized constructor for the Blockade class
*/
Blockade::Blockade(Player* player, Territory* target) : Order(player)
{
	this->target = target;
}

/*Copy constructor for the Blockade class
*/
Blockade::Blockade(const Blockade& blockade) : Order(blockade) 
{
	this->target = blockade.target;
}

Blockade::~Blockade()
{
	delete this->target;
	delete this;
}

/*Assignment operator for the Blockade class
*/
Blockade& Blockade::operator=(const Blockade& blockade) 
{
	Order::operator=(blockade);
	target = blockade.target;
	return *this;
}

/*Validate method for Blockade class, validating the owner of the target territory is myself
*/
bool Blockade::validate()
{
	if (target->getOwner() == getPlayer())
		return true;
	return false;
}

/*Execute method if validate() returns true
*/
bool Blockade::execute()
{
	if (validate())
	{
		cout << "Blockading " << target->name << " territory, tripling its forces.\n";
		executed = true;
		return true;
	}
	return false;
}

/*Stream insertion operator for Blockade class order
*/
ostream& operator << (std::ostream& o, const Blockade& b)
{
	return o << "A blockade order has been issued";
}

/*Default constructor for the Airlift class
*/
Airlift::Airlift() : Order()
{
	Territory(0, "current");
	Territory(0, "next");
}

/*Parametrized constructor for the Airlift class
*/
Airlift::Airlift(Player* player, Territory* current, Territory* next, unsigned int numOfArmies) : Order(player)
{
	this->current = current;
	this->next = next;
	this->numOfArmies = numOfArmies;
}

/*Copy constructor for the Airlift class
*/
Airlift::Airlift(const Airlift& airlift) : Order(airlift) 
{
	this->current = airlift.current;
	this->next = airlift.next;
}

Airlift::~Airlift()
{
	delete this->current;
	delete this->next;
	delete this;
}

/*Assignment operator for the Airlift class
*/
Airlift& Airlift::operator=(const Airlift& airlift) 
{
	Order::operator=(airlift);
	current = airlift.current;
	next = airlift.next;
	return *this;
}

/*Validate method for Airlift class, validating the owner of the target territory is myself, as well as numOfArmies is positive
*/
bool Airlift::validate()
{
	if (current->getOwner() == getPlayer() && this->numOfArmies > 0)
		return true;
	return false;
}

/*Execute method if validate() returns true
*/
bool Airlift::execute()
{
	if (validate())
	{
		cout << "Airlifting " << numOfArmies << " armies from " << current->name << " to " << next->name << " territory.\n";
		executed = true;
		return true;
	}
	return false;
}

/*Stream insertion operator for Airlift class order
*/
ostream& operator << (std::ostream& o, const Airlift& airlift)
{
	return o << "An airlift order has been issued.";
}

/*Default constructor for the Negotiate class
*/
Negotiate::Negotiate() : Order()
{
}

/*Parametrized constructor for the Negotiate class
*/
Negotiate::Negotiate(Player* current, Player* enemy) : Order(current)
{
	this->enemy = enemy;
}

/*Copy constructor for the Negotiate class
*/
Negotiate::Negotiate(const Negotiate& negotiate) : Order(negotiate) 
{
	this->enemy = negotiate.enemy;
}

Negotiate::~Negotiate()
{
	delete this->enemy;
	delete this;
}

/*Assignment operator for the Negotiate class
*/
Negotiate& Negotiate::operator=(const Negotiate& negotiate) 
{
	Order::operator=(negotiate);
	this->enemy = negotiate.enemy;
	return *this;
}

/*Validate method for Negotiate class, validating that the enemy target territory is not one of my territories
*/
bool Negotiate::validate()
{
	if (getPlayer() != enemy)
		return true;
	return false;
}

/*Execute method if validate() returns true
*/
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

/*Stream insertion operator for Negotiate class order
*/
ostream& operator << (std::ostream& o, const Negotiate& negotiate)
{
	return o << "A negotiate order has been issued.";
}

// Create a new vector of the Orders in this OrdersList and return it
vector<Order*> OrdersList::getOrdersList()
{
	vector<Order*> o;
	for (int i = 0; i < ordersList.size(); i++)
	{
		o.push_back(ordersList.at(i));
	}
	return o;
}

/*Copy constructor for the OrdersList class
*/
OrdersList::OrdersList(const OrdersList& oL) 
{
	ordersList = oL.ordersList;
}

/*Assignment operator for the OrdersList class
*/
OrdersList& OrdersList::operator=(const OrdersList& oL) 
{
	ordersList = oL.ordersList;
	return *this;
}

/*Add method, adding an order to the OrdersList
*/
void OrdersList::add(Order* order) 
{ 
	ordersList.push_back(order); 
}

/*Remove method, removing an order from the OrdersList
*/
void OrdersList::remove(int index)
{
	//if position out of bound, cannot remove
	if (index < 0 || index >= ordersList.size())
		return;

	ordersList.erase(ordersList.begin() + index);
}

/*Move method, moving an order from a position to another position in the OrdersList
*/
void OrdersList::move(int oldIndex, int newIndex)
{
	//if position out of bound, cannot move
	if (oldIndex < 0 || oldIndex >= ordersList.size())
		return;

	int newOrderIndex = min(max(newIndex, 0), (int)ordersList.size());

	Order* toMove = ordersList[oldIndex];
	ordersList.erase(ordersList.begin() + oldIndex);
	ordersList.insert(ordersList.begin() + newOrderIndex, toMove);
}

/*Default constructor for the OrdersList class
*/
OrdersList::OrdersList()	
{	
	// create empty vector of Order	
	vector<Order*> o;	
	this->ordersList = o;	
}

// Destructor. Deletes pointer of each Order contained in the OrdersList vector, and the OrdersList pointer itself.
OrdersList::~OrdersList()
{
	for (int i = 0; i < this->ordersList.size(); i++)
	{
		delete this->ordersList[i];
		this->ordersList[i] = NULL;
	}
	this->ordersList.clear(); // remove placeholder memory locations
	delete this;
}

/*Stream insertion operator for OrdersList class
*/
ostream& operator <<(ostream& o, const OrdersList& ol)
{
	stringstream ss;

	ss << "Current list:" << endl;

	for (Order* order : ol.ordersList)
	{
		ss << "\t" << "An order of " << typeid(*order).name() << " is in the list,\n";
	}

	return o << ss.str() << "==============================" << endl;
}
