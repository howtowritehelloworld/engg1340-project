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
    int cost;
    int damage;
    int attackspeed;
    int range;
    std::string type[5];
    std::vector<struct tile*> tiles_covered;

    void mage(int level);
    void archer(int level);
    void sniper(int level);
    void cannon(int level);
};

#endif
