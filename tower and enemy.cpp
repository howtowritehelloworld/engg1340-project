#include <iostream>
#include <string>
using namespace std;

struct tower
{
    string name;
    char icon;
    int cost;
    int damage;
    int attackspeed;
    int range;
    string type[5];  
};

struct enemy
{
    string name;
    char icon;
    int health;
    string type[5];
};

int main()
{
    tower mage;
    mage.name = "Mage";
    mage.icon = 'M';
    mage.cost =  4;
    mage.damage = 2;
    mage.attackspeed = 2;
    mage.range = 1;
    mage.type[0] = "AOE"; mage.type[1] = "Ground"; mage.type[2] = "Air";

    tower archer;
    archer.name = "Archer";
    archer.icon = 'A';
    archer.cost = 3;
    archer.damage = 3;
    archer.attackspeed = 1;
    archer.range = 1;
    archer.type[0] = "Single"; archer.type[1] = "Ground"; archer.type[2] = "Air";

    tower sniper;
    sniper.name = "Sniper";
    sniper.icon = 'S';
    sniper.cost = 5;
    sniper.damage = 6;
    sniper.attackspeed = 3;
    sniper.range = 2;
    sniper.type[0] = "Single"; sniper.type[1] = "Ground"; sniper.type[2] = "Air"; sniper.type[3] = "Camo";

    tower cannon;
    cannon.name = "Cannon";
    cannon.icon = 'C';
    cannon.cost = 4;
    cannon.damage = 4;
    cannon.attackspeed = 3;
    cannon.range = 1;
    cannon.type[0] = "AOE"; cannon.type[1] = "Ground";


    enemy knight;
    knight.name = "Knight";
    knight.icon = 'K';
    knight.health = 14;
    knight.type[0] = "Ground";

    enemy dragon;
    dragon.name = "Dragon";
    dragon.icon = 'D';
    dragon.health = 12;
    dragon.type[0] = "Air";

   enemy ghost;
   ghost.name = "Ghost";
   ghost.icon = 'G';
   ghost.health = 9;
   ghost.type[0] = "Ground"; ghost.type[1] = "Camo";
} 