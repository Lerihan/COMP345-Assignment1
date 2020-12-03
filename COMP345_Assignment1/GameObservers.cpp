#include "GameEngine.h"
#include <iostream>
#include <list>

using namespace std;

//implement a method that attaches a new observer to the list of observers in Subject class
void Subject::attach(Observer* observer) {
	observers.push_back(observer);
}

//detach an observer if it is a valid one in the observer list.
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

//print information about the player and the phase currently being played
void Subject::notify() {
	for (Observer* observer : observers) {
		observer->update();
	}
}

//default constructor of PhaseObserver
PhaseObserver::PhaseObserver(){
}

//copy constructor that creates a deep copy from the attributes of copied PhaseObserver object
PhaseObserver::PhaseObserver(const PhaseObserver& po)
{
	gameEngine = po.gameEngine;
	currentPlayerNum = po.currentPlayerNum;
}

//assignment operator
PhaseObserver& PhaseObserver::operator=(const PhaseObserver& po)
{
	gameEngine = po.gameEngine;
	currentPlayerNum = po.currentPlayerNum;

	return *this;
}

//attach the gameEngine to the current gameEngine
PhaseObserver::PhaseObserver(GameEngine* gameEngine)
{
	gameEngine->attach(this);
	this->gameEngine = gameEngine;
}

//deletion operator
PhaseObserver::~PhaseObserver()
{
	delete this->gameEngine;
}

//update method that prints out the current phase being played
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

//default operator for GameStatisticsObserver class
GameStatisticsObserver::GameStatisticsObserver(){}

//its copy constructor that creates a deep copy
GameStatisticsObserver::GameStatisticsObserver(const GameStatisticsObserver& gso)
{
	gameEngine = gso.gameEngine;
}

//assignment operator
GameStatisticsObserver& GameStatisticsObserver::operator=(const GameStatisticsObserver& gso)
{
	gameEngine = gso.gameEngine;
	return *this;
}

//similarly, attach the gameEngine to the current gameEngine
GameStatisticsObserver::GameStatisticsObserver(GameEngine* gameEngine)
{
	gameEngine->attach(this);
	this->gameEngine = gameEngine;
}

//deletion operator
GameStatisticsObserver::~GameStatisticsObserver()
{
	delete this->gameEngine;
}

//update method that also prints the game statistics, about players, territories percentage owned, and who own the game.
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

//stream insertion operator for PhaseObserver class
ostream& operator<<(ostream& out, const PhaseObserver& po)
{
	out << "" <<endl;
	return out;
}

//stream insertion operator for GameStatisticsObserver class
ostream& operator<<(ostream& out, const GameStatisticsObserver& gso)
{
	out << "" << endl;
	return out;
}
