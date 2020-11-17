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

void GameStatisticsObserver::update() {

	int totalTerritories = gameEngine->getMap()->listOfTerritories.size();

	for (int i = 0; i < gameEngine->getTotalPlayers().size(); i++) {
		int playerOwnedTerritory = gameEngine->getTotalPlayers()[i]->getTerritories().size();
		if (playerOwnedTerritory == 0) {
			cout << gameEngine->getTotalPlayers()[i]->getName() << " has been eliminated from the game.";
		}
		else if (playerOwnedTerritory == totalTerritories)
		{
			cout << gameEngine->getTotalPlayers()[i]->getName() << " has won the game.";
		}
		else 
		{
			cout << gameEngine->getTotalPlayers()[i]->getName() << " owns " << 100.0*(playerOwnedTerritory/totalTerritories) << "% of the map";
		}
	}
}
