#pragma once

#include <iostream>
#include <string>
#include "Player.h"
#include "Map.h"


class Order
{

public:

	Order();

	Order(Player* player);

	Order(const Order& other);

	Order& operator = (const Order& other);

	virtual bool validate() = 0;

	virtual bool execute() = 0;

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

	virtual bool validate() override;

	virtual bool execute() override;
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

	virtual bool validate() override;

	virtual bool execute() override;
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

	virtual bool validate() override;

	virtual bool execute() override;
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

	virtual bool validate() override;

	virtual bool execute() override;
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

	virtual bool validate() override;

	virtual bool execute() override;
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

	virtual bool validate() override;

	virtual bool execute() override;
};



