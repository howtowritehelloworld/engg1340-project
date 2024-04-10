#include <iostream>
#include <chrono>
#include <thread>
#include "path.h"
#include "enemy.h"
#include "map.h"

using namespace std;


void spawn_enemy(char e[5], pathtile*& pathhead, int i) {
    if (i < 5) {
        enemy* new_enemy = new enemy;
        new_enemy->knight();
        pathhead->on_top = new_enemy;
    }
}

void move(char map[9][16], pathtile*& pathhead) {
    pathtile* current = pathhead->next;
    enemy* previous = pathhead->on_top;
    enemy* t = NULL;
    pathhead->on_top = t;
    delete t;
    while (current != NULL){
        enemy* temp = current->on_top;
        current->on_top = previous;
        previous = temp;
        
        if (current->on_top != NULL) {
            cout << "enemy " << current->on_top->icon << " is at "  << current->row << " " << current->col << endl;
        }


        current = current->next;
    }
}

void play_game(char map[9][16], pathtile*& pathhead, char e[5]) {

    int tick = 0;
    bool end = false;
    
    while (tick < 50 && !end){
        
        move(map, pathhead);
        spawn_enemy(e, pathhead, tick);
        updatemap(map, pathhead);
        printmap(map);
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        tick++;
    }

}



int main() {
    pathtile* pathhead = new pathtile;
    char map[9][16] = {
        {'.','.','.','.','.','.','.','.','.','.', '.', '.', '.', '.', '.', '.'},
        {'.','.','.','.','.','.','.','.','.','.', '.', '.', '.', '.', '.', '.'},
        {'S','X','X','.','X','X','X','X','X','X', 'X', '.', '.', '.', '.', '.'},
        {'.','.','X','.','X','.','.','.','.','.', 'X', '.', '.', '.', '.', '.'},
        {'.','.','X','.','X','X','X','X','X','.', 'X', '.', '.', '.', '.', '.'},
        {'.','.','X','.','.','.','.','.','X','.', 'X', '.', '.', '.', '.', '.'},
        {'.','.','X','X','.','.','.','.','X','.', 'X', '.', '.', '.', '.', '.'},
        {'.','.','.','X','X','.','.','.','X','.', 'X', 'X', 'X', 'X', 'X', 'E'},
        {'.','.','.','.','X','X','X','X','X','.', '.', '.', '.', '.', '.', '.'},
    };
    int path_length = configpath(map, pathhead);
    cout << path_length << endl;
    char e[] = {'a', 'b', 'c', 'd', 'e'};
    play_game(map, pathhead, e);
    return 0;
}