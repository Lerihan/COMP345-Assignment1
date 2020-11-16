#pragma once
#include "Map.h"
#include "GameObservers.h"

using namespace std;

class GameEngine : public Subject
{
public:
	void startGame();
	void startupPhase();
	vector<Player*> getTotalPlayers();
	Map* getMap();

private:
	Map* map;
	vector<Player*> players;
	Player* firstPlayer;
	int numOfPlayers;
	bool observerOn;

	string phase;
	string getPhase();

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