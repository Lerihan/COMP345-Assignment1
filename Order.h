#pragma once

#include <iostream>
#include <string>

class Player;

class Order
{
public:
	
	Order(Player* player);

	virtual bool validate() = 0;

	virtual void execute() = 0;

};

class Deploy : public Order
{
	Deploy(Player* player, std::string armyName);
	
	virtual bool validate();

	virtual void execute();

};
