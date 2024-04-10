#include <string>
using namespace std;

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