#include "PlayerStrategies.h"

AggressivePlayerStrategy::AggressivePlayerStrategy() { }

void AggressivePlayerStrategy::issueOrder(Order* o)
{

}

vector<Territory*> AggressivePlayerStrategy::toAttack(vector<Territory*> t)
{
	vector<Territory*> toAttack;
	for (int i = 0; i < t.size(); i++)
	{
		toAttack.push_back(t.at(i));
	}
	Territory::sortTerritoriesByArmies(toAttack, 1); // sort Territories by priority
	return toAttack; // return the sorted vector
}

vector<Territory*> AggressivePlayerStrategy::toDefend(vector<Territory*> t)
{
	vector<Territory*> toDefend;
	for (int i = 0; i < t.size(); i++)
	{
		toDefend.push_back(t.at(i));
	}
	Territory::sortTerritoriesByArmies(toDefend, 0); // sort Territories by priority
	return toDefend; // return the sorted vector
}