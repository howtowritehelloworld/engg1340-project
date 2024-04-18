#ifndef TOWER_H
#define TOWER_H

#include <string>
#include <vector>
#include "map.h"
#include "enemy.h"
#include "path.h"


struct tower{
    std::string name;
    int color_id;
    char icon;
    int level;
    int cost;
    int damage;
    int attackspeed;
    int cd = 0;
    int range;
    std::string type[5];
    std::vector<struct tile*> tiles_covered;

    void mage(int tower_level);
    void archer(int tower_level);
    void sniper(int tower_level);
    void cannon(int tower_level);
};

#endif
