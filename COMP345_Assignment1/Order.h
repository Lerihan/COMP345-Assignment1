//#pragma once
//
//#include <iostream>
//#include <string>
//#include "Player.h"
//#include "Map.h"
//
//class Player;
//
//class Territory;
//
//class Order
//{
//
//public:
//
//	Order();
//
//	Order(Player* player);
//
//	virtual bool validate() = 0;
//
//	virtual bool execute() = 0;
//
//private:
//
//	Player* player;
//};
//
//class Deploy : public Order
//{
//private:
//
//	Territory* territory;
//	unsigned int numOfArmies;
//
//public:
//
//	Deploy(Player* player, Territory* territory, unsigned int numOfArmies);
//
//	virtual bool validate() override;
//
//	virtual bool execute() override;
//};
//
//class Advance : public Order
//{
//private:
//
//	Territory* current;
//	Territory* next;
//	unsigned int numOfArmies;
//
//public:
//
//	Advance(Player* player, Territory* current, Territory* next, unsigned int numOfArmies);
//
//	virtual bool validate() override;
//
//	virtual bool execute() override;
//};
//
//class Bomb : public Order
//{
//private:
//
//	Territory* target;
//
//public:
//
//	Bomb(Player* player, Territory* target);
//
//	virtual bool validate() override;
//
//	virtual bool execute() override;
//};
//
//class Blockade : public Order
//{
//private:
//
//	Territory* target;
//
//public:
//
//	Blockade(Player* player, Territory* target);
//
//	virtual bool validate() override;
//
//	virtual bool execute() override;
//};
//
//class Airlift : public Order
//{
//private:
//
//	Territory* current;
//	Territory* next;
//	unsigned int numOfArmies;
//
//public:
//
//	Airlift(Player* player, Territory* current, Territory* next, unsigned int numOfArmies);
//
//	virtual bool validate() override;
//
//	virtual bool execute() override;
//};
//
//class Negotiate : public Order
//{
//private:
//
//	Player* enemy;
//
//public:
//
//	Negotiate(Player* current, Player* enemy);
//
//	virtual bool validate() override;
//
//	virtual bool execute() override;
//};
//
//
