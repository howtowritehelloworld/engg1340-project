#ifndef PATH_H
#define PATH_H
#include <vector>
#include "map.h"

struct path{
    enemy* enemy_on_top = NULL;
    std::pair<int,int> coordinates;
    path* next = NULL;
};

void get_next(int map[9][16], path*& current, path*& previous);
int configpath(int map[9][16], path*& path_start);

#endif // PATH_H
