#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <fstream>
#include <vector>
#include "tower.h"
#include "enemy.h"
#include "path.h"

void readmap(int map[9][16], int map_num, path*& path_start);
void spawn_enemy(path*& path_start, int i, std::vector<std::string> enemies);
void move(path*& path_start, int& killed_enemies, int& health);
void attack_all(std::vector<struct tower*> towers);


#endif // MAP_H
