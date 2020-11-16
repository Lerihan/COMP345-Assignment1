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

PhaseObserver::PhaseObserver(GameEngine* gameEngine)
{
	gameEngine->attach(this);
	this->subject = gameEngine;
}

void PhaseObserver::update() {
	Player p;
	currentPlayerNum = p.getPlayerNumber();

	const char* currentPhaseInfo;
	switch (currentPhase) {
		case Phase::Reinforcement:
			currentPhaseInfo = "Reinforcement Phase";
			break;
		case Phase::IssuingOrder:
			currentPhaseInfo = "Issuing Orders Phase";
			break;
		case Phase::OrdersExecution:
			currentPhaseInfo = "Executing Orders Phase";
			break;
	}
	cout <<"Player "<< currentPlayerNum << ":" << currentPhase << endl;
}

GameStatisticsObserver::GameStatisticsObserver(GameEngine* gameEngine)
{
	gameEngine->attach(this);
	this->subject = gameEngine;
}


float gameStats(Player* players, Map* map)
{
	float numTerritories = (float)players->getTerritories().size();
	float playerOwnedTerritories = (float)map->listOfTerritories.size();
	float percentOwned = 100.0*playerOwnedTerritories/numTerritories;
	return percentOwned;
}

void GameStatisticsObserver::update() {

	int totalTerritories = subject->getMap()->listOfTerritories.size();

	for (int i = 0; i < subject->getTotalPlayers().size(); i++) {

	}
}
