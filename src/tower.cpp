#include "tower.h"

using namespace std;
void tower::mage(int tower_level)
{

    name = "Mage";
    color_id = 3;
    icon = 'M';
    level = tower_level;
    cost = 40 * level;
    damage = 3 * tower_level;
    attackspeed = 2;
    range = 1;
    type[0] = "AOE";
    type[1] = "Ground";
    type[2] = "Air";
    type[3] = "Camo";
}

void tower::archer(int tower_level)
{
    /*

    Input:
    tower_level : Level of the tower to be created

    Process:
    Sets the attributes for an archer tower according to tower_level

    Output:
    Modified struct tower

    */
    name = "Archer";
    color_id = 4;
    icon = 'A';
    level = tower_level;
    cost = 20 * level;
    damage = 3 * tower_level;
    attackspeed = 1;
    range = 1;
    type[0] = "Single";
    type[1] = "Ground";
    type[2] = "Air";
    type[3] = "";
}

void tower::sniper(int tower_level)
{

    /*

    Input:
    tower_level : Level of the tower to be created

    Process:
    Sets the attributes for a sniper tower according to tower_level

    Output:
    Modified struct tower

    */
    name = "Sniper";
    color_id = 5;
    icon = 's';
    level = tower_level;
    cost = 50 * level;
    damage = 6 * tower_level;
    attackspeed = 3;
    range = 2;
    type[0] = "Single";
    type[1] = "Ground";
    type[2] = "Air";
    type[3] = "Camo";
}

void tower::cannon(int tower_level)
{
    /*

    Input:
    tower_level : Level of the tower to be created

    Process:
    Sets the attributes for a cannon tower according to tower_level

    Output:
    Modified struct tower

    */
    name = "Cannon";
    color_id = 6;
    icon = 'C';
    level = tower_level;
    cost = 30 * level;
    damage = 5 * tower_level;
    attackspeed = 3;
    range = 1;
    type[0] = "AOE";
    type[1] = "Ground";
    type[2] = "";
    type[3] = "";
}

void tower::CalculateDamage()
{
    /*

    Input:

    Process:
    Attack enemies
        AOE : Attacks all enemies in range
        Single : Attacks the enemy furthest away from start
    Once attacked, set cooldown to attackspeed
    During cooldown, tower cannot attack.

    Output:
    Modified health of enemies

    */

    if (cd > 0)
    {
        cd--;
        return;
    }

    if (type[0] == "AOE")
    {
        bool attacked = false;
        for (int i = 0; i < path_covered.size(); i++)
        {
            if (path_covered[i]->enemy_on_top != NULL)
            {
                if (path_covered[i]->enemy_on_top->type[0] == "Air" && type[2] == "")
                {
                    continue;
                }
                else if (path_covered[i]->enemy_on_top->type[1] == "Camo" && type[3] == "")
                {
                    continue;
                }
                else
                {
                    path_covered[i]->enemy_on_top->health -= damage;
                    attacked = true;
                }
            }
        }
        if (attacked)
        {
            cd = attackspeed;
        }
    }
    else if (type[0] == "Single")
    {
        int last;
        bool no_enemy = true;
        for (int i = 0; i < path_covered.size(); i++)
        {
            if (path_covered[i]->enemy_on_top != NULL)
            {
                if (path_covered[i]->enemy_on_top->type[0] == "Air" && type[2] == "")
                {
                }
                else if (path_covered[i]->enemy_on_top->type[1] == "Camo" && type[3] == "")
                {
                }
                else
                {
                    last = i;
                    no_enemy = false;
                }
            }
        }
        if (no_enemy)
        {
            return;
        }
        path_covered[last]->enemy_on_top->health -= damage;
        cd = attackspeed;
    }
}

void tower::set_tower_coverage(path *&path_start)
{
    /*

    Input:
    path_start : pointer to the first path tile in the map

    Process:
    Traverse the path from path_start
    Set the path_covered attribute of the tower to all path tiles within range of the tower

    Output:
    Modified path_covered attribute of the tower

    */
    path_covered.clear();
    path *current = path_start;
    while (current != NULL)
    {
        int row = current->coordinates.first;
        int col = current->coordinates.second;
        if (abs(row - coordinates.first) <= range && abs(col - coordinates.second) <= range)
        {
            path_covered.push_back(current);
        }
        current = current->next;
    }
}

void tower::create_tower(string tower_name, int tower_level)
{
    /*

    Input:
    tower_name : Name of the tower to be created
    tower_level : Level of the tower to be created

    Process:
    Calls the respective function to create the tower

    Output:
    Modified struct tower with the attributes of the tower created

    */
    if (tower_name == "Mage")
    {
        mage(tower_level);
    }
    else if (tower_name == "Archer")
    {
        archer(tower_level);
    }
    else if (tower_name == "Sniper")
    {
        sniper(tower_level);
    }
    else if (tower_name == "Cannon")
    {
        cannon(tower_level);
    }
}

void tower::upgrade_tower()
{
    /*

    Input:

    Process:
    Increase the level of the tower by 1
    Calls create_tower to update the attributes of the tower

    Output:
    Modified struct tower with the attributes of the upgraded tower

    */
    create_tower(name, level + 1);
}

void attack_all(vector<struct tower *> towers)
{
    /*

    Input:
    towers : vector of pointers to all towers in the map

    Process:
    Calls CalculateDamage for all towers in the map
    All towers will attack enemies in their range

    Output:
    Modified enemy health

    */
    for (int i = 0; i < towers.size(); i++)
    {
        towers[i]->CalculateDamage();
    }
}
