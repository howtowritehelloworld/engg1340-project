#include "path.h"
using namespace std;


bool is_not_repeat(tile*& previous, tile*& new_tile) {
    return previous == NULL || new_tile != previous;
}

bool in_range(pair<int,int> coordinates){
    return coordinates.first >= 0 && coordinates.first < 9 && coordinates.second >= 0 && coordinates.second < 16;
}

void get_next(tile map[9][16], tile*& current, tile*& previous) {

    pair<int, int> neighbors_coordinates[4] = {
        make_pair(current->coordinates.first - 1, current->coordinates.second),
        make_pair(current->coordinates.first + 1, current->coordinates.second),
        make_pair(current->coordinates.first, current->coordinates.second - 1),
        make_pair(current->coordinates.first, current->coordinates.second + 1)
    };

    for (int i = 0; i < 4; i++) {
        if (!in_range(neighbors_coordinates[i])) {
            continue;
        }
        tile* neighbor = &map[neighbors_coordinates[i].first][neighbors_coordinates[i].second];
        if (neighbor->is_path && 
            is_not_repeat(previous, neighbor)){
            current->next = neighbor;
            previous = current;
            current = neighbor;
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