#pragma once
#include <list>
#include <vector>

using namespace std;

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

class PhaseObserver : public Observer {
	public:
		PhaseObserver();
		PhaseObserver(GameEngine* gameEngine);
		~PhaseObserver();
		void update() override;

	private:
		int currentPlayerNum;
		enum Phase {Reinforcement, IssuingOrder, OrdersExecution, NoPhase};
		GameEngine* gameEngine;
};

class GameStatisticsObserver : public Observer {
	public:
		GameStatisticsObserver();
		GameStatisticsObserver(GameEngine* gameEngine);
		~GameStatisticsObserver();
		void update() override;
	private:
		GameEngine* gameEngine;
};