#include "PlayerStrategies.h"
#include "Order.h"

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

// Issues Orders for this strategy type
//
void AggressivePlayerStrategy::issueOrder(Player* p)
{
	vector<Territory*> attack = p->toAttack();
	vector<Territory*> defend = p->toDefend();

	// deploy all reinforcements to the input Player's strongest Territory
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