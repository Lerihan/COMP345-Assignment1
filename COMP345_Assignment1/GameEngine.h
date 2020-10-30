#pragma once
#include "Map.h"

using namespace std;

class GameEngine
{
public:
	void startGame();

private:
	Map* map;
	vector<Player*> players;
	void selectMap();
	void selectPlayers();
	void setObservers();
};