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

public:

	Order();

	Order(Player* player);

	Order(const Order& other);

	Order& operator = (const Order& other);

	bool operator==(const Order& other);

	virtual bool validate() = 0;

	virtual bool execute() = 0;

	const Player* getPlayer();

	void setPlayer(Player* player);

protected:

	bool executed = false;

private:

	Player* player;
};

class Deploy : public Order
{
private:

	Territory* territory;
	unsigned int numOfArmies;

public:

	Deploy();

	Deploy(Player* player, Territory* territory, unsigned int numOfArmies);

	Deploy(const Deploy& deploy);

	Deploy& operator = (const Deploy& deploy);

	virtual bool validate();

	virtual bool execute();
};

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

	Advance& operator = (const Advance& advance);

	virtual bool validate();

	virtual bool execute();
};

class Bomb : public Order
{
private:

	Territory* source;
	Territory* target;

public:

	Bomb();

	Bomb(Player* player, Territory* source,  Territory* target);

	Bomb(const Bomb& bomb);

	Bomb& operator = (const Bomb& bomb);

	virtual bool validate();

	virtual bool execute();
};

class Blockade : public Order
{
private:

	Territory* target;

public:

	Blockade();

	Blockade(Player* player, Territory* target);

	Blockade(const Blockade& blockade);

	Blockade& operator = (const Blockade& blockade);

	virtual bool validate();

	virtual bool execute();
};

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

	Airlift& operator = (const Airlift& airlift);

	virtual bool validate();

	virtual bool execute();
};

class Negotiate : public Order
{
private:

	Player* enemy;

public:

	Negotiate();

	Negotiate(Player* current, Player* enemy);

	Negotiate(const Negotiate& negotiate);

	Negotiate& operator = (const Negotiate& negotiate);

	virtual bool validate();

	virtual bool execute();
};

class OrdersList 
{
public:

	OrdersList();

	OrdersList(const OrdersList& ordersList);

	OrdersList& operator=(const OrdersList& ordersList);

	void move(int oldPosition, int newPosition);

	void add(Order* order);

	void remove(Order* order);

private:

	vector<Order*> ordersList;
};

