
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

void tile::create_new_tower(string name, tile*& path_start){
    if (is_path || is_tower()){
        return;
    }
    tower* t = new tower;
    if (name == "mage"){
        t->mage();
    }
    else if (name == "archer"){
        t->archer();
    }
    else if (name == "sniper"){
        t->sniper();
    }
    else if (name == "cannon"){
        t->cannon();
    }
    tower_on_top = t;
    set_tower_coverage(path_start);

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

void spawn_enemy(tile*& path_start, int i) {
    if (i < 5) {
        enemy* new_enemy = new enemy;
        new_enemy->knight();
        path_start->enemy_on_top = new_enemy;
    }
}

void move(tile map[9][16], tile*& path_start) {
    tile* current = path_start->next;
    enemy* previous = path_start->enemy_on_top;
    enemy* t = NULL;
    path_start->enemy_on_top = t;
    delete t;
    while (current != NULL){
        if (current->enemy_on_top != NULL) {
                cout << "enemy " << current->enemy_on_top->icon << " is at "  << current->coordinates.first << " " << current->coordinates.second << endl;
            }

        enemy* temp = current->enemy_on_top;
        current->enemy_on_top = previous;
        previous = temp;
        
        
        

        current = current->next;
    }
}



int main(){
    tile map[9][16];
    tile* path_start = new tile;
    readmap(map, 1, path_start);
    printmap(map);
    
    configpath(map, path_start);

    // test set path
    // tile* current = path_start;
    // while (current != NULL) {
    //     cout << current->coordinates.first << " " << current->coordinates.second << endl;
    //     current = current->next;
    // }

    // test enemy movement
    // int i = 0;
    // while (i<30){
    //     spawn_enemy(path_start, i);
    //     printmap(map);
    //     i++;
    //     move(map, path_start);
    // }

    // test placing new tower
    map[2][1].create_new_tower("mage", path_start);
    for (int i = 0; i < map[2][1].tower_on_top->tiles_covered.size(); i++){
        cout << map[2][1].tower_on_top->tiles_covered[i]->coordinates.first << " " << map[2][1].tower_on_top->tiles_covered[i]->coordinates.second << endl;
    }

    printmap(map);
}