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

class PhaseObserver : public Observer {
	public:
		void update() override;
	private:
		int currentPlayerNum;
		enum Phase {Reinforcement, IssuingOrder, OrdersExecution, NoPhase};
		Phase currentPhase = Phase::NoPhase;
};

class GameStatisticsObserver : public Observer {
	public:
		void update() override;
	private:
		string showGameStats;
};