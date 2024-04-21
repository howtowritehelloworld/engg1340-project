
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

        path_start->enemy_on_top = new_enemy;
    }
    else
    {
        path_start->enemy_on_top = NULL;
    }
}

void move(path*& path_start, int& killed_enemies, int& health) {
    path* current = path_start->next;
    enemy* previous = path_start->enemy_on_top;
    while (current != NULL){
        // if (current->enemy_on_top != NULL) {
        //         cout << "enemy " << current->enemy_on_top->icon << " is at "  << current->coordinates.first << " " << current->coordinates.second << endl;
        //         cout << "health: " << current->enemy_on_top->health << endl;
        //     }

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

void attack_all(vector<struct tower*> towers){
    for (int i = 0; i < towers.size(); i++){
        towers[i]->CalculateDamage();
    }
}



// int main(){
//     tile map[9][16];
//     tile* path_start = new tile;
//     readmap(map, 4, path_start);
//     printmap(map);
//     configpath(map, path_start);

//     cout << (path_start->next == NULL) << endl;
//     // test set path
//     tile* current = path_start;
//     while (current) {
//         cout << current->coordinates.first << " " << current->coordinates.second << endl;
//         current = current->next;
//     }
//     // test placing new tower
//     map[0][0].create_new_tower("mage", 1, path_start);
//     for (int i = 0; i < map[0][0].tower_on_top->tiles_covered.size(); i++){
//         cout << map[0][0].tower_on_top->tiles_covered[i]->coordinates.first << " " << map[0][0].tower_on_top->tiles_covered[i]->coordinates.second << endl;
//     }

//     printmap(map);

//     // test enemy movement
//     vector<string> enemies = {"K1"};
//     int i = 0;
//     int health = 3;
//     int killed_enemies = 0;
//     while (i<30){
//         // if (map[4][5].is_enemy()&&map[4][5].enemy_on_top->icon == 'D'){
//         //     map[4][5].enemy_on_top->health = 0;
//         // }
        
//         spawn_enemy(path_start, i, enemies);
//         printmap(map);
//         i++;
//         std::this_thread::sleep_for(std::chrono::milliseconds(500));
//         move(map, path_start, killed_enemies, health);
//     }

    
// }
