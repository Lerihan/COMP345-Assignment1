#include "GameObservers.h"
#include <iostream>
#include <list>

using namespace std;

class Subject {
	public:
		Subject() {};
		virtual ~Subject() {};
		virtual void attach(Observer*);
		virtual void detach(Observer*);
		virtual void notify();
	private:
		vector<Observer*> observers;
};


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