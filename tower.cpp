#include "tower.h"

using namespace std;
void tower::mage(int tower_level)
{
    name = "Mage";
    color_id = 3;
    icon = 'M';
    level = tower_level;
    cost = 40;
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
    cost = 20;
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
    cost = 50;
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
    cost = 30;
    damage = 4*tower_level;
    attackspeed = 3;
    range = 1;
    type[0] = "AOE"; type[1] = "Ground"; type[2] = ""; type[3] = "";
}

void tower::CalculateDamage(){
    if (cd > 0){
        cd--;
        return;
    }

    if (type[0] == "AOE"){
        for (int i = 0; i < path_covered.size(); i++){
            if (path_covered[i]-> enemy_on_top != NULL){
                if (path_covered[i]->enemy_on_top->type[0] == "Air" && type[2] == ""){
                    continue;
                }
                else if (path_covered[i]->enemy_on_top->type[1] == "Camo" && type[3] == ""){
                    continue;
                }
                path_covered[i]->enemy_on_top->health -= damage;
                cd = attackspeed;
            }
        }
    }
    else if (type[0] == "Single"){
        int last;
        bool no_enemy = true;
        for (int i = 0; i < path_covered.size(); i++){
            if (path_covered[i]->enemy_on_top != NULL){
                if (path_covered[i]->enemy_on_top->type[0] == "Air" && type[2] == ""){
                }
                else if (path_covered[i]->enemy_on_top->type[1] == "Camo" && type[3] == ""){
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
        path_covered[last]->enemy_on_top->health -= damage;
        cd = attackspeed;
    }
}

void tower::set_tower_coverage(path*& path_start){
    path* current = path_start;
    while (current != NULL){
        int row = current->coordinates.first;
        int col = current->coordinates.second;
        if (abs(row - coordinates.first) <= range && abs(col - coordinates.second) <= range){
            path_covered.push_back(current);
        }
        current = current->next;
    }
}

void tower::sample_tower(string tower_name){
    if (tower_name == "Mage")
    {
        mage(1);
    }
    else if (tower_name == "Archer")
    {
        archer(1);
    }
    else if (tower_name == "Sniper")
    {
        sniper(1);
    }
    else if (tower_name == "Cannon")
    {
        cannon(1);
    }
}

void tower::create_new_tower(string name, int level, path*& path_start, int &money){
    if (name == "Mage" && money >= 40)
    {
        money -= 40;
        mage(level);
    }
    else if (name == "Archer" && money >= 20)
    {
        money -= 20;
        archer(level);
    }
    else if (name == "Sniper" && money >= 50)
    {
        money -= 50;
        sniper(level);
    }
    else if (name == "Cannon" && money >= 30)
    {
        money -= 30;
        cannon(level);
    }
    set_tower_coverage(path_start);
}

void tower::upgrade_tower(path*& path_start, int &money){
    create_new_tower(name, level+1, path_start, money);
}