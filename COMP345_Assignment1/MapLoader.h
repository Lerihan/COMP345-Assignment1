#pragma once
#include "Map.h"
#include <string>


class MapLoader {

private:
	string* dominationFileName;
	Map* finalMap;
  
public:
	MapLoader(); //default constructor
	MapLoader(MapLoader& map); //copy constructor
	MapLoader& operator = (const MapLoader& map); //Assignment operator
	~MapLoader(); //destructor

	MapLoader(string dominationFileName);
	void ReadMap(string dominationFileName);
	Map* GetMap(std::string filePath);
	friend istream& operator >> (istream& in, string dominationMap);
	void ValidateConnectedGraph(Map* map);

	vector<string> SplitWords(string s);
	string FirstComponent(string s);
};