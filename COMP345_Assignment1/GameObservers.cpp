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

PhaseObserver::PhaseObserver(){
}

PhaseObserver::PhaseObserver(const PhaseObserver& po)
{
	gameEngine = po.gameEngine;
	currentPlayerNum = po.currentPlayerNum;
}

PhaseObserver& PhaseObserver::operator=(const PhaseObserver& po)
{
	gameEngine = po.gameEngine;
	currentPlayerNum = po.currentPlayerNum;

	return *this;
}

PhaseObserver::PhaseObserver(GameEngine* gameEngine)
{
	gameEngine->attach(this);
	this->gameEngine = gameEngine;
}

PhaseObserver::~PhaseObserver()
{
	delete this->gameEngine;
}

void PhaseObserver::update() {
	string currentPhase = gameEngine->getPhase();

	if (currentPhase == "Reinforcement Phase") {
		cout << "Current Phase: " << currentPhase << endl;
		cout << "-------------------------------" << endl;
		currentPhase.clear();
	}
	if (currentPhase == "Issue Order Phase") {
		cout << "Current Phase: " << currentPhase << endl;
		cout << "-------------------------------" << endl;
		currentPhase.clear();
	}
	if (currentPhase == "Issue Order Phase: Issue Deploy Order") {
		cout << "Current Phase: " << currentPhase << endl;
		cout << "-------------------------------" << endl;
		currentPhase.clear();
	}
	if (currentPhase == "Issue Order Phase: Issue Advance Order") {
		cout << "Current Phase: " << currentPhase << endl;
		cout << "-------------------------------" << endl;
		currentPhase.clear();
	}
	if (currentPhase == "Execute Order Phase") {
		cout << "Current Phase: " << currentPhase << endl;
		cout << "-------------------------------" << endl;
		currentPhase.clear();
	}
	if (currentPhase == "Execute Order Phase: Deploy Order") {
		cout << "Current Phase: " << currentPhase << endl;
		cout << "-------------------------------" << endl;
		currentPhase.clear();
	}
	if (currentPhase == "Execute Order Phase: Airlift Order") {
		cout << "Current Phase: " << currentPhase << endl;
		cout << "-------------------------------" << endl;
		currentPhase.clear();
	}
	if (currentPhase == "Execute Order Phase: Blockade Order") {
		cout << "Current Phase: " << currentPhase << endl;
		cout << "-------------------------------" << endl;
		currentPhase.clear();
	}
}

GameStatisticsObserver::GameStatisticsObserver(){}

GameStatisticsObserver::GameStatisticsObserver(const GameStatisticsObserver& gso)
{
	gameEngine = gso.gameEngine;
}

GameStatisticsObserver& GameStatisticsObserver::operator=(const GameStatisticsObserver& gso)
{
	gameEngine = gso.gameEngine;
	return *this;
}


GameStatisticsObserver::GameStatisticsObserver(GameEngine* gameEngine)
{
	gameEngine->attach(this);
	this->gameEngine = gameEngine;
}

GameStatisticsObserver::~GameStatisticsObserver()
{
	delete this->gameEngine;
}

void GameStatisticsObserver::update() {

	int totalTerritories = gameEngine->getMap()->listOfTerritories.size();

	cout << "\nCurrent Game Statistics" << endl;
	cout << "-------------------------------" << endl;

	for (int i = 0; i < gameEngine->getPlayers().size(); i++) {
		int playerOwnedTerritory = gameEngine->getPlayers()[i]->getTerritories().size();
		cout << "Player " << gameEngine->getPlayers()[i]->getPlayerNumber() << " owns "
			<< 100.0*playerOwnedTerritory/totalTerritories << "% of the map."<< endl;
		if (playerOwnedTerritory == 0) {
			cout << gameEngine->getPlayers()[i]->getPlayerNumber() << " has been eliminated from the game." << endl;
		}
		if (playerOwnedTerritory == totalTerritories)
		{
			cout << gameEngine->getPlayers()[i]->getPlayerNumber() << " has won the game." << endl;
		}
	}
}

ostream& operator<<(ostream& out, const PhaseObserver& po)
{
	out << "" <<endl;
	return out;
}

ostream& operator<<(ostream& out, const GameStatisticsObserver& gso)
{
	out << "" << endl;
	return out;
}
