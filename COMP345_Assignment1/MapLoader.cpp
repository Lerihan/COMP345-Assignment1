#include "MapLoader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

MapLoader::MapLoader() {
	this->dominationFileName = NULL;
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
		//Map map;
		string line = "";
		bool hasContinent = false;
		bool hasCountries = false;
		bool hasBorders = false;
		std::vector<Continent*>* continents = new std::vector<Continent*>();
		//std::vector<Country*>* countries = new std::vector<Country*>();
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
						continents->push_back(newContinent);
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
						/*Continent* newCountry = new Country(line);
						continents->push_back(newCountry);
						getline(readFile, line);*/
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
