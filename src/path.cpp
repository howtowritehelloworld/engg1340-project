#include "path.h"
using namespace std;



bool is_not_repeat(path*& previous, pair<int, int> new_path) {
    /*
    
    Input:
    previous : Pointer to the previous path tile
    new_path : Coordinates of the new path tile

    Process:
    Checks if the new path tile is not the same as the previous path tile

    Output:
    Returns true if the new path tile is not the same as the previous path tile, false otherwise

    */
    return previous == NULL || new_path.first != previous->coordinates.first || new_path.second != previous->coordinates.second;
}

bool in_range(pair<int,int> coordinates)
{
    /*

    Input:
    coordinates : Coordinates of a tile

    Process:
    Checks if the coordinates are within the map

    Output:
    Returns true if the coordinates are within the map, false otherwise

    */
    return coordinates.first >= 0 && coordinates.first < 9 && coordinates.second >= 0 && coordinates.second < 16;
}


void get_next(int map[9][16], path*& current, path*& previous) 
{
    /*

    Input:
    map : 2D array representing the map
    current : Pointer to the current path tile
    previous : Pointer to the previous path tile

    Process:
    Based on the coordinates of the current path tile, the neighbors are found.
    If the neighbor is a path tile and not the previous path tile, a new path tile is created.

    Output:
    Modified path linked list

    */

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

int configpath(int map[9][16], path*& path_start) 
{
    /*
    
    Input:
    map : 2D array representing the map
    path_start : Pointer to the start of the path linked list

    Process:
    Configures the path linked list based on the map

    Output:
    The path length
    Modified path linked list

    */
    path* current = path_start;
    path* previous = NULL;
    int i = 1;
    while (current) {
        get_next(map, current, previous);
        i++;
    }
    return i;
}