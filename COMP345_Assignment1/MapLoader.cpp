#include "MapLoader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

//Default Constructor
MapLoader::MapLoader() {
	this->dominationFileName = NULL;
}

//Copy Constructor
MapLoader::MapLoader(MapLoader &map){
	MapLoader::MapLoader();
}

//Assignment operator
MapLoader& MapLoader:: operator = (const MapLoader &map){
	return *this;
}

//Destructor
MapLoader::~MapLoader(){
	delete this;
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
		Continent continent;
		Map map;
		this->finalMap = &map;
		this->addFinalContinent = &continent;
		string line = "";
		bool hasContinent = false;
		bool hasCountries = false;
		bool hasBorders = false;
		std::vector<Continent*>* continents = new std::vector<Continent*>();
		std::vector<Territory*>* countries = new std::vector<Territory*>();
		int index = 1;
		ifstream readFile;
		readFile.open(dominationFileName);

		if (!readFile) {
			cout << "Can't read file" << endl;
		}
		else {
			while (getline(readFile, line))
			{
				if (line.find("[continents]") == 0) {
					getline(readFile, line);

					while (line.find("[countries]") != 0) {
						if (line == "")
							break;
						Continent* newContinent = new Continent(line);
						//continents->push_back(newContinent);
						this->finalMap->addContinent(newContinent);
						cout << "New Continent: " << line << endl;
						getline(readFile, line);
					}
					hasContinent = true;
				}

				if (line.find("[countries]") == 0) {
					getline(readFile, line);
					while (line.find("[borders]") != 0) {
						if (line == "")
							break;
						Territory* newCountry = new Territory(line);
						//countries->push_back(newCountry);
						this->addFinalContinent->addTerritory(newCountry);
						getline(readFile, line);
						cout << "New Country: " << line << endl;
						getline(readFile, line);
					}

					hasCountries = true;
				}

				if (line.find("[borders]") == 0) {
					getline(readFile, line);
					while (!line.empty()) {
						if (line == "")
							break;
						cout << "New Border: " << line << endl;
						getline(readFile, line);
					}
					hasBorders = true;
				}
			}
			if (hasContinent && hasCountries && hasBorders) {
				cout << "Map File is valid" << endl;
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
