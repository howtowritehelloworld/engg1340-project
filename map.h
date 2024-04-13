#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <fstream>
#include <vector>
#include "tower.h"
#include "enemy.h"
#include "path.h"

struct tile{
    std::pair<int,int> coordinates;
    char icon;
    int color_id;
    enemy* enemy_on_top = NULL;
    tower* tower_on_top = NULL;
    tile* next = NULL;

    bool is_path = false;
    bool is_empty();
    bool is_tower();
    bool is_enemy();
    
};



void printmap(tile map[9][16]);
// void updatemap(char map[9][16], pathtile*& pathhead, std::vector<struct tower*> towers);
void readmap(tile map[9][16], int map_num);

#endif // MAP_H
