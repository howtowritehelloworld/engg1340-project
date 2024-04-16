#include "enemy.h"
using namespace std;

void enemy::knight()
{
    name = "Knight";
    icon = 'K';
    health = 6;
    weight = 2;
    type[0] = "Ground";
}

void enemy::dragon()
{
    name = "Dragon";
    icon = 'D';
    health = 9;
    weight = 3;
    type[0] = "Air";
}

void enemy::ghost()
{
    name = "Ghost";
    icon = 'G';
    health = 6;
    weight = 3;
    type[0] = "Ground"; type[1] = "Camo";
}
