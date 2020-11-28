#include "MapLoader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

//Default Constructor
MapLoader::MapLoader() {
	this->dominationFileName = NULL;
}

//Copy Constructor
MapLoader::MapLoader(MapLoader &map){
	dominationFileName = map.dominationFileName;
}

//Assignment operator
MapLoader& MapLoader:: operator = (const MapLoader &map) {
	return *this;
}

//Destructor
MapLoader::~MapLoader() {
	delete dominationFileName;
}

MapLoader::MapLoader(string dominationFileName) {
	this->dominationFileName = new std::string(dominationFileName);
}

Map* MapLoader::GetMap(string filePath) {
	return ReadMap(filePath);
}

	//Map map;
Map* MapLoader::ReadMap(string dominationFileName) {
	try {
		Map* map = new Map();
		Continent* newContinent;
		Territory* newCountry;
		string line = "";
		bool hasContinent = false;
		bool hasCountries = false;
		bool hasBorders = false;

		map->name = FirstComponent(dominationFileName);

		ifstream readFile;
		readFile.open(dominationFileName);

		if (!readFile) {
			cout << "Can't read file" << endl;
			return NULL;
		}
		else {
			while (getline(readFile, line))
			{
				//Reads continents
				if (line.find("[continents]") == 0) {
					getline(readFile, line);

					int index = 1;
					while (line.find("[countries]") != 0) {
						if (line == "")
							break;

						//Split line to access different attributes of continents
						vector<string> attributes = SplitWords(line);
						newContinent = new Continent(index, attributes[0], stoi(attributes[1])); //stoi converts str to int
						map->addContinent(newContinent);
						index++;
						//cout << "New Continent: " << line << endl;
						getline(readFile, line);
					}
					hasContinent = true;
				}

				if (line.find("[countries]") == 0 && hasContinent) {
					getline(readFile, line);
					while (line.find("[borders]") != 0) {
						if (line == "")
							break;

						//Split line to access different attributes of territories
						vector<string> attributes = SplitWords(line); //index name continent x y
						newCountry = new Territory(stoi(attributes[0]), attributes[1], stoi(attributes[2])); //id name continentid
						map->listOfContinents[stoi(attributes[2]) - 1]->addTerritory(newCountry); //add territory to continent
						map->addTerritory(newCountry); //add territory in full list of territories (in map)

						//cout << "New Country: " << line << endl;
						getline(readFile, line);
					}

					hasCountries = true;
				}

				if (line.find("[borders]") == 0 && hasContinent && hasCountries) {
					getline(readFile, line);
					while (!line.empty()) {
						if (line == "")
							break;

						vector<string> adjCountries = SplitWords(line); //countryid adj1 adj2 adj3 ...
						Territory* t0 = map->getTerritory(stoi(adjCountries[0]));
						for (int i = 1; i < adjCountries.size(); i++)
						{
							Territory* t = map->getTerritory(stoi(adjCountries[i]));
							map->addAdjTerritory(t0, t);
						}
						//cout << "New Border: " << line << endl;
						getline(readFile, line);
					}
					hasBorders = true;
				}
			}

			if (hasContinent && hasCountries && hasBorders) {
				cout << "Map File is valid" << endl;
				this->finalMap = map;
				readFile.close();
				return map;
				delete newCountry; //deallocate memory (not sure if it does it correctly)
				delete newContinent;
				delete map; 
			}
			else {
				cout << "Map File is invalid" << endl;
				readFile.close();
				return NULL;
			}
		}
	}
	catch (const std::exception& e) {
		return NULL;
		cout << e.what() << endl;
	}
}

//Code from http://www.cplusplus.com/forum/beginner/99171/
vector<string> MapLoader::SplitWords(string s)
{
	istringstream iss(s);
	vector<string> v;
	while (iss >> s)
	{
		v.push_back(s);
	}
	return v;
}

string MapLoader::FirstComponent(string s)
{
	s[0] = toupper(s[0]);
	size_t pos = s.find('.');
	return s.substr(0, pos);
}

string ConquestFileReader::FirstComponent(string s)
{
	s[0] = toupper(s[0]);
	size_t pos = s.find('.');
	return s.substr(0, pos);
}

vector<string> ConquestFileReader::SplitWords(string s)
{
	istringstream iss(s);
	vector<string> v;
	while (iss >> s)
	{
		v.push_back(s);
	}
	return v;
}

istream& operator>>(istream& in, string dominationMap)
{	
	cout << "Enter map name: ";
	in >> dominationMap;
	cout << "Map details";
	return in;
}

//Validate map is a connected graph
void MapLoader::ValidateConnectedGraph(Map* map)
{
	if (map->validate()) {
		cout << "Map is a connected graph.";
	}
	else {
		cout << "Map is not a connected graph.";
	}
}

ConquestFileReader::ConquestFileReader()
{
	this->conquestFileName = NULL;
}

ConquestFileReader::ConquestFileReader(string conquestFileName)
{
	this->conquestFileName = new std::string(conquestFileName);;
}

ConquestFileReader::ConquestFileReader(ConquestFileReader& conquestFile)
{
	conquestFileName = conquestFile.conquestFileName;
}

Map* ConquestFileReader::GetMapConquest(string filePath) {
	return conquestReadMap(filePath);
}

Map* ConquestFileReader::conquestReadMap(string fileName)
{
	try {
		Map* map = new Map();
		Continent* newContinent;
		Territory* newCountry;
		string line = "";
		bool hasContinent = false;
		bool hasCountries = false;
		bool hasBorders = false;
		int continentId = 1;
		int territoryId = 1;

		//map->name = FirstComponent(fileName);

		ifstream readFile;
		readFile.open(fileName);

		if (!readFile) {
			cout << "Can't read file" << endl;
			return NULL;
		}
		else {
			while (getline(readFile, line))
			{
				//Reads continents
				if (line.find("[Continents]") == 0) {
					getline(readFile, line);

					while (line.find("[Territories]") != 0) {
						if (line == "")
							break;

						//Split line to access different attributes of continents
						string continentName = line.substr(0, line.find("="));
						int armyValue = line[line.size() - 1];
						newContinent = new Continent(continentId, continentName, armyValue); //stoi converts str to int
						map->addContinent(newContinent);
						continentId++;
						cout << "New Continent: " << line << endl;
						getline(readFile, line);
					}
					hasContinent = true;
				}

				if (line.find("[Territories]") == 0 && hasContinent) {
					getline(readFile, line);

					while (!line.empty()) {
						if (line == "")
							break;

						//Split line to access different attributes of territories
						vector<string> attributes = SplitWords(line); //index name continent x y
						string territoryName = line.substr(0, line.find(","));

						newCountry = new Territory(territoryId, territoryName, continentId); //id name continentid
						//map->listOfContinents[double(continentId) - 1]->addTerritory(newCountry); //add territory to continent

						map->addTerritory(newCountry); //add territory in full list of territories (in map)
						territoryId++;
						continentId++;
						cout << "New Country: " << line << endl;
						getline(readFile, line);
					}

					hasCountries = true;
				}
			}

			readFile.close();

			while (getline(readFile, line)) {
				if (line.find("[Territories]") == 0) {
					getline(readFile, line);
					while (!line.empty()) {
								vector<string> adjCountries = SplitWords(line); //countryid adj1 adj2 adj3 ...
								Territory* t0 = map->getTerritory(stoi(adjCountries[0]));
								for (int i = 1; i < adjCountries.size(); i++)
								{
									Territory* t = map->getTerritory(stoi(adjCountries[i]));
									map->addAdjTerritory(t0, t);
								}
								cout << "New Border: " << line << endl;
						getline(readFile, line);
					}
				}
			}

			if (hasContinent && hasCountries) {
				cout << "Map File is valid" << endl;
				//this->finalMap = map;
				readFile.close();
				return map;
				delete newCountry; //deallocate memory (not sure if it does it correctly)
				delete newContinent;
				delete map;
			}
			else {
				cout << "Map File is invalid" << endl;
				readFile.close();
				return NULL;
			}
		}
	}
	catch (const std::exception& e) {
		return NULL;
		cout << e.what() << endl;
	}
}

ConquestFileReader::~ConquestFileReader()
{
	delete conquestFileName;
}

ConquestFileReaderAdapter::ConquestFileReaderAdapter()
{
	this->conquestReader = conquestReader;
	this->mapLoader = mapLoader;
}

ConquestFileReaderAdapter::~ConquestFileReaderAdapter()
{
	delete conquestReader;
	delete mapLoader;
}

ConquestFileReaderAdapter::ConquestFileReaderAdapter(ConquestFileReaderAdapter& conquestAdapter)
{
	conquestReader = conquestAdapter.conquestReader;
	mapLoader = conquestAdapter.mapLoader;
}

ConquestFileReaderAdapter& ConquestFileReaderAdapter::operator=(const ConquestFileReaderAdapter& conquestAdapter)
{
	conquestReader = conquestAdapter.conquestReader;
	mapLoader = conquestAdapter.mapLoader;
	return *this;
}

ConquestFileReaderAdapter::ConquestFileReaderAdapter(MapLoader* reader)
{
	mapLoader = reader;
	conquestReader = NULL;
}

ConquestFileReaderAdapter::ConquestFileReaderAdapter(ConquestFileReader* reader)
{
	conquestReader = reader;
}


Map* ConquestFileReaderAdapter::ReadMap(string& fileName)
{
	return conquestReader->conquestReadMap(fileName);
}
