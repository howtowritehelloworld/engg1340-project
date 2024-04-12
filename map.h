#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include "tower.h"
#include "enemy.h"
#include "path.h"


void printmap(char map[9][16]);
void updatemap(char map[9][16], pathtile*& pathhead, std::vector<struct tower*> towers);

#endif // MAP_H
