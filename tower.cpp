#include "tower.h"

using namespace std;
void tower::mage(int level)
{
    name = "Mage";
    color_id = 3;
    icon = 'M';
    cost = 4;
    damage = 2*level;
    attackspeed = 2;
    range = 1;
    type[0] = "AOE"; type[1] = "Ground"; type[2] = "Air"; type[3] = NULL;
}

void tower::archer(int level)
{
    name = "Archer";
    color_id = 4;
    icon = 'A';
    cost = 3;
    damage = 3*level;
    attackspeed = 1;
    range = 1;
    type[0] = "Single"; type[1] = "Ground"; type[2] = "Air"; type[3] = NULL; 
}

void tower::sniper(int level)
{
    name = "Sniper";
    color_id = 5;
    icon = 's';
    cost = 5;
    damage = 6*level;
    attackspeed = 3;
    range = 2;
    type[0] = "Single"; type[1] = "Ground"; type[2] = "Air"; type[3] = "Camo";
}

void tower::cannon(int level)
{
    name = "Cannon";
    color_id = 6;
    icon = 'C';
    cost = 4;
    damage = 4*level;
    attackspeed = 3;
    range = 1;
    type[0] = "AOE"; type[1] = "Ground"; type[2] = NULL; type[3] = NULL;
}

