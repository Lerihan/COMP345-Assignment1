#include "MapLoader.h"
#include <iostream>
#include <string>

 int main() {
     string dominationMap;
 	MapLoader* mapLoader = new MapLoader();

    cout << "Select the map to play with: " << endl;
    cin >> dominationMap;
    cout << "Map details: " << endl;

 	Map* map = mapLoader->GetMap(dominationMap);
    mapLoader->ValidateConnectedGraph(map);
 	std::cout << endl;

 }