#include "PlayerStrategies.h"
#include "Order.h"

PlayerStrategy::~PlayerStrategy() { };

// ###############################
// HumanPlayerStrategy
// ###############################
HumanPlayerStrategy::HumanPlayerStrategy() { }

void HumanPlayerStrategy::issueOrder(Player* p)
{
	vector<Territory*> attack = p->toAttack();
	vector<Territory*> defend = p->toDefend();

	// Add (Deploy) armies to Owned Territories From Reinforcement Pool (Until Empty)
	int pool = p->getReinforcementPool();
	string territoryName;
	Territory* toDeploy = defend.at(0);
	int numToDeploy = 0;
	
	bool found = false;
	while (pool > 0)
	{
		cout << endl << *p << endl;
		cout << "You still have " << pool << " armies in your reinforcement pool." << endl;
		cout << "Deploy armies from your reinforcement pool to your owned territories until you don't have anymore." << endl;

		while (!found)
		{
			cout << "Which Territory would you like to Deploy to ? (Case-Sensitive): ";
			cin >> territoryName;

			for (int i = 0; i < defend.size(); i++)
			{
				if (defend.at(i)->name == territoryName) // found
				{
					found = true;
					toDeploy = defend.at(i);
					do
					{
						cout << "How many armies should be Deployed ?: ";
						cin >> numToDeploy;

						if (numToDeploy <= 0)
							cout << "You cannot deploy a negative/zero number of armies." << endl;
						if (numToDeploy > pool)
							cout << "You do not have enough armies in your reinforcement pool." << endl;
					} while (numToDeploy <= 0 || numToDeploy > pool);
					break; // get out of for loop once found
				}
			}

			if (!found)
				cout << "This territory does not exist or belong to you." << endl;
			else
			{
				found = false; // set it back to false to avoid infinite loop
				break;
			}
		}

		// when numToDeploy is valid, do the action
		p->getOrdersList()->add(new Deploy(p, toDeploy, numToDeploy)); // add deploy order !
		p->removeReinforcements(numToDeploy); // NOTE: Already done in Deploy()
		pool -= numToDeploy; // remove from local variable too
		cout << "Player " << p->getPlayerNumber() << " will deploy " << numToDeploy << " armies to " << toDeploy->name << endl;
	}

	// Advance Order toDefend
	int numToDefend = 0;
	int numToMove = 0;
	Territory* srcToDefend = defend.at(0);
	Territory* targetToDefend = defend.at(0);
	string source = "";
	string target = "";
	found = false;

	cout << endl << *p << endl;
	do
	{
		cout << "How many times would you like to Defend a Territory? (1-3): ";
		cin >> numToDefend;
	} while (numToDefend < 0 || numToDefend > 3);

	for (int i = 0; i < numToDefend; i++)
	{
		do
		{
			cout << "Which Territory would you like to Defend? [" << i + 1 << "] (Case-Sensitive): ";
			cin >> target;

			for (int j = 0; j < defend.size(); j++)
			{
				if (defend.at(j)->name == target) // found target
				{
					targetToDefend = defend.at(j);
					cout << "The source Territory needs to be adjacent to " << target << " and must belong to you!" << endl;
					targetToDefend->printAdjTerritoryOwned();

					do
					{
						cout << "Which Territory would you like to take armies from? [" << i + 1 << "] (Case-Sensitive): ";
						cin >> source;

						if (!targetToDefend->isAdjacent(source))
							cout << "Territory " << source << " is not adjacent to " << target << endl;
						else if (targetToDefend->getOwnerOfAdjacent(source) != p)
							cout << "Territory " << source << " does not belong to you." << endl;
						else
						{
							do
							{
								cout << "Territory " << source << " has " << srcToDefend->numberOfArmies << " armies." << endl;
								cout << "How many Armies would you like to move? [" << i + 1 << "]: ";
								cin >> numToMove;

								if (numToMove <= 0 || numToMove > srcToDefend->numberOfArmies)
								{
									cout << "Number of Armies is below zero or higher than what's available." << endl;
								}
							} while (numToMove <= 0 || numToMove > targetToDefend->numberOfArmies);
						}
					} while (!targetToDefend->isAdjacent(source) || targetToDefend->getOwnerOfAdjacent(source) != p);
					found = true; // found source and target
					srcToDefend = targetToDefend->getAdjTerritoryByName(source);
					p->getOrdersList()->add(new Advance(p, srcToDefend, targetToDefend, numToMove));
					cout << "Player " << p->getPlayerNumber() << " will advance " << numToMove << " armies from "
						<< source << " to " << target << " for defense." << endl;
					break;
				}
			}

			if (!found)
				cout << "This territory does not exist or belong to you." << endl;
			else
			{
				found = false;
				break;
			}
		} while (!found);
	}

	// Advance Order toAttack
	int numToAttack = 0;
	numToMove = 0;
	Territory* srcToAttack = defend.at(0);
	Territory* targetToAttack = attack.at(0);
	source = "";
	target = "";
	found = false;

	cout << endl << *p << endl;
	do
	{
		cout << "How many times would you like to Attack a Territory? (1-3): ";
		cin >> numToAttack;
	} while (numToAttack < 0 || numToAttack > 3);

	for (int i = 0; i < numToAttack; i++)
	{
		do
		{
			cout << "Which Territory would you like to take armies from? [" << i + 1 << "] (Case-Sensitive): ";
			cin >> source;
			
			for (int j = 0; j < defend.size(); j++)
			{
				if (defend.at(j)->name == source) // found target
				{
					srcToAttack = defend.at(j);
					cout << "The target Territory needs to be adjacent to " << source << " and must NOT belong to you!" << endl;
					srcToAttack->printAdjTerritoryNotOwned();

					do
					{
						cout << "Which Territory would you like to Attack? [" << i + 1 << "] (Case-Sensitive): ";
						cin >> target;

						if (!srcToAttack->isAdjacent(target))
							cout << "Territory " << target << " is not adjacent to " << source << endl;
						else if (srcToAttack->getOwnerOfAdjacent(target) == p)
							cout << "Territory " << target << " belongs to you." << endl;
						else
						{
							do
							{
								cout << "Territory " << source << " has " << srcToAttack->numberOfArmies << " armies." << endl;
								cout << "How many Armies would you like to move? [" << i + 1 << "]: ";
								cin >> numToMove;

								if (numToMove <= 0 || numToMove > srcToAttack->numberOfArmies)
									cout << "Number of Armies is below zero or higher than what's available." << endl;

							} while (numToMove <= 0 || numToMove > targetToAttack->numberOfArmies);
						}
					} while (!srcToAttack->isAdjacent(target) || srcToAttack->getOwnerOfAdjacent(target) == p);
					found = true; // found source and target
					targetToAttack = srcToAttack->getAdjTerritoryByName(target);
					p->getOrdersList()->add(new Advance(p, srcToAttack, targetToAttack, numToMove));
					cout << "Player " << p->getPlayerNumber() << " will advance " << numToMove << " armies from "
						<< source << " to " << target << " for attack." << endl;
					break;
				}
			}

			if (!found)
				cout << "This territory does not exist or belong to you." << endl;
			else
			{
				found = false;
				break;
			}
		} while (!found);
	}

	// Use one card
	Card* card = NULL;
	int cardInput;
	string cardType;
	cout << endl << *p << endl;

	do
	{
		do
		{
			cout << "Which card would you like to play? (Airlift (1), Bomb (2), Blockade (3), Diplomacy (4), Reinforcement (5)): ";
			cin >> cardInput;
		} while (cardInput < 1 || cardInput > 5);
	
		switch (cardInput)
		{
		case 1:
			cardType = "AirliftCard";
			break;
		case 2:
			cardType = "BombCard";
			break;
		case 3:
			cardType = "BlockadeCard";
			break;
		case 4:
			cardType = "DiplomacyCard";
			break;
		case 5:
			cardType = "ReinforcementCard";
			break;
		}
		card = p->getCard(cardType);

		if (card != NULL)
			card->play();
	} while (card == NULL);
}

// Returns the input vector of Territories sorted in increeasing number of armies.
vector<Territory*> HumanPlayerStrategy::toAttack(vector<Territory*> t)
{
	Territory::sortTerritoriesByArmies(t, 1); // sort Territories by priority
	return t; // return the sorted vector
}

// Returns the input vector of Territories sorted in increasing number of armies.
vector<Territory*> HumanPlayerStrategy::toDefend(vector<Territory*> t)
{
	Territory::sortTerritoriesByArmies(t, 0); // sort Territories by priority
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

	 // ==================== CONFLICT:  the following is from passiveandneutral branch 
	vector<Card*> v = p->getHand()->getCardsInHand();
	if (v.size() != 0)
	{
		p->getHand()->play(); // Player plays first Card in their Hand		
	}
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
	//creates territory vector listing the player's weakest to strongest Territories
	vector<Territory*> defend = p->toDefend();

	Territory* currTerritory = nullptr;													//for readability

	//create a variable to count # of total armies, adding in reinforcement pool army
	int totalNumOfArmies = p->getReinforcementPool();									//for readability, using an INT for step-down rounding
	//loop to add in # of armies for each territory of the player
	for (int i = 0; i < defend.size(); i++) {
		totalNumOfArmies = totalNumOfArmies + defend.at(i)->numberOfArmies;
	}
	//variable to know how much armies should be evenly spread
	int idealNumOfArmy = totalNumOfArmies / defend.size();	
	
	//for each territory, add in (from reinforcement pool) a number of army to match idealNumOfArmy
	for (int i = 0; i < defend.size(); i++) {
		currTerritory = defend.at(i);
		//if territory's army has less than idealNumOfArmy, simply add in from reinforcement pool
		if (idealNumOfArmy > currTerritory->numberOfArmies) {
			int numOfArmyNeeded = idealNumOfArmy - currTerritory->numberOfArmies;		//calculate how much army does the player need to equaly distribute the reinforcement
			p->getOrdersList()->add(new Deploy(p, currTerritory, numOfArmyNeeded));		//deploys the needed amount of soldiers for the territory to reach the needed number
			p->removeReinforcements(numOfArmyNeeded);									//remove that amount from the reinforcement pool
		}
		//if territory's army is greater than idealNumOfArmy, remove excess and add to reinforcement pool
		else if (idealNumOfArmy < currTerritory->numberOfArmies) {
			int numOfExtraArmy = currTerritory->numberOfArmies - idealNumOfArmy;		//calculate how much army does the player need to equaly distribute the reinforcement
			currTerritory->removeTroops(numOfExtraArmy);									//removes troops from the Territory
			p->getOrdersList()->add(new Deploy(p, currTerritory, 0));					//makes a deploy order with 0 reinforcements
			p->addReinforcements(numOfExtraArmy);										//add that amount to the reinforcement pool
		}
	}
	currTerritory = nullptr;

	//benevolent player should not be able to play Bomb & Airlift cards. If either type is found, skips the card
	vector<Card*> v = p->getHand()->getCardsInHand();			//for readability
	if (v.size() != 0) {
		if (v.at(0)->getType() == "BombCard" )			//check their type to see if the card is a Bomb or Airlift
		{			
			cout << "Benevolent Player can not play Bomb Cards.";
			v.at(0)->d->insertBackToDeck(v.at(0));				//insert the card back into its deck
			p->getHand()->deleteFirstCard();
		}			
		else if (v.at(0)->getType() == "AirliftCard") {
			cout << "Benevolent Player can not play Airlift Cards.";
			v.at(0)->d->insertBackToDeck(v.at(0));				//insert the card back into its deck
			p->getHand()->deleteFirstCard();						//erase the card from the player's Hand
		}
		else
		{
			p->getHand()->play();							//plays the first card of the player's hand
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