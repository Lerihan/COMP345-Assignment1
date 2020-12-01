#include "MapLoader.h"
#include <iostream>
#include <string>
#include <any>
using namespace std;

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

 int main() {

     string mapFormat;
     string mapName;
     
     bool isValid = false;
     Map* map=nullptr;
     do {

         cout << "Select conquest or domination map: " << endl;
         cin >> mapFormat;
         cout << "Select the map to play with: ";
         cin >> mapName;
         cout << "Map details: " << endl;
         MapLoader* mapLoader = SelectMapFormat(mapFormat);
         map = mapLoader->GetMap(mapName);
		 cout << *map;
		 map->printAdjTerritory(map->getTerritory(1));
		 map->printAdjTerritory(map->getTerritory(2));
		 map->printAdjTerritory(map->getTerritory(3));
         exit(0);
         
     }
     while (map == NULL || !isValid || mapFormat.empty());

     
     }

     

