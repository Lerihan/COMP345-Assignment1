#pragma once

//#include "Player.h"
#include "Order.h"
#include "Map.h"

class Order;
class Territory;

class PlayerStrategy
{
	public:
		virtual void issueOrder(Order* o) = 0;
		virtual vector<Territory*> toDefend(vector<Territory*> t) = 0;
		virtual vector<Territory*> toAttack(vector<Territory*> t) = 0;
};
/*
class HumanPlayerStrategy : PlayerStrategy
{

};
*/
class AggressivePlayerStrategy : public PlayerStrategy
{
	public:
		AggressivePlayerStrategy();

		void issueOrder(Order* o);
		vector<Territory*> toDefend(vector<Territory*> t);
		vector<Territory*> toAttack(vector<Territory*> t);


};
/*
class BenevolentPlayerStrategy : public PlayerStrategy
{

};

class NeutralPlayerStrategy : PlayerStrategy
{

};*/