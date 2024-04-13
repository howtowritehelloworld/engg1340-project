#include "path.h"
using namespace std;


bool is_not_previous(tile*& previous, tile*& new_tile) {
    return previous == NULL || new_tile != previous;
}


void get_next(tile map[9][16], tile*& current, tile*& previous) {

    tile* neighbors[4] = {
        &map[current->coordinates.first - 1][current->coordinates.second],
        &map[current->coordinates.first + 1][current->coordinates.second],
        &map[current->coordinates.first][current->coordinates.second - 1],
        &map[current->coordinates.first][current->coordinates.second + 1]
    };

    for (int i = 0; i < 4; i++) {
        if (neighbors[i]->is_path && 
            is_not_previous(previous, neighbors[i])){
            current->next = neighbors[i];
            previous = current;
            current = neighbors[i];
            return;
        }
    }
    current = NULL;
}

int configpath(tile map[9][16], tile*& path_start) {
    tile* current = path_start;
    tile* previous = NULL;

    int i = 1;
    while (current) {
        get_next(map, current, previous);
        i++;
    }
    return i;
}