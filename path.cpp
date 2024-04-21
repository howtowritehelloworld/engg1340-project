#include "path.h"
using namespace std;



bool is_not_repeat(path*& previous, pair<int, int> new_path) {
    return previous == NULL || new_path.first != previous->coordinates.first || new_path.second != previous->coordinates.second;
}

bool in_range(pair<int,int> coordinates){
    return coordinates.first >= 0 && coordinates.first < 9 && coordinates.second >= 0 && coordinates.second < 16;
}


void get_next(int map[9][16], path*& current, path*& previous) {

    pair<int, int> neighbors_coordinates[4] = 
    {
        make_pair(current->coordinates.first - 1, current->coordinates.second),
        make_pair(current->coordinates.first + 1, current->coordinates.second),
        make_pair(current->coordinates.first, current->coordinates.second - 1),
        make_pair(current->coordinates.first, current->coordinates.second + 1)
    };

    for (int i = 0; i < 4; i++) 
    {
        if (!in_range(neighbors_coordinates[i])) 
        {
            continue;
        }
        int neighbor = map[neighbors_coordinates[i].first][neighbors_coordinates[i].second];
        if (neighbor == -2  && 
            is_not_repeat(previous, neighbors_coordinates[i]))
        {

            path* temp = new path;
            temp->coordinates = neighbors_coordinates[i];

            current->next = temp;
            previous = current;
            current = temp;
            return;
        }
    }
    current = NULL;
}

int configpath(int map[9][16], path*& path_start) {
    path* current = path_start;
    path* previous = NULL;
    int i = 1;
    while (current) {
        get_next(map, current, previous);
        i++;
    }
    return i;
}