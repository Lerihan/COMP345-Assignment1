#pragma once
#include "Map.h"
#include <string>


class MapLoader {

private:
	string* dominationFileName = NULL;
	Continent* createContinent(std::string line);
	//Country* createCountry(std::string line);
	Map* finalMap = nullptr;

public:
	MapLoader();
	MapLoader(string dominationFileName);
	void ReadMap(string dominationFileName);
	Map* GetMap(std::string filePath);

};