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
    int color_id;
    enemy* enemy_on_top = NULL;
    struct tower* tower_on_top = NULL;
    tile* next = NULL;

    bool is_path = false;
    bool is_empty();
    bool is_tower();
    bool is_enemy();

    void set_tower_coverage(tile*& path_start);
    void create_new_tower(std::string name, tile*& path_start);
    
};



void printmap(tile map[9][16]);
// void updatemap(char map[9][16], pathtile*& pathhead, std::vector<struct tower*> towers);
void readmap(tile map[9][16], int map_num, tile*& path_start);
void move(tile map[9][16], tile*& path_start);

#endif // MAP_H
