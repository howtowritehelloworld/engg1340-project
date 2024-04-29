
#include <chrono>
#include <thread>
#include "map.h"
using namespace std;

void readmap(int map[9][16], int map_num, path *&path_start)
{
    /*

    Input:
    map : 2D array representing the map
    map_num : map number of the map to be read
    path_start : pointer to the first path tile in the map

    Process:
    Reads the map file corresponding to the map_num (in map folder)
    Initializes the map array with the values read from the file
        Path: -2
        Empty: -1
    Sets the path_start pointer to the first path tile in the map

    Output:
    map : 2D array representing the map (Modified)
    path_start : pointer to the first path tile in the map (Modified)

    */
    string filename = "map/map_" + std::to_string(map_num) + ".txt";
    ifstream inputfile(filename);
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            char icon;
            inputfile >> icon;
            switch (icon)
            {
            case 'S':
            {
                path *temp = new path;
                temp->coordinates = make_pair(i, j);
                path_start = temp;
                map[i][j] = -2;
                break;
            }
            case 'X':
            {
                map[i][j] = -2;
                break;
            }
            case 'E':
            {
                map[i][j] = -2;
                break;
            }
            case '.':
            {
                map[i][j] = -1;
                break;
            }
            }
        }
    }
    inputfile.close();
}

void spawn_enemy(path *&path_start, int i, vector<string> enemies)
{
    /*

    Input:
    path_start : pointer to the first path tile in the map
    i : game tick
    enemies : vector of strings containing the enemy name and enemy level

    Process:
    Reads the vector enemies
    Find the name and level of enemy to be spawned at the given tick
    Spawn the enemy at the first path tile by setting the path tile's enemy_on_top attribute
    If no enemy is to be spawned, set the path tile's enemy_on_top attribute to NULL

    Output:
    path_start : pointer to the first path tile in the map (Modified)

    */
    if (i < enemies.size())
    {
        enemy *new_enemy = new enemy;

        if (enemies[i][0] == 'K')
        {
            new_enemy->knight((int)enemies[i][1] - '0');
        }
        else if (enemies[i][0] == 'G')
        {
            new_enemy->ghost((int)enemies[i][1] - '0');
        }
        else if (enemies[i][0] == 'D')
        {
            new_enemy->dragon((int)enemies[i][1] - '0');
        }
        else if (enemies[i][0] == 'V')
        {
            new_enemy->vampire((int)enemies[i][1] - '0');
        }

        path_start->enemy_on_top = new_enemy;
    }
    else
    {
        path_start->enemy_on_top = NULL;
    }
}

void move(path *&path_start, int &killed_enemies, int &health)
{
    /*

    Input :
    path_start : pointer to the first path tile in the map
    killed_enemies : number of enemies killed
    health : health of the player

    Process :
    Move the enemies on the path_start by one step.
    If the enemy is killed, increment killed_enemies.
    If the enemy reaches the end of the path, decrement health.

    Output:
    path_start : pointer to the first path tile in the map (Modified)
    killed_enemies : number of enemies killed (Modified)
    health : health of the player (Modified)

    */
    path *current = path_start;
    enemy *previous = NULL;
    while (current != NULL)
    {
        enemy *temp = current->enemy_on_top;
        if (previous != NULL && previous->health <= 0)
        {
            current->enemy_on_top = NULL;
            killed_enemies++;
        }
        else
        {
            current->enemy_on_top = previous;
        }
        previous = temp;
        current = current->next;
    }

    if (previous != NULL)
    {
        killed_enemies++;
        health--;
    }
}