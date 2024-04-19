
#include <chrono>
#include <thread>
#include "map.h"
using namespace std;

bool tile::is_empty(){
    return (!is_path && tower_on_top == NULL);
}

bool tile::is_tower(){
    return (!is_path && tower_on_top != NULL);
}

bool tile::is_enemy(){
    return (is_path && enemy_on_top != NULL);
}

void tile::set_tower_coverage(tile*& path_start){
    tile* current = path_start;
    while (current != NULL){
        int row = current->coordinates.first;
        int col = current->coordinates.second;
        if (abs(row - coordinates.first) <= tower_on_top->range && abs(col - coordinates.second) <= tower_on_top->range){
            tower_on_top->tiles_covered.push_back(current);
        }
        current = current->next;
    }
}

void tile::create_new_tower(string name, int level, tile*& path_start, int &money){
    if (is_path || is_tower()){
        return;
    }
    tower* t = new tower;
    if (name == "Mage"){
        money -= 40;
        t->mage(level);
    }
    else if (name == "Archer"){
        money -= 20;
        t->archer(level);
    }
    else if (name == "Sniper"){
        money -= 50;
        t->sniper(level);
    }
    else if (name == "Cannon"){
        money -= 30;
        t->cannon(level);
    }
    tower_on_top = t;
    set_tower_coverage(path_start);

}

void tile::upgrade_tower(tile*& path_start, int &money){
    if (!is_tower()){
        return;
    }
    int level = tower_on_top->level;
    string name = tower_on_top->name;
    tower_on_top = NULL;
    create_new_tower(name, level+1, path_start, money);
}

void printmap(tile map[9][16]) {
    cout << "*******************************" << endl;
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 16; col++) {
            if (map[row][col].is_enemy()){
                cout << map[row][col].enemy_on_top->icon << " ";
            }
            else if (map[row][col].is_path){
                cout << "X ";
            }
            else if (map[row][col].is_tower()){
                cout << map[row][col].tower_on_top->icon << " ";
            }
            
            else {
                cout << ". ";
            }
            
        }
        cout << endl;
    }
    cout << "*******************************" << endl;
}

void readmap(tile map[9][16], int map_num, tile*& path_start){
    string filename = "map/map_" + std::to_string(map_num) + ".txt";
    ifstream inputfile(filename);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 16; j++) {
            char icon;
            inputfile >> icon;
            map[i][j].is_path = (icon == 'X' || icon == 'S' || icon == 'E');
            map[i][j].coordinates = make_pair(i,j);
            if (icon == 'S') {
                path_start = &map[i][j];
            }
        }
    }
    inputfile.close();
}

void spawn_enemy(tile*& path_start, int i, vector<string> enemies) {
    if (i < enemies.size()) {
        enemy* new_enemy = new enemy;
        
        if (enemies[i][0] == 'K'){
            new_enemy->knight((int)enemies[i][1] - '0');
        }
        else if (enemies[i][0] == 'G'){
            new_enemy->ghost((int)enemies[i][1] - '0');
        }
        else if (enemies[i][0] == 'D'){
            new_enemy->dragon((int)enemies[i][1] - '0');
        }

        path_start->enemy_on_top = new_enemy;
    }
}

void move(tile map[9][16], tile*& path_start, int& killed_enemies, int& health) {
    tile* current = path_start->next;
    enemy* previous = path_start->enemy_on_top;
    enemy* temp = NULL;
    path_start->enemy_on_top = temp;
    while (current != NULL){
        // if (current->enemy_on_top != NULL) {
        //         cout << "enemy " << current->enemy_on_top->icon << " is at "  << current->coordinates.first << " " << current->coordinates.second << endl;
        //         cout << "health: " << current->enemy_on_top->health << endl;
        //     }

        temp = current->enemy_on_top;
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

void attack_all(tile map[9][16]){
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 16; j++){
            if (map[i][j].is_tower()){
                map[i][j].tower_on_top->CalculateDamage();
            }
        }
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
