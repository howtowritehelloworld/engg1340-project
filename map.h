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
    enemy* enemy_on_top = NULL;
    struct tower* tower_on_top = NULL;
    tile* next = NULL;

    bool is_path = false;
    bool is_empty();
    bool is_tower();
    bool is_enemy();

    void set_tower_coverage(tile*& path_start);
    void create_new_tower(std::string name, int level, tile*& path_start);
    
};


void readmap(tile map[9][16], int map_num, tile*& path_start);
void spawn_enemy(tile*& path_start, int i, std::vector<std::string> enemies);
void move(tile map[9][16], tile*& path_start, int& killed_enemies, int& health);


#endif // MAP_H
