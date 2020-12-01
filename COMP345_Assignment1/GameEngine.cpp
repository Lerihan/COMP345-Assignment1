#include <iostream>
#include <string>
#include <ctime>
#include <random>
#include <algorithm>
#include <chrono> 
#include "GameEngine.h"

// Default constructor, sets all attributes to default values. They are initialiazed according to game rules in the startGame() method.
GameEngine::GameEngine()
{
	this->map = nullptr;
	vector<Player*> players;
	this->firstPlayer = nullptr;
	this->deck = nullptr;;
	this->numOfPlayers = 0;
	this->observerOn = false;
	this->phase = "empty";
}

// Copy constructor. Creates a deep copy of this GameEngine, and all of its components.
// TODO: how to copy first player
GameEngine::GameEngine(GameEngine& game)
{
	this->map = new Map(*game.map);
	this->players;
	for (int i = 0; i < game.players.size(); i++)
	{
		this->players.push_back(new Player(*game.players.at(i)));
	}
	this->firstPlayer = game.firstPlayer;
	this->deck = new Deck(*game.deck);
	this->numOfPlayers = game.numOfPlayers;
	this->observerOn = game.observerOn;
	this->phase = game.phase;
}

// Destructor
// This should be the only destructor called so it deletes all corresponding components (Map, Players, Deck, etc).
GameEngine::~GameEngine()
{
	delete this->map;
	delete this->deck;
	this->firstPlayer = nullptr;

	for (int i = 0; i < this->players.size(); i++)
	{
		delete this->players[i];
		this->players[i] = nullptr;
	}
	this->players.clear();
}

void GameEngine::startGame()
{
	cout << "Welcome!" << endl;
	cout << endl;

	selectMap();
	cout << endl;

	createComponents();
	cout << endl;

	setObservers();
	cout << endl;

	startupPhase();
}

void GameEngine::startupPhase()
{
	setRandomOrder();
	cout << endl;

	setRandomTerritory();
	cout << endl;

	setInitialArmies();
	cout << endl;
}

Map* GameEngine::getMap()
{
	return map;
}

// Accessor of the GameEngine's players vector
vector<Player*> GameEngine::getPlayers()
{
	return this->players;
}

string GameEngine::getPhase()
{
	return phase;
}

Deck* GameEngine::getDeck()
{
	return this->deck;
}

MapLoader* SelectMapFormat(string mapFormat) {
	if (mapFormat == "conquest") {
		ConquestFileReaderAdapter* conquestAdapter = new ConquestFileReaderAdapter();
		return conquestAdapter;
	}
	if (mapFormat == "domination") {
		MapLoader* mapLoader = new MapLoader();
		return mapLoader;
	}
	else return nullptr;
}

void GameEngine::selectMap()
{
	string dominationMap;
	string mapFormat;
	bool isValid = false;
	MapLoader* mapLoader = new ConquestFileReaderAdapter();

	do
	{
		cout << "Select conquest or domination map format: ";
		cin >> mapFormat;
		mapLoader = SelectMapFormat(mapFormat);
		cout << "Select the map to play with: ";
		cin >> dominationMap;
		if (mapLoader == nullptr) {
			continue;
		}
		else {
			map = mapLoader->GetMap(dominationMap);
		}

		if (map != NULL)
			isValid = map->validate();
		if (map == NULL || !isValid)
		{
			cout << "Map is invalid." << endl;
		}
	} while (map == NULL /*|| isValid*/);

	delete mapLoader;
}

// for now sets all Players to Aggressive strategy
void GameEngine::createComponents()
{
	// how many players
	int playernum = 0;
	do
	{
		cout << "Select the number of players (2-5): ";
		cin >> playernum;

		if (playernum < 2 || playernum > 5)
		{
			cout << "Please enter a valid number of players." << endl;
		}
	} while (playernum < 2 || playernum > 5);
	numOfPlayers = playernum; // set number of players

	// create deck and players with set hand
	this->deck = new Deck();

	Player* p = nullptr; // for readability
	for (int i = 0; i < numOfPlayers; i++)
	{
		p = new Player("aggressive"); // deallocate memory later

		// Draw 5 cards from the deck and place it in the player's hand
		for (int i = 0; i < 5; i++)
		{
			this->deck->draw(p);
		}
		this->players.push_back(p);
	}
	p = nullptr;
}

void GameEngine::setObservers()
{
	char answer;

	do
	{
		cout << "Would you like to turn on the observers ? (y/n): ";
		cin >> answer;

		if (answer == 'y')
		{
			observerOn = true;
			new PhaseObserver(this);
			new GameStatisticsObserver(this);
			cout << "Observers will be on." << endl;
			break;
		}
		else if (answer == 'n')
		{
			observerOn = false;
			cout << "Observers will be off." << endl;
			break;
		}
	} while (answer != 'y' || answer != 'n');
}

void GameEngine::setInitialArmies()
{
	// set specific number
	int numOfArmies;
	switch (numOfPlayers)
	{
	case 2:
		numOfArmies = 40;
		break;
	case 3:
		numOfArmies = 35;
		break;
	case 4:
		numOfArmies = 30;
		break;
	case 5:
		numOfArmies = 25;
		break;
	}

	//attach number to all players
	for (int i = 0; i < players.size(); i++)
	{
		players.at(i)->addReinforcements(numOfArmies);
	}
}

// shuffle code from: http://www.cplusplus.com/reference/algorithm/shuffle/
void GameEngine::setRandomOrder()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(players.begin(), players.end(), std::default_random_engine(seed));

	std::cout << "The playing order is: ";
	for (int i = 0; i < numOfPlayers; i++)
	{
		cout << players[i]->getPlayerNumber() << " ";
	}
	cout << endl;
}

void GameEngine::setRandomTerritory()
{
	vector<Territory*> territoriesCopy = map->listOfTerritories;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(territoriesCopy.begin(), territoriesCopy.end(), std::default_random_engine(seed));

	int turn = 0;
	for (int i = 0; i < territoriesCopy.size(); i++)
	{
		territoriesCopy[i]->setOwner(players[turn]); // set the owner of this Territory to be the Player it is assigned to
		players[turn]->addTerritory(territoriesCopy[i]);
		turn++;

		if (turn > (players.size() - 1))
			turn = 0;
	}
}

// Function that controls the main game
// Loops through 3 phases
void GameEngine::mainGameLoop()
{
	int rounds = 0; // number of rounds the game lasted
	Player* winner = nullptr;
	while (winner == nullptr)
	{
		if (rounds == 100) { // end game if it reaches deadlock state
			// change number if we find it takes more rounds to actually end the game
			cout << "A stalemate has been reached. The game will now exit." << endl;
			return;
		}
		kickPlayers(); // check if a Player owns no Territories; if yes, kick them from the game
		winner = checkWinner(); // check if a Player has won the game
		if (winner != nullptr)
		{
			break;
		}

		cout << "========" << endl;
		cout << "Round " << ++rounds << endl;
		cout << "========" << endl << endl;

		// Reinforcement phase
		cout << "Reinforcement phase:" << endl;
		cout << "--------------------" << endl;
		for (int i = 0; i < this->players.size(); i++)
		{
			if (!this->players.at(i)->isEliminated())
			{
				reinforcementPhase(players.at(i));
			}
		}
		cout << endl;
		cout << *(this->players[0]) << endl;

		// Issuing Orders phase
		cout << "Issuing orders phase:" << endl;
		cout << "---------------------" << endl;
		for (int i = 0; i < this->players.size(); i++)
		{
			if (!this->players[i]->isEliminated())
			{
				issueOrdersPhase(players[i]);
			}
		}
		cout << endl;
		cout << *(this->players[0]) << endl;

		// Orders execution phase
		cout << "Orders execution phase:" << endl;
		cout << "-----------------------" << endl;
		for (int i = 0; i < this->players.size(); i++)
		{
			if (!this->players[i]->isEliminated())
			{
				executeOrdersPhase(players[i]);
			}
		}
		cout << endl;
		cout << *(this->players.at(0)) << endl;
		cout << *(this->players.at(1)) << endl;

		//notify();
	}
	endGamePhase(winner);
}

// Determines how many armies to add to the input Player's reinforcement pool at the start of each reinforcement phase
void GameEngine::reinforcementPhase(Player* currPlayer)
{
	phase = "Reinforcement Phase";
	notify();

	int newArmies = 3; // minimum number of new armies to assign to Player

	// check if Player owns whole Continent
	int bonusArmies = 0; // if Player gets bonus reinforcements from owning whole Continent
	Continent* currContinent = nullptr; // for readability
	for (int i = 0; i < map->listOfContinents.size(); i++)
	{
		currContinent = map->listOfContinents[i];
		if (currContinent->controlsContinent(currPlayer))
			bonusArmies += currContinent->armyvalue;
	}
	currContinent = nullptr;

	// Player gets number of armies equal to their number of Territories / 3, unless this number is less than 3
	if ((currPlayer->getTerritories().size() / 3) > newArmies)
		newArmies = currPlayer->getTerritories().size() / 3;

	cout << "Player " << currPlayer->getPlayerNumber() << " will receive " << newArmies << " new reinforcements "
		<< "and " << bonusArmies << " bonus reinforcements." << endl;
	currPlayer->addReinforcements(newArmies + bonusArmies); // add armies
}

// Prompts user for Order to be issued and calls issueOrder()
// TODO: generalize to call methodsof Player's strategy class; I think this method should pretty much be empty by the end
// of the assignment
void GameEngine::issueOrdersPhase(Player* currPlayer) {

	phase = "Issue Order Phase";
	currPlayer->issueOrder();
	for (int i = 0; i < currPlayer->getOrders().size(); i++) {
		if (currPlayer->getOrders().at(i)->getType() == "Advance" || currPlayer->getOrders().at(i)->getType() == "Airlift")
			currPlayer->setAttacked(true);
	}
}

void GameEngine::executeOrdersPhase(Player* currPlayer)
{
	phase = "Execute Order Phase";
	notify();
	// execute deploy orders
	for (int i = 0; i < currPlayer->getOrders().size(); i++)
	{
		if (!currPlayer->getOrders()[i]->isExecuted())
		{
			if (currPlayer->getOrders()[i]->getType() == "Deploy")
			{
				cout << "Player " << currPlayer->getPlayerNumber() << " has executed a " << currPlayer->getOrders()[i]->getType() << " order." << endl;
				phase = "Execute Order Phase: Deploy Order";
				notify();
				currPlayer->getOrders()[i]->execute();
			}
		}
	}

	// execute airlift orders
	for (int i = 0; i < currPlayer->getOrders().size(); i++)
	{
		if (!currPlayer->getOrders()[i]->isExecuted())
		{
			if (currPlayer->getOrders()[i]->getType() == "Airlift")
			{
				cout << "Player " << currPlayer->getPlayerNumber() << " has executed a " << currPlayer->getOrders()[i]->getType() << " order." << endl;
				phase = "Execute Order Phase: Airlift Order";
				notify();
				currPlayer->getOrders()[i]->execute();
			}
		}
	}

	// execute blockade orders
	for (int i = 0; i < currPlayer->getOrders().size(); i++)
	{
		if (!currPlayer->getOrders()[i]->isExecuted())
		{
			if (currPlayer->getOrders()[i]->getType() == "Blockade")
			{
				cout << "Player " << currPlayer->getPlayerNumber() << " has executed a " << currPlayer->getOrders()[i]->getType() << " order." << endl;
				phase = "Execute Order Phase: Blockade Order";
				notify();
				currPlayer->getOrders()[i]->execute();
			}
		}
	}

	// execute all other orders in the order they appear in the OrdersList
	for (int i = 0; i < currPlayer->getOrders().size(); i++)
	{
		if (!currPlayer->getOrders().at(i)->isExecuted())
		{
			cout << "Player " << currPlayer->getPlayerNumber() << " has executed a " << currPlayer->getOrders().at(i)->getType() << " order." << endl;
			currPlayer->getOrders().at(i)->execute();
		}
	}

	if (currPlayer->hasAttacked()) {
		this->deck->draw(currPlayer);
		currPlayer->setAttacked(false);
	}		


	// TODO: should we delete the execute orders here, or just leave them as executed?
}

// Checks if a Player has lost the game.
// a Player loses if he does not control any Territories
void GameEngine::kickPlayers()
{
	Player* currPlayer = nullptr; // for readability
	for (int i = 0; i < this->getPlayers().size(); i++)
	{
		currPlayer = this->players[i];
		if (currPlayer->getTerritories().size() <= 0) // if Player has no Territories kick them from the game
		{
			cout << "Player " << currPlayer->getPlayerNumber() << " controls no more Territories. They are removed from the game." << endl;

			// put the losing Player's Cards back in the Deck
			Hand* hand = currPlayer->getHand(); // for readability
			for (int j = 0; j < hand->getCardsInHand().size(); j++)
			{
				this->deck->insertBackToDeck(hand->getCardsInHand()[j]); // put each Card back in the Deck
				hand->getCardsInHand()[j] = nullptr;
			}
			hand->getCardsInHand().clear(); // Player's Hand size is now 0
			hand = nullptr;
			currPlayer->eliminatePlayer(); // sets isEliminated to true
		}
	}
	currPlayer = nullptr;
}

// Checks if a Player has won the game; if so return that winning Player, else return nullptr
// a Player has won if they conrol all the Territories on the Map
Player* GameEngine::checkWinner()
{
	int players = 0; // number of players still in the game
	Player* winner = nullptr;
	for (int i = 0; i < this->getPlayers().size(); i++)
	{
		if (!this->getPlayers().at(i)->isEliminated())
		{
			players++;
			winner = this->getPlayers().at(i);
		}
	}

	if (players == 1) {
		return winner;
	}
	return nullptr;
}

// Launches end of game winner message
void GameEngine::endGamePhase(Player* winner)
{
	cout << "########################################" << endl;
	cout << "            Winner!!!" << endl;
	cout << "########################################" << endl;
	cout << "Congratulations, Player " << winner->getPlayerNumber() << "! You won!" << endl;
	cout << "Restart the program to play again." << endl;
}

// Assignment operator, performs shallow copy only.
// TODO: how to copy first player
GameEngine& GameEngine::operator =(const GameEngine& game)
{
	if (&game != this)
	{
		// assign new values
		this->map = game.map;
		this->players;
		for (Player* p : game.players)
		{
			this->players.push_back(p);
		}
		this->firstPlayer = game.firstPlayer;
		this->deck = game.deck;
		this->numOfPlayers = game.numOfPlayers;
		this->observerOn = game.observerOn;
		this->phase = game.phase;
	}
	return *this;
}

// Stream insertion operator returns map name and number of players
ostream& operator <<(ostream& strm, GameEngine& game)
{
	strm << "This game was played with " << game.map->name << ".map and " << game.numOfPlayers << " players." << endl;
	return strm;
}