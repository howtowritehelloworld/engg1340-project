#ifndef MAP_H
#define MAP_H

#include <iostream>
#include "enemy.h"
#include "path.h"

void printmap(char map[9][16]);
void updatemap(char map[9][16], pathtile*& pathhead);

#endif // MAP_H
