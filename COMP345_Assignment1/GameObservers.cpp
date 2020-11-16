#include "GameEngine.h"
#include <iostream>
#include <list>

using namespace std;

void Subject::attach(Observer* observer) {
	observers.push_back(observer);
}

void Subject::detach(Observer* detach_observer) {
	int count = observers.size();
	int i;

	for (i = 0; i < count; i++) {
		if (observers[i] == detach_observer)
			break;
	}
	if (i < count)
		observers.erase(observers.begin() + i);
}

void Subject::notify() {
	for (Observer* observer : observers) {
		observer->update();
	}
}

PhaseObserver::PhaseObserver(){}

PhaseObserver::PhaseObserver(GameEngine* gameEngine)
{
	gameEngine->attach(this);
	this->gameEngine = gameEngine;
}

void PhaseObserver::update() {
	string currentPhase = gameEngine->getPhase();

	//why is there no switch 
	if (currentPhase == "Reinforcement Phase") {
		cout << "Current Phase:" << currentPhase << endl;
	}
	if (currentPhase == "Issue Order Phase") {
		cout << "Current Phase:" << currentPhase << endl;
	}
	if (currentPhase == "Execute Order Phase") {
		cout << "Current Phase:" << currentPhase << endl;
	}
}

GameStatisticsObserver::GameStatisticsObserver(){}

GameStatisticsObserver::GameStatisticsObserver(GameEngine* gameEngine)
{
	gameEngine->attach(this);
	this->gameEngine = gameEngine;
}


float gameStats(Player* players, Map* map)
{
	float numTerritories = (float)players->getTerritories().size();
	float playerOwnedTerritories = (float)map->listOfTerritories.size();
	float percentOwned = 100.0*playerOwnedTerritories/numTerritories;
	return percentOwned;
}

void GameStatisticsObserver::update() {

	int totalTerritories = gameEngine->getMap()->listOfTerritories.size();

	for (int i = 0; i < gameEngine->getTotalPlayers().size(); i++) {
		
	}
}
