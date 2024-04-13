
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


void printmap(tile map[9][16]) {
    cout << "*******************************" << endl;
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 16; col++) {
            if (map[row][col].is_path){
                cout << "X ";
            }
            else if (map[row][col].is_empty()){
                cout << ". ";
            }
            
        }
        cout << endl;
    }
    cout << "*******************************" << endl;
}

// void updatemap(char map[9][16], pathtile*& pathhead, vector<tower*> towers){
//     for (int row = 0; row < 9; row++) {
//         for (int col = 0; col < 16; col++) {
//                 map[row][col] = '.';
//         }
//     }

//     for (int i = 0; i < towers.size(); i++){
//         map[towers[i]->coordinates[0].first][towers[i]->coordinates[0].second] = towers[i]->icon;
//     }


//     if (pathhead->on_top != NULL){
//         map[pathhead->row][pathhead->col] = pathhead->on_top->icon;
//     }
//     else {
//         map[pathhead->row][pathhead->col] = 'S';
//     }
//     pathtile* currentpath = pathhead->next;
    
//     while (currentpath->next != NULL) {
//         if (currentpath->on_top != NULL){
//             map[currentpath->row][currentpath->col] = currentpath->on_top->icon;
//         }
//         else {
//             map[currentpath->row][currentpath->col] = 'X';
//         }
//         currentpath = currentpath->next;
//     }
//     if (currentpath->on_top != NULL){
//         map[currentpath->row][currentpath->col] = currentpath->on_top->icon;
//     }
//     else {
//         map[currentpath->row][currentpath->col] = 'E';
//     }
// }

void readmap(tile map[9][16], int map_num){
    string filename = "map/map_" + std::to_string(map_num) + ".txt";
    ifstream inputfile(filename);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 16; j++) {
            char icon;
            inputfile >> icon;
            map[i][j].is_path = (icon == 'X' || icon == 'S' || icon == 'E');
            map[i][j].coordinates = make_pair(i,j);
        }
    }
    inputfile.close();
}

int main(){
    tile map[9][16];
    readmap(map, 1);
    printmap(map);
    tile* path_start = new tile;
    configpath(map, path_start);
    tile* current = path_start;
    while (current){
        cout << current->coordinates.first << " " << current->coordinates.second << endl;
        current = current->next;
    }
}