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
		cout << "-------------------------------" << endl;
	}
	if (currentPhase == "Issue Order Phase") {
		cout << "Current Phase:" << currentPhase << endl;
		cout << "-------------------------------" << endl;
	}
	if (currentPhase == "Execute Order Phase") {
		cout << "Current Phase: " << currentPhase << endl;
		cout << "-------------------------------" << endl;
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

	cout << "\nCurrent Game Statistics" << endl;
	cout << "-------------------------------" << endl;

	for (int i = 0; i < gameEngine->getPlayers().size(); i++) {
		int playerOwnedTerritory = gameEngine->getPlayers()[i]->getTerritories().size();
		if (playerOwnedTerritory == 0) {
			cout << gameEngine->getPlayers()[i]->getPlayerNumber() << " has been eliminated from the game." << endl;
		}
		else if (playerOwnedTerritory == totalTerritories)
		{
			cout << gameEngine->getPlayers()[i]->getPlayerNumber() << " has won the game." << endl;
		}
		else 
		{
			cout << "Player " << gameEngine->getPlayers()[i]->getPlayerNumber() << " owns " 
				<< 100.0*(playerOwnedTerritory/totalTerritories) << "% of the map" << endl;
		}
	}
}
