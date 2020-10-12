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
    
	if (map->validate()) {
		cout << "Map is a connected graph.";
	}
	else {
		cout << "Map is not a connected graph.";
	}

    std::cout << endl;
}
