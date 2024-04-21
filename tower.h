#ifndef TOWER_H
#define TOWER_H

#include <string>
#include <vector>
#include "map.h"
#include "enemy.h"
#include "path.h"


struct tower{
    std::pair<int, int> coordinates;

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

    std::vector<struct path*> path_covered;
    void mage(int level);
    void archer(int level);
    void sniper(int level);
    void cannon(int level);

    void CalculateDamage();
    void set_tower_coverage(struct path*& path_start);
    void create_new_tower(std::string name, int level, path*& path_start, int &money);
    void upgrade_tower(path*& path_start, int &money);
};

#endif
