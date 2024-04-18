#include "tower.h"

using namespace std;
void tower::mage(int tower_level)
{
    name = "Mage";
    color_id = 3;
    icon = 'M';
    level = tower_level;
    cost = 4;
    damage = 2*tower_level;
    attackspeed = 2;
    range = 1;
    type[0] = "AOE"; type[1] = "Ground"; type[2] = "Air";
}

void tower::archer(int tower_level)
{
    name = "Archer";
    color_id = 4;
    icon = 'A';
    level = tower_level;
    cost = 3;
    damage = 3*tower_level;
    attackspeed = 1;
    range = 1;
    type[0] = "Single"; type[1] = "Ground"; type[2] = "Air";     
}

void tower::sniper(int tower_level)
{
    name = "Sniper";
    color_id = 5;
    icon = 's';
    level = tower_level;
    cost = 5;
    damage = 6*tower_level;
    attackspeed = 3;
    range = 2;
    type[0] = "Single"; type[1] = "Ground"; type[2] = "Air"; type[3] = "Camo";
}

void tower::cannon(int tower_level)
{
    name = "Cannon";
    color_id = 6;
    icon = 'C';
    level = tower_level;
    cost = 4;
    damage = 4*tower_level;
    attackspeed = 3;
    range = 1;
    type[0] = "AOE"; type[1] = "Ground";
}

