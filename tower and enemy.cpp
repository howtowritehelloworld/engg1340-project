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

    void mage()
    {
        name = "Mage";
        icon = 'M';
        cost = 4;
        damage = 2;
        attackspeed = 2;
        range = 1;
        type[0] = "AOE"; type[1] = "Ground"; type[2] = "Air";
    }

    void archer()
    {
        name = "Archer";
        icon = 'A';
        cost = 3;
        damage = 3;
        attackspeed = 1;
        range = 1;
        type[0] = "Single"; type[1] = "Ground"; type[2] = "Air";     
    }

    void sniper()
    {
        name = "Sniper";
        icon = 'S';
        cost = 5;
        damage = 6;
        attackspeed = 3;
        range = 2;
        type[0] = "Single"; type[1] = "Ground"; type[2] = "Air"; type[3] = "Camo";
    }

    void cannon()
    {
        name = "Cannon";
        icon = 'C';
        cost = 4;
        damage = 4;
        attackspeed = 3;
        range = 1;
        type[0] = "AOE"; type[1] = "Ground";
    }

};

struct enemy
{
    string name;
    char icon;
    int health;
    string type[5];

    void knight()
    {
        name = "Knight";
        icon = 'K';
        health = 14;
        type[0] = "Ground";
    }

    void dragon()
    {
        name = "Dragon";
        icon = 'D';
        health = 12;
        type[0] = "Air";
    }

    void ghost()
    {
        name = "Ghost";
        icon = 'G';
        health = 9;
        type[0] = "Ground"; type[1] ="Camo";
    }

};
