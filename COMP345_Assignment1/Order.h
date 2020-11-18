#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include "Map.h"

using namespace std;

class Territory;
class Player;

class Order
{

//Order base class
public:

	Order();

	Order(Player* player);

	Order(const Order& other);

	virtual ~Order(); // declare as virtual so appropriate subclass destructor is called.

	Order& operator = (const Order& other);

	bool operator==(const Order& other);

	virtual bool validate() = 0;

	virtual bool execute() = 0;

	virtual string getType() = 0; // returns string indicating type of Order

	const Player* getPlayer();

	void setPlayer(Player* player);

	bool isExecuted();

	Player* player;

protected:

	bool executed = false;
};

// Deploy armies to one of player's territories
class Deploy : public Order
{
private:

	Territory* territory;
	unsigned int numOfArmies;

public:

	Deploy();

	Deploy(Player* player, Territory* territory, unsigned int numOfArmies);

	Deploy(const Deploy& deploy);

	~Deploy();

	Deploy& operator = (const Deploy& deploy);

	virtual bool validate();

	virtual bool execute();

	string getType(); // returns string indicating type of Order

	friend ostream& operator<<(std::ostream& o, const Deploy& deploy);
};

//Advance armies from one territory to the target territory
class Advance : public Order
{
private:

	Territory* current;
	Territory* next;
	unsigned int numOfArmies;

public:

	Advance();

	Advance(Player* player, Territory* current, Territory* next, unsigned int numOfArmies);

	Advance(const Advance& advance);

	~Advance();

	Advance& operator = (const Advance& advance);

	virtual bool validate();

	virtual bool execute();

	string getType(); // returns string indicating type of Order

	friend ostream& operator<<(std::ostream& o, const Advance& advance);
};

//Bomb order, shrinking target territory forces by 1/2
class Bomb : public Order
{
private:

	Territory* source;
	Territory* target;

public:

	Bomb();

	Bomb(Player* player, Territory* source,  Territory* target);

	Bomb(const Bomb& bomb);

	~Bomb();

	Bomb& operator = (const Bomb& bomb);

	virtual bool validate();

	virtual bool execute();

	string getType(); // returns string indicating type of Order

	friend ostream& operator<<(std::ostream& o, const Bomb& bomb);
};

//Blockade order, increasing target territory armies by 3 fold
class Blockade : public Order
{
private:

	Territory* target;

public:
	
	Blockade();

	Blockade(Player* player, Territory* target);

	Blockade(const Blockade& blockade);

	~Blockade();

	Blockade& operator = (const Blockade& blockade);

	virtual bool validate();

	virtual bool execute();

	string getType(); // returns string indicating type of Order

	friend ostream& operator<<(std::ostream& o, const Blockade& blockade);
};

//Airlift armies to any target territories
class Airlift : public Order
{
private:

	Territory* current;
	Territory* next;
	unsigned int numOfArmies;

public:

	Airlift();

	Airlift(Player* player, Territory* current, Territory* next, unsigned int numOfArmies);

	Airlift(const Airlift& airlift);

	~Airlift();

	Airlift& operator = (const Airlift& airlift);

	virtual bool validate();

	virtual bool execute();

	string getType(); // returns string indicating type of Order

	friend ostream& operator<<(std::ostream& o, const Airlift& airlift);
};

//Negotiate order that does nothing during current turn
class Negotiate : public Order
{
private:

	Player* enemy;

public:

	Negotiate();

	Negotiate(Player* current, Player* enemy);

	Negotiate(const Negotiate& negotiate);

	~Negotiate();

	Negotiate& operator = (const Negotiate& negotiate);

	virtual bool validate();

	virtual bool execute();

	string getType(); // returns string indicating type of Order

	friend ostream& operator<<(std::ostream& o, const Negotiate& negotiate);
};

//OrderList class, implementing a vector
class OrdersList 
{
public:

	OrdersList();

	OrdersList(const OrdersList& ordersList);

	~OrdersList();

	OrdersList& operator=(const OrdersList& ordersList);

	void move(int oldPosition, int newPosition);

	void add(Order* order);

	void remove(int index);

	friend ostream& operator <<(std::ostream& o, const OrdersList& oL);

	vector<Order*> getOrdersList();

private:

	vector<Order*> ordersList;
};
