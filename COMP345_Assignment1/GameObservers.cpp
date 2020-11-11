#include "GameObservers.h"
#include "GameEngine.h"
#include "Map.h"
#include "Player.h"
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


float gameStats(Player* players, Map* map)
{
	float numTerritories = (float)players->getTerritories().size();
	float playerOwnedTerritories = (float)map->listOfTerritories.size();
	float percentOwned = 100.0*playerOwnedTerritories/numTerritories;
	return percentOwned;
}

void GameStatisticsObserver::update() {


}
