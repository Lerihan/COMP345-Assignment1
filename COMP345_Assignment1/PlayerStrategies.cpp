#include "PlayerStrategies.h"
#include "Order.h"

// ###############################
// HumanPlayerStrategy
// ###############################
HumanPlayerStrategy::HumanPlayerStrategy() { }

void HumanPlayerStrategy::issueOrder(Player* p)
{

}

// Returns the input vector of Territories sorted in increeasing number of armies.
vector<Territory*> HumanPlayerStrategy::toAttack(vector<Territory*> t)
{
	return t; // return the sorted vector
}

// Returns the input vector of Territories sorted in increasing number of armies.
vector<Territory*> HumanPlayerStrategy::toDefend(vector<Territory*> t)
{
	return t; // return the sorted vector
}


// ###############################
// AggressivePlayerStrategy
// ###############################
AggressivePlayerStrategy::AggressivePlayerStrategy() { }

// Issues Orders for this strategy type
//
void AggressivePlayerStrategy::issueOrder(Player* p)
{
	vector<Territory*> attack = p->toAttack();
	vector<Territory*> defend = p->toDefend();

	if (p->getReinforcementPool() != 0) // only issue deploy orer is reinforcement pool is not empty
	{
		// deploy all reinforcements to the input Player's strongest Territory
		p->getOrdersList()->add(new Deploy(p, defend.at(0), p->getReinforcementPool()));
		p->removeReinforcements(p->getReinforcementPool()); // empty Player's reinforcement pool
	}

	// advance to other Territories
	// issue one order for each of the Player's Territories that has an adjacent enemey Territory
	bool found = false; // needed to break out of if statement and inner for loop
	Territory* currTerritory = nullptr; // for readability
	Territory* adjTerritory = nullptr; // for readability
	for (int i = 0; i < defend.size(); i++)
	{
		found = false;
		currTerritory = defend.at(i); // for readability
		for (int j = 0; j < currTerritory->listOfAdjTerritories.size(); j++)
		{
			adjTerritory = currTerritory->listOfAdjTerritories.at(j); // for readability
			if (adjTerritory->getOwner() != p)
			{ // if this is an enemy Territory then advance to it
				p->getOrdersList()->add(new Advance(p, currTerritory, adjTerritory, currTerritory->numberOfArmies)); // add new Advance order to attack
				found = true; // also break out of inner for loop
			}
			if (found)
				break; // break out of inner for loop
		}
	}
	currTerritory = nullptr;
	adjTerritory = nullptr;

	p->getHand()->getCardsInHand().at(0)->play(); // Player plays first Card in their Hand
}

// Returns the input vector of Territories sorted in increeasing number of armies.
vector<Territory*> AggressivePlayerStrategy::toAttack(vector<Territory*> t)
{
	Territory::sortTerritoriesByArmies(t, 1); // sort Territories by priority
	return t; // return the sorted vector
}

// Returns the input vector of Territories sorted in decreasing number of armies.
vector<Territory*> AggressivePlayerStrategy::toDefend(vector<Territory*> t)
{
	Territory::sortTerritoriesByArmies(t, 0); // sort Territories by priority
	return t; // return the sorted vector
}


// ###############################
// BenevolentPlayerStrategy
// ###############################
BenevolentPlayerStrategy::BenevolentPlayerStrategy() { }

void BenevolentPlayerStrategy::issueOrder(Player* p)
{

}

// Returns the input vector of Territories sorted in increeasing number of armies.
vector<Territory*> BenevolentPlayerStrategy::toAttack(vector<Territory*> t)
{
	return t; // return the sorted vector
}

// Returns the input vector of Territories sorted in increasing number of armies.
vector<Territory*> BenevolentPlayerStrategy::toDefend(vector<Territory*> t)
{
	return t; // return the sorted vector
}


// ###############################
// NeutralPlayerStrategy
// ###############################
NeutralPlayerStrategy::NeutralPlayerStrategy() { }

void NeutralPlayerStrategy::issueOrder(Player* p)
{

}

// Returns the input vector of Territories sorted in increeasing number of armies.
vector<Territory*> NeutralPlayerStrategy::toAttack(vector<Territory*> t)
{
	return t; // return the sorted vector
}

// Returns the input vector of Territories sorted in increasing number of armies.
vector<Territory*> NeutralPlayerStrategy::toDefend(vector<Territory*> t)
{
	return t; // return the sorted vector
}