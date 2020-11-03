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
	ReadMap(filePath);
	return finalMap;
}

void MapLoader::ReadMap(string dominationFileName) {
	try {
		Map map;
		string line = "";
		bool hasContinent = false;
		bool hasCountries = false;
		bool hasBorders = false;

		map.name = FirstComponent(dominationFileName);

		ifstream readFile;
		readFile.open(dominationFileName);

		if (!readFile) {
			cout << "Can't read file" << endl;
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
						Continent* newContinent = new Continent(index, attributes[0], stoi(attributes[1])); //stoi converts str to int
						//continents->push_back(newContinent);
						map.addContinent(newContinent);
						cout << "New Continent: " << line << endl;
						index++;
						getline(readFile, line);
					}
					hasContinent = true;
				}

				if (line.find("[countries]") == 0) {
					getline(readFile, line);

					if (hasContinent) {
						while (line.find("[borders]") != 0) {
							if (line == "")
								break;

							//Split line to access different attributes of territories
							vector<string> attributes = SplitWords(line); //index name continent x y
							Territory* newCountry = new Territory(stoi(attributes[0]), attributes[1]);
							map.listOfContinents[stoi(attributes[2]) - 1]->addTerritory(newCountry); //add territory to continent
							map.addTerritory(newCountry); //add territory in full list of territories (in map)
							//countries->push_back(newCountry);
							//this->addFinalContinent->addTerritory(newCountry); //does this do anything ?
							//getline(readFile, line);
							cout << "New Country: " << line << endl;
							getline(readFile, line);
						}
					}
					hasCountries = true;
				}

				if (line.find("[borders]") == 0) {
					getline(readFile, line);

					if (hasCountries && hasContinent) {
						while (!line.empty()) {
							if (line == "")
								break;

							vector<string> adjCountries = SplitWords(line); //countryid adj1 adj2 adj3 ...
							Territory* t0 = map.getTerritory(stoi(adjCountries[0]));
							for (int i = 1; i < adjCountries.size(); i++)
							{
								Territory* t = map.getTerritory(stoi(adjCountries[i]));
								map.addAdjTerritory(t0, t);
							}

							cout << "New Border: " << line << endl;
							getline(readFile, line);
						}
					}				
					hasBorders = true;
				}
			}

			if (hasContinent && hasCountries && hasBorders) {
				cout << "Map File is valid" << endl;
				this->finalMap = &map;
				readFile.close();
			}
			else {
				cout << "Map File is invalid" << endl;
				readFile.close();
			}
		}
	}
	catch (const std::exception& e) {
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
	try {
		if (map == NULL) {
			cout << "Map is not a connected graph.";
		}
		else {
			map->validate();
			//cout << *map << endl;
			cout << "Map is  a connected graph.";
		}
	}
	catch (const std::exception& e) {
		cout << e.what() << endl;
	}

	
}
