#include "MapLoader.h"
#include <iostream>
#include <string>

 //int main() {
 //    string dominationMap;
 //	MapLoader* mapLoader = new MapLoader();

 //   cout << "Select the map to play with: " << endl;
 //   cin >> dominationMap;
 //   cout << "Map details: " << endl;

 //	Map* map = mapLoader->GetMap(dominationMap);
 //   mapLoader->ValidateConnectedGraph(map);
 //	std::cout << endl;

 //}

 int main() {
     string conquestMap;
     ConquestFileReader* conquestMapLoader = new ConquestFileReader();
     cout << "Select the map to play with: " << endl;
     cin >> conquestMap;
     cout << "Map details: " << endl;

     Map* mapLoader = conquestMapLoader->GetMapConquest(conquestMap);
     ConquestFileReaderAdapter* adapter = new ConquestFileReaderAdapter(conquestMapLoader);
     adapter->ValidateConnectedGraph(mapLoader);
     std::cout << endl;
 }
