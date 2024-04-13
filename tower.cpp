#include "tower.h"

using namespace std;
void tower::mage()
{
    name = "Mage";
    icon = 'M';
    cost = 4;
    damage = 2;
    attackspeed = 2;
    range = 1;
    type[0] = "AOE"; type[1] = "Ground"; type[2] = "Air";
}

void tower::archer()
{
    name = "Archer";
    icon = 'A';
    cost = 3;
    damage = 3;
    attackspeed = 1;
    range = 1;
    type[0] = "Single"; type[1] = "Ground"; type[2] = "Air";     
}

void tower::sniper()
{
    name = "Sniper";
    icon = 's';
    cost = 5;
    damage = 6;
    attackspeed = 3;
    range = 2;
    type[0] = "Single"; type[1] = "Ground"; type[2] = "Air"; type[3] = "Camo";
}

void tower::cannon()
{
    name = "Cannon";
    icon = 'C';
    cost = 4;
    damage = 4;
    attackspeed = 3;
    range = 1;
    type[0] = "AOE"; type[1] = "Ground";
}

