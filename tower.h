#ifndef TOWER_H
#define TOWER_H

#include <string>
#include <vector>
#include "map.h"
#include "enemy.h"
#include "path.h"


struct tower{
    std::string name;
    char icon;
    int cost;
    int damage;
    int attackspeed;
    int range;
    std::string type[5];
    std::vector<std::pair<int,int>> coordinates;
    std::vector<struct tile*> tiles_covered;

    void mage();
    void archer();
    void sniper();
    void cannon();
    // void check_coverage(pathtile*& pathhead);
};

// void configure_tower(std::string tname, int row, int col, std::vector<tower*>& towers, pathtile*& pathhead);
void print_towers(std::vector<tower*> towers);

#endif
