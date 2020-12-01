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
	Map* ReadMap(string dominationFileName);
	virtual Map* GetMap(std::string filePath);
	friend istream& operator >> (istream& in, string dominationMap);
	void ValidateConnectedGraph(Map* map);

	vector<string> SplitWords(string s);
	string FirstComponent(string s);
};

class ConquestFileReader {
	private:
		string* conquestFileName;
	public:	
		ConquestFileReader();
		ConquestFileReader(string);
		ConquestFileReader(ConquestFileReader& conquestFile);
		ConquestFileReader& operator= (const ConquestFileReader& conquestFile);
		Map* conquestReadMap(string fileName);
		string FirstComponent(string s);
		vector<string> SplitWords(string s);
		~ConquestFileReader();
};

class ConquestFileReaderAdapter: public MapLoader {
	private:
		ConquestFileReader* conquestReader;
		MapLoader* mapLoader;
		Map* finalMap;
	public:
		virtual Map* GetMap(string filePath);
		ConquestFileReaderAdapter();
		~ConquestFileReaderAdapter();
		ConquestFileReaderAdapter(ConquestFileReaderAdapter& conquestAdapter);
		ConquestFileReaderAdapter& operator=(const ConquestFileReaderAdapter& conquestAdapter);
};