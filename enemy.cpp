#include "enemy.h"
using namespace std;

void enemy::knight(int level)
{
    name = "Knight";
    icon = 'K';
    health = 6*level;
    weight = 2*level;
    money = 2*level;
    type[0] = "Ground"; type[1] = "";
}

void enemy::dragon(int level)
{
    name = "Dragon";
    icon = 'D';
    health = 9*level;
    weight = 4*level;
    money = 4*level;
    type[0] = "Air"; type[1] = "";
}

void enemy::vampire(int level)
{
    name = "Vampire";
    icon = 'V';
    health = 6*level;
    weight = 4*level;
    money = 4*level;
    type[0] = "Air"; type[1] = "Camo";
}

void enemy::ghost(int level)
{
    name = "Ghost";
    icon = 'G';
    health = 6*level;
    weight = 3*level;
    money = 3*level;
    type[0] = "Ground"; type[1] = "Camo";
}
