#include "PlayerStrategies.h"
#include "Order.h"

PlayerStrategy::~PlayerStrategy() { };

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
AggressivePlayerStrategy::~AggressivePlayerStrategy() { };

// Issues Orders for this strategy type
//
void AggressivePlayerStrategy::issueOrder(Player* p)
{
	vector<Territory*> attack = p->toAttack();
	vector<Territory*> defend = p->toDefend();

	if (p->getReinforcementPool() != 0) // only issue deploy order is reinforcement pool is not empty
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

	/*
	vector<Card*> v = p->getHand()->getCardsInHand();
	if (v.size() != 0)
	{
		//cout << *p << endl;
		cout << "start play" << endl;
		p->getHand()->getCardsInHand().at(0)->play(); // Player plays first Card in their Hand
		cout << "end play" << endl;
		//cout << *p << endl;
		cout << "start begin" << endl;
		p->getHand()->getCardsInHand().erase(p->getHand()->getCardsInHand().begin()); // remove card from player's hand
		cout << "end begin" << endl;
	}
	*/
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
	//benevolent player should not be able to play Bomb & Airlift cards
	//searches through the player's hand and skips over the cards completely
	for (int i = 0; i < p->getHand()->cardsInHand.size(); i++) {				//searching through the benevolent player's hand
		if (p->getHand()->cardsInHand.at(i)->getType() == "BombCard" || p->getHand()->cardsInHand.at(i)->getType() == "AirliftCard")			//check their type to see if the card is a Bomb or Airlift
			p->getHand()->cardsInHand.erase(find(p->getHand()->cardsInHand.begin(), p->getHand()->cardsInHand.end(), p->getHand()->cardsInHand.at(i)));			//erase the card from the player's Hand
			p->getHand()->cardsInHand.at(i)->d->insertBackToDeck(p->getHand()->cardsInHand.at(i));		//insert the card back into its deck
	}

	vector<Territory*> attack = p->toAttack();
	//creates territory vector listing the player's weakest to strongest Territories
	vector<Territory*> defend = p->toDefend();

	//create a variable to count # of total armies, adding in reinforcement pool army
	int totalNumOfArmies = p->getReinforcementPool();		//using an INT for step-down rounding
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

	//neutral player should not be able to play any cards
	//goes through the player's hand and skips over the cards completely
	//for (int i = 0; i < p->getHand()->cardsInHand.size(); i++) {	
	//	p->getHand()->cardsInHand.erase(find(p->getHand()->cardsInHand.begin(), p->getHand()->cardsInHand.end(), p->getHand()->cardsInHand.at(i)));			//erase the card from the player's Hand
	//	p->getHand()->cardsInHand.at(i)->d->insertBackToDeck(p->getHand()->cardsInHand.at(i));		//insert the card back into its deck
	//}

	//vector<Territory*> attack = p->toAttack();
	//vector<Territory*> defend = p->toDefend();
	//does nothing; does not issue orders
}

// Returns the input vector of Territories sorted in increasing number of armies.
vector<Territory*> NeutralPlayerStrategy::toAttack(vector<Territory*> t)
{
	Territory::sortTerritoriesByArmies(t, 1);
	return t; // return the vector
}

// Returns the input vector of Territories sorted in increasing number of armies.
vector<Territory*> NeutralPlayerStrategy::toDefend(vector<Territory*> t)
{
	Territory::sortTerritoriesByArmies(t, 1); //sort Territories by priority 
	return t; // return the sorted vector
}