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

enum Phase {Reinforcement, IssueOrder, ExecuteOrer};

class GameEngine;

class PhaseObserver : public Observer {
	public:
		PhaseObserver(GameEngine* gameEngine);
		void update() override;

	private:
		int currentPlayerNum;
		enum Phase {Reinforcement, IssuingOrder, OrdersExecution, NoPhase};
		Phase currentPhase = Phase::NoPhase;
		GameEngine* subject;
};

class GameStatisticsObserver : public Observer {
	public:
		GameStatisticsObserver(GameEngine* gameEngine);
		void update() override;
	private:
		string showGameStats;
		GameEngine* subject;
};