#ifndef SAVEGAME_H
#define SAVEGAME_H

#include <iostream>
#include <fstream>
#include <vector>
#include "tower.h"
#include "enemy.h"
#include "path.h"
#include "map.h"

void saveGame(int health, int wave_num, int money, int map_num, std::vector<tower*> towers);
void loadGame(int &health, int &wave_num , int &money, int& map_num, std::vector<tower*> &towers);

#endif
