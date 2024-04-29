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
    void create_tower(std::string tower_name, int level);
    void upgrade_tower();
};

void attack_all(std::vector<struct tower*> towers);

#endif
