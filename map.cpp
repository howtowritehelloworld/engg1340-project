
#include "map.h"
using namespace std;

void printmap(char map[9][16]) {
    cout << "*******************************" << endl;
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 16; col++) {
            cout << map[row][col] << " ";
        }
        cout << endl;
    }
    cout << "*******************************" << endl;
}

void updatemap(char map[9][16], pathtile*& pathhead, vector<tower*> towers){
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 16; col++) {
                map[row][col] = '.';
        }
    }

    for (int i = 0; i < towers.size(); i++){
        map[towers[i]->coordinates[0].first][towers[i]->coordinates[0].second] = towers[i]->icon;
    }


    if (pathhead->on_top != NULL){
        map[pathhead->row][pathhead->col] = pathhead->on_top->icon;
    }
    else {
        map[pathhead->row][pathhead->col] = 'S';
    }
    pathtile* currentpath = pathhead->next;
    
    while (currentpath->next != NULL) {
        if (currentpath->on_top != NULL){
            map[currentpath->row][currentpath->col] = currentpath->on_top->icon;
        }
        else {
            map[currentpath->row][currentpath->col] = 'X';
        }
        currentpath = currentpath->next;
    }
    if (currentpath->on_top != NULL){
        map[currentpath->row][currentpath->col] = currentpath->on_top->icon;
    }
    else {
        map[currentpath->row][currentpath->col] = 'E';
    }
}
