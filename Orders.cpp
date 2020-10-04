
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
}

Advance::Advance(Player* player, Territory* current, Territory* next, unsigned int numOfArmies) : Order(player)
{
	this->current = current;
	this->next = next;
	this->numOfArmies = numOfArmies;
}

Bomb::Bomb(Player* player, Territory* target) : Order(player)
{
	this->target = target;
}

Blockade::Blockade(Player* player, Territory* target) : Order(player)
{
	this->target = target;
}

Airlift::Airlift(Player* player, Territory* current, Territory* next, unsigned int numOfArmies) : Order(player)
{
	this->current = current;
	this->next = next;
	this->numOfArmies = numOfArmies;
}

Negotiate::Negotiate(Player* current, Player* enemy) : Order(current)
{
	this->enemy = enemy;
}



















