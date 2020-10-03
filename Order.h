#pragma once

#include <iostream>
#include <string>

class Player;

class Territory;

class Order
{
public:
	
	Order(Player* player);

	virtual bool validate() = 0;

	virtual void execute() = 0;

private:
	Player* player;
};

class Deploy : public Order
{
public:

	Deploy(Player* player, Territory* territory, unsigned int numOfArmies);
	
	virtual bool validate() override;

	virtual void execute() override;

private:
	Territory* territory;
	unsigned int numOfArmies;
};

class Advance : public Order
{
public:

	Advance(Player* player, Territory* current, Territory* adjacent, unsigned int numOfArmies);

	virtual bool validate() override;

	virtual void execute() override;

private:
	Territory* current;
	Territory* adjacent;
	unsigned int numOfArmies;
};

class Bomb : public Order
{
public:

	Bomb(Player* player, Territory* target);

	virtual bool validate() override;

	virtual void execute() override;

private:
	Territory* target;
};

class Blockade : public Order
{
public:

	Blockade(Player* player, Territory* target);

	virtual bool validate() override;

	virtual void execute() override;

private:
	Territory* target;
};

class Airlift : public Order
{
public:

	Airlift(Player* player, Territory* current, Territory* next, unsigned int numOfArmies);

	virtual bool validate() override;

	virtual void execute() override;

private:
	Territory* current;
	Territory* next;
	unsigned int numOfArmies;
};

class Negotiate : public Order
{
public:

	Negotiate(Player* current, Player* enemy);

	virtual bool validate() override;

	virtual void execute() override;

private:
	Player* enemy;
};

std::ostream & operator << (std::ostream &out, const Order &o);

