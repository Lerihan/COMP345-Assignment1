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

	// deploy all reinforcements to the input Player's stronges Territory
	p->getOrdersList()->add(new Deploy(p, defend.at(0), p->getReinforcementPool()));
	p->removeReinforcements(p->getReinforcementPool()); // empty Player's reinforcement pool

	// advance to other Territories
	// issue one order for each of the Player's Territories that
	bool found = false; // need to break out of if statement adn inner for loop
	for (int i = 0; i < defend.size(); i++)
	{
		found = false;
		for (int j = 0; j < defend.at(i)->listOfAdjTerritories.size(); j++)
		{
			if (defend.at(i)->listOfAdjTerritories.at(j)->getOwner() != p)
			{ // if this is enemy Territory then advance to it
				p->getOrdersList()->add(new Advance( // add new Advance order to attack
					p, defend.at(i), defend.at(i)->listOfAdjTerritories.at(j), defend.at(i)->numberOfArmies));
				found = true; // also break out of inner for loop
				found = true; // also break out of inner for loop
			}
			if (found)
				break;
		}
	}
	cout << p->getOrders().size() << endl;
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
	vector<Territory*> attack = p->toAttack();
	//creates territory vector listing the player's weakest to strongest Territories
	vector<Territory*> defend = p->toDefend();

	//create a variable to count # of total armies, adding in reinforcement pool army
	int totalNumOfArmies = p->getReinforcementPool();
	//loop to add in # of armies for each territory of the player
	for (int i = 0; i < defend.size(); i++) {
		totalNumOfArmies = totalNumOfArmies + defend.at(i)->numberOfArmies;
	}
	//variable to know how much armies should be evenly spread
	int idealNumOfArmy = totalNumOfArmies / defend.size();	
	//for each territory, add in (from reinforcement pool) a number of army to match idealNumOfArmy
	for (int i = 0; i < defend.size(); i++) {
		//if territory's army has less than idealNumOfArmy, simply add in from reinforcement pool
		if (idealNumOfArmy > defend.at(i)->numberOfArmies) {
			int numOfArmyNeeded = idealNumOfArmy - defend.at(i)->numberOfArmies;		//calculate how much army does the player need to equaly distribute the reinforcement
			p->getOrdersList()->add(new Deploy(p, defend.at(i), numOfArmyNeeded));		//deploys the needed amount of soldiers for the territory to reach the needed number
			p->removeReinforcements(numOfArmyNeeded);									//remove that amount from the reinforcement pool
		}
		//if territory's army is greater than idealNumOfArmy, remove excess and add to reinforcement pool
		else if (idealNumOfArmy < defend.at(i)->numberOfArmies) {
			int numOfExtraArmy =  defend.at(i)->numberOfArmies - idealNumOfArmy;		//calculate how much army does the player need to equaly distribute the reinforcement
			defend.at(i)->removeTroops(numOfExtraArmy);									//removes troops from the Territory
			p->getOrdersList()->add(new Deploy(p, defend.at(i), 0));					//makes a deploy order with 0 reinforcements
			p->addReinforcements(numOfExtraArmy);										//add that amount to the reinforcement pool
		}
	}
}

// Returns the input vector of Territories sorted in increasing number of armies.
vector<Territory*> BenevolentPlayerStrategy::toAttack(vector<Territory*> t)
{
	Territory::sortTerritoriesByArmies(t, 1);
	return t; // return the vector
}

// Returns the input vector of Territories sorted in increasing number of armies.
vector<Territory*> BenevolentPlayerStrategy::toDefend(vector<Territory*> t)
{
	Territory::sortTerritoriesByArmies(t, 1); //sort Territories by priority 
	return t; // return the sorted vector
}


// ###############################
// NeutralPlayerStrategy
// ###############################
NeutralPlayerStrategy::NeutralPlayerStrategy() { }

void NeutralPlayerStrategy::issueOrder(Player* p)
{
	vector<Territory*> attack = p->toAttack();
	vector<Territory*> defend = p->toDefend();
	//does nothing; does not issue orders
}

// Returns the input vector of Territories sorted in increasing number of armies.
vector<Territory*> BenevolentPlayerStrategy::toAttack(vector<Territory*> t)
{
	Territory::sortTerritoriesByArmies(t, 1);
	return t; // return the vector
}

// Returns the input vector of Territories sorted in increasing number of armies.
vector<Territory*> BenevolentPlayerStrategy::toDefend(vector<Territory*> t)
{
	Territory::sortTerritoriesByArmies(t, 1); //sort Territories by priority 
	return t; // return the sorted vector
}