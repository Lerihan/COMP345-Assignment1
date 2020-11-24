#pragma once

#include "Player.h"

class PlayerStratgy
{
	public:
		virtual void issueOrder(Order* o) = 0;
		virtual vector<Territory*> toDefend() = 0; // returns vector of arbitrary Territories
		virtual vector<Territory*> toAttack() = 0; // returns vector of arbitrary Territories
};

class HumanPlayerStrategy : PlayerStratgy
{

};

class AggressivePlayerStrategy : PlayerStratgy
{

};

class BenevolentPlayerStrategy : PlayerStratgy
{

};

class NeutralPlayerStrategy : PlayerStratgy
{

};