#include "save.h"
#include <iostream>
#include <fstream>


void saveGame(const std::vector &map) {
    std::ofstream savefile("save.txt");
    if (savefile.is_open()) { 
        for (int row = 0; row < map.size(); row++) {
            for (int col = 0; col < map[row].size(); col++) {
                if (is_tower) {
                    savefile <<; 
                } else {
                    savefile <<; 
                }
            }
            outputFile << "\n"; // Move to the next line after each row
        }

        outputFile.close();
        
    }
}

void loadGame() {
    
}
