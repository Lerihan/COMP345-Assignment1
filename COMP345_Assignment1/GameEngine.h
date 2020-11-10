#pragma once
#include "Map.h"

using namespace std;

class GameEngine
{
public:
	void startGame();
	void startupPhase();

private:
	Map* map;
	vector<Player*> players;
	Player* firstPlayer;
	int numOfPlayers;
	bool observerOn;

	void selectMap();
	void selectPlayers(); 
	void setObservers();
	void setInitialArmies();
	void chooseFirstPlayer();
	int randomNumber(int min,  int max);
	void mainGameLoop(); // void for now
	void reinforcementPhase(Player* p); // void for now
	int issueOrdersPhase(Player* currPlayer);
};