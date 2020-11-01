#include "GameObservers.h"
#include <iostream>
#include <list>

using namespace std;

Subject::Subject() {
	observers = new list<Observer*>;
}

Subject::~Subject(){
	delete observers;
}

void Subject::attach(Observer* observer) {
	observers->push_back(observer);
}

void Subject::detach(Observer* detach_observer) {
}

void Subject::notify() {
	for (Observer* observer : *observers) {
		observer->update();
	}
}