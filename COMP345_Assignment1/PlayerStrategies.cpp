#include "PlayerStrategies.h"

AggressivePlayerStrategy::AggressivePlayerStrategy() { }

void AggressivePlayerStrategy::issueOrder(Order* o)
{

}

// Returns the input vector of Territories sorted in increeasing number of armies.
vector<Territory*> AggressivePlayerStrategy::toAttack(vector<Territory*> t)
{
	Territory::sortTerritoriesByArmies(t, 1); // sort Territories by priority
	return t; // return the sorted vector
}

// Returns the input vector of Territories sorted in increasing number of armies.
vector<Territory*> AggressivePlayerStrategy::toDefend(vector<Territory*> t)
{
	Territory::sortTerritoriesByArmies(t, 1); // sort Territories by priority
	return t; // return the sorted vector
}