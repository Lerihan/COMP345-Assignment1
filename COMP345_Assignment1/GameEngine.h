#pragma once
#include "MapLoader.h"
#include "Map.h"
#include "Cards.h"
#include "GameObservers.h"

using namespace std;

class GameEngine : public Subject
{
public:
	GameEngine();
	GameEngine(GameEngine& game);
	~GameEngine();
	void startGame();
	void startupPhase();
	Map* getMap();
	Deck* getDeck();
	void mainGameLoop(); // void for now
	vector<Player*> getPlayers();
	string getPhase();

	// made public for now so I can use them in part 3 driver
	void reinforcementPhase(Player* currPlayer); // void for now
	void issueOrdersPhase(Player* currPlayer);
	void executeOrdersPhase(Player* currPlayer);

	Player* checkWinner(); // checks if a Player has won

private:
	Map* map;
	vector<Player*> players;
	Player* firstPlayer;
	Deck* deck;
	int numOfPlayers;
	bool observerOn;
	string phase;

	PhaseObserver* phaseObserver;
	GameStatisticsObserver* gameStatsObserver;

	void selectMap();
	void createComponents();
	void setObservers();
	void setInitialArmies();
	void setRandomOrder();
	void setRandomTerritory();
	void kickPlayers(); // checks if a Player has lost the game
	void endGamePhase(Player* winner); // launches end game winner message

	GameEngine& operator =(const GameEngine& game);
	friend ostream& operator <<(ostream& strm, GameEngine& game);

};