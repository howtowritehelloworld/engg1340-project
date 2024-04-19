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
    type[0] = "AOE"; type[1] = "Ground"; type[2] = "Air"; type[3] = "";
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
    type[0] = "Single"; type[1] = "Ground"; type[2] = "Air"; type[3] = ""; 
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
    type[0] = "AOE"; type[1] = "Ground"; type[2] = ""; type[3] = "";
}

void tower::CalculateDamage(){
    if (type[0] == "AOE"){
        for (int i = 0; i < tiles_covered.size(); i++){
            if (tiles_covered[i]->is_enemy()){
                if (tiles_covered[i]->enemy_on_top->type[0] == "Air" && type[2] == ""){
                    continue;
                }
                else if (tiles_covered[i]->enemy_on_top->type[1] == "Camo" && type[3] == ""){
                    continue;
                }
                tiles_covered[i]->enemy_on_top->health -= damage;
            }
        }
    }
    else if (type[0] == "Single"){
        int last;
        bool no_enemy = true;
        for (int i = 0; i < tiles_covered.size(); i++){
            if (tiles_covered[i]->is_enemy()){
                if (tiles_covered[i]->enemy_on_top->type[0] == "Air" && type[2] == ""){
                }
                else if (tiles_covered[i]->enemy_on_top->type[1] == "Camo" && type[3] == ""){
                }
                else{
                    last = i;
                    no_enemy = false;
                }
            }
        }
        if (no_enemy){
            return;
        }
        tiles_covered[last]->enemy_on_top->health -= damage;
    }
}
