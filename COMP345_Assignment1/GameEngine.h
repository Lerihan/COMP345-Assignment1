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
	vector<Player*> getPlayers();

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
	void setRandomOrder();
	void setRandomTerritory();
	void mainGameLoop(); // void for now
	void reinforcementPhase(Player* currPlayer); // void for now
	void issueOrdersPhase(Player* currPlayer);
	void executeOrdersPhase(Player* currPlayer);
	void kickPlayer(); // checks if a Player has lost the game
	Player* checkWinner(); // checks if a Player has won
	void endGamePhase(Player* winner); // launches end game winner message
};