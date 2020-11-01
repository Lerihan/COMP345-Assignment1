#pragma once
#include <list>
#include <vector>

using namespace std;

class Observer {
	public:
		Observer(Subject* model);
		~Observer();
		virtual void update() = 0;
};

class Subject {
	public:
		void detach(Observer* observer);
		void attach(Observer* observer);
		void notify();

		Subject();
		~Subject();
	private:
		vector<Observer*> observers;
};