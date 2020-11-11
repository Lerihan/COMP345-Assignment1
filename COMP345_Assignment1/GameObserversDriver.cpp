#pragma once 
#include "Player.h"
#include "MapLoader.h"
#include "GameEngine.h"
#include "GameObservers.h"

int main() {
	MapLoader* mapLoader = new MapLoader();
	Map* map = mapLoader->GetMap("europe.map");


	Player player1;
	Player player2;

	GameStatisticsObserver gameStatisticsObserver = GameStatisticsObserver();
	PhaseObserver phaseObserver = PhaseObserver();

	player1.attach(&gameStatisticsObserver);
	player1.attach(&phaseObserver);
	player2.attach(&gameStatisticsObserver);
	player2.attach(&phaseObserver);

	player1.addTerritory(map->getTerritory(0));
	player2.addTerritory(map->getTerritory(1));
	player1.issueOrder();
	player2.issueOrder();

	player1.addArmies(10);
	player2.addArmies(20);

	




}