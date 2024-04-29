
#include <chrono>
#include <thread>
#include "map.h"
using namespace std;

void readmap(int map[9][16], int map_num, path*& path_start){
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
                    path* temp = new path;
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

void spawn_enemy(path*& path_start, int i, vector<string> enemies) {
    if (i < enemies.size()) 
    {
        enemy* new_enemy = new enemy;
        
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

void move(path*& path_start, int& killed_enemies, int& health) {
    path* current = path_start;
    enemy* previous = NULL;
    while (current != NULL){

        enemy* temp = current->enemy_on_top;
        if (previous != NULL && previous->health <= 0){
            current->enemy_on_top = NULL;
            killed_enemies++;
        }
        else{
            current->enemy_on_top = previous;
        }
        previous = temp;
        current = current->next;
    }
    if (previous != NULL){
        killed_enemies++;
        health--;
    }
}