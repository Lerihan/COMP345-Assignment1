#pragma once
#include "Map.h"
#include <string>


class MapLoader {

private:
	string* dominationFileName;
public:
	MapLoader(); //default constructor
	MapLoader(MapLoader& map); //copy constructor
	MapLoader& operator = (const MapLoader& map); //Assignment operator
	~MapLoader(); //destructor

	MapLoader(string dominationFileName);
	Map* ReadMap(string dominationFileName); // read map file
	virtual Map* GetMap(std::string filePath); //calls ReadMap
	//friend ostream& operator << (ostream& out, const MapLoader *m);
	void ValidateConnectedGraph(Map* map); //validate that map is a connected graph

	vector<string> SplitWords(string s); 
	string FirstComponent(string s);
};

class ConquestFileReader {
	private:
		string* conquestFileName; // name of file
	public:	 
		ConquestFileReader(); //default constructor
		ConquestFileReader(string); //parametrized constructor
		ConquestFileReader(ConquestFileReader& conquestFile); //copy constructor
		ConquestFileReader& operator= (const ConquestFileReader& conquestFile); //assignment operator
		Map* conquestReadMap(string fileName); //reads conquest map format
		string FirstComponent(string s);
		vector<string> SplitWords(string s);
		//friend ostream& operator << (ostream& out, string conquestFileName);
		~ConquestFileReader(); //destructor
};

class ConquestFileReaderAdapter: public MapLoader {
	private:
		ConquestFileReader* conquestReader;
		MapLoader* mapLoader;
		Map* finalMap;
	public:
		virtual Map* GetMap(string filePath); //adapter to choose between domination or conquest map
		ConquestFileReaderAdapter(); //deault constructor
		~ConquestFileReaderAdapter(); //destructor
		ConquestFileReaderAdapter(ConquestFileReaderAdapter& conquestAdapter); //copy constructor
		ConquestFileReaderAdapter& operator=(const ConquestFileReaderAdapter& conquestAdapter); //assignment operator
};