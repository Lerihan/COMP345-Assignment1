#pragma once
#include "Map.h"

using namespace std;

class GameEngine
{
public:
	void startGame();
	void startupPhase();
	void mainGameLoop(); // void for now

	Map* getMap();
	vector<Player*> getPlayers();

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
	void reinforcementPhase(Player* currPlayer); // void for now
	void issueOrdersPhase(Player* currPlayer);
	void executeOrdersPhase(Player* currPlayer);
	void kickPlayer(); // checks if a Player has lost the game
	Player* checkWinner(); // checks if a Player has won
	void endGamePhase(Player* winner); // launches end game winner message
};