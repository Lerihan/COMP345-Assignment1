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
	string getPhase();

private:
	Map* map;
	vector<Player*> players;
	Player* firstPlayer;
	int numOfPlayers;
	bool observerOn;
	string phase;

	void selectMap();
	void selectPlayers(); 
	void setObservers();
	void setInitialArmies();
	void chooseFirstPlayer();
	int randomNumber(int min,  int max);
	void mainGameLoop(); // void for now
	void reinforcementPhase(Player* currPlayer); // void for now
	void issueOrdersPhase(Player* currPlayer);
	void executeOrdersPhase(Player* currPlayer);
	void kickPlayer(); // checks if a Player has lost the game
	Player* checkWinner(); // checks if a Player has won
	void endGamePhase(Player* winner); // launches end game winner message
};