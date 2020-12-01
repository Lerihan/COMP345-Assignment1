#include "MapLoader.h"
#include <iostream>
#include <string>
#include <any>
using namespace std;

 /*int main() {
     string dominationMap;
 	MapLoader* mapLoader = new MapLoader();

    cout << "Select the map to play with: " << endl;
    cin >> dominationMap;
    cout << "Map details: " << endl;

 	Map* map = mapLoader->GetMap(dominationMap);
    mapLoader->ValidateConnectedGraph(map);
 	std::cout << endl;

 }*/
//MapLoader* SelectMapFormat(string mapFormat) {
//    if (mapFormat == "conquest") {
//        ConquestFileReaderAdapter* conquestAdapter = new ConquestFileReaderAdapter();
//        return conquestAdapter;
//    }
//    if (mapFormat == "domination") {
//        MapLoader* mapLoader = new MapLoader();
//    }
//    else return nullptr;
//}


 int main() {
    /* string conquestMap;
     ConquestFileReader* conquestMapLoader = new ConquestFileReader();
     cout << "Select the map to play with: " << endl;
     cin >> conquestMap;
     cout << "Map details: " << endl;

     Map* map = conquestMapLoader->read
     ConquestFileReaderAdapter* adapter = new ConquestFileReaderAdapter(conquestMapLoader);
     adapter->ValidateConnectedGraph(map);

     string dominationMap;
 	 MapLoader* mapLoader = new MapLoader();

     cout << "Select the map to play with: " << endl;
     cin >> dominationMap;
     cout << "Map details: " << endl;

     map = mapLoader->ReadMap(dominationMap);
     mapLoader->ValidateConnectedGraph(map);
 	 std::cout << endl;

     std::cout << endl;*/

     string mapFormat;
     string mapName;
     
     bool isValid = false;
     Map* map=nullptr;
     do {

         cout << "Select conquest or domination map: " << endl;
         cin >> mapFormat;
         if (mapFormat == "conquest") {
             ConquestFileReaderAdapter* mapLoader = new ConquestFileReaderAdapter();
             cout << "Select the map to play with: ";
             cin >> mapName;
             cout << "Map details: " << endl;
             map = mapLoader->GetMap(mapName);
             exit(0);
         }
         if (mapFormat == "domination") {
             MapLoader* mapLoader = new MapLoader();
             cout << "Select the map to play with: ";
             cin >> mapName;
             cout << "Map details: " << endl;
             map = mapLoader->GetMap(mapName);
             exit(0);
         }

        /* cout << "Select the map to play with: ";
         cin >> mapName;
         cout << "Map details: " << endl;
         MapLoader* mapLoader = SelectMapFormat(mapFormat);
         map = mapLoader->GetMap(mapName);*/
         
     }
     while (map == NULL || !isValid || mapFormat.empty());

     
     }

     

