#pragma once

#include "Player.h"
#include "Map.h"

class Order;
class Territory;
class Player;

class PlayerStrategy
{
	public:
		virtual ~PlayerStrategy();

		virtual void issueOrder(Player* p) = 0;
		virtual vector<Territory*> toDefend(vector<Territory*> t) = 0;
		virtual vector<Territory*> toAttack(vector<Territory*> t) = 0;
};

class HumanPlayerStrategy : public PlayerStrategy
{
	public:
		HumanPlayerStrategy();

		void issueOrder(Player* p);
		vector<Territory*> toDefend(vector<Territory*> t);
		vector<Territory*> toAttack(vector<Territory*> t);

};

class AggressivePlayerStrategy : public PlayerStrategy
{
	public:
		AggressivePlayerStrategy();
		~AggressivePlayerStrategy();

		void issueOrder(Player* p);
		vector<Territory*> toDefend(vector<Territory*> t);
		vector<Territory*> toAttack(vector<Territory*> t);
};

class BenevolentPlayerStrategy : public PlayerStrategy
{
	public:
		BenevolentPlayerStrategy();

		void issueOrder(Player* p);
		vector<Territory*> toDefend(vector<Territory*> t);
		vector<Territory*> toAttack(vector<Territory*> t);

};

class NeutralPlayerStrategy :public  PlayerStrategy
{
	public:
		NeutralPlayerStrategy();

		void issueOrder(Player* p);
		vector<Territory*> toDefend(vector<Territory*> t);
		vector<Territory*> toAttack(vector<Territory*> t);

};