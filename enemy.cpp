#include <string>
#include "enemy.h"
using namespace std;

void enemy::knight()
{
    name = "Knight";
    icon = 'K';
    health = 14;
    type[0] = "Ground";
}

void enemy::dragon()
{
    name = "Dragon";
    icon = 'D';
    health = 12;
    type[0] = "Air";
}

void enemy::ghost()
{
    name = "Ghost";
    icon = 'G';
    health = 9;
    type[0] = "Ground"; type[1] = "Camo";
}