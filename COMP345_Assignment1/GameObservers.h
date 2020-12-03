#pragma once
#include <list>
#include <vector>

using namespace std;

//Observer parent class
class Observer {
	public:
		virtual void update() = 0;
};

class Subject {
	public:
		void detach(Observer* observer);
		void attach(Observer* observer);
		void notify();
	private:
		vector<Observer*> observers;
};

class GameEngine;

//inherit from Observer parent class
class PhaseObserver : public Observer {
	public:
		PhaseObserver();
		PhaseObserver(const PhaseObserver& po);
		PhaseObserver& operator = (const PhaseObserver& po);
		PhaseObserver(GameEngine* gameEngine);
		friend ostream& operator << (ostream& out, const PhaseObserver& po);
		~PhaseObserver();
		void update() override;

	private:
		int currentPlayerNum;
		GameEngine* gameEngine;
};

//inherit from Observer parent class
class GameStatisticsObserver : public Observer {
	public:
		GameStatisticsObserver();
		GameStatisticsObserver(const GameStatisticsObserver& gso); 
		GameStatisticsObserver& operator = (const GameStatisticsObserver& gso); 
		GameStatisticsObserver(GameEngine* gameEngine);
		friend ostream& operator << (ostream& out, const GameStatisticsObserver& gso);
		~GameStatisticsObserver();
		void update() override;
	private:
		GameEngine* gameEngine;
};