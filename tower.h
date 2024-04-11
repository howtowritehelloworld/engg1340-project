#ifndef TOWER_H
#define TOWER_H

#include <string>
#include <vector>
#include "enemy.h"
#include "path.h"
#include "map.h"

struct tower{

    std::string name;
    char icon;
    int cost;
    int damage;
    int attackspeed;
    int range;
    std::string type[5];
    std::vector<std::pair<int,int>> coordinates;
    std::vector <std::pair<int,int>> tiles_covered;

    void mage();
    void archer();
    void sniper();
    void cannon();
    void check_coverage(pathtile*& pathhead);

};



#endif
