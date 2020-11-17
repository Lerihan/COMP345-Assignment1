#pragma once
#include "MapLoader.h"
#include "Map.h"
#include "Cards.h"

using namespace std;

class GameEngine
{
public:
	void startGame();
	void startupPhase();

	Map* getMap();

private:
	Map* map;
	vector<Player*> players;
	Player* firstPlayer;
	Deck* deck;
	int numOfPlayers;
	bool observerOn;

	void selectMap();
	void createComponents();
	void setObservers();
	void setInitialArmies();
	void chooseFirstPlayer();
	int randomNumber(int min,  int max);
	void mainGameLoop(); // void for now
	void reinforcementPhase(Player* currPlayer); // void for now
	void issueOrdersPhase(Player* currPlayer);
	void executeOrdersPhase(Player* currPlayer);
};