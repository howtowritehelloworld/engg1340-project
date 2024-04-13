#ifndef PATH_H
#define PATH_H
#include <vector>
#include "map.h"

void get_next(struct tile map[9][16], tile*& current, tile*& previous);
int configpath(struct tile map[9][16], tile*& path_start);

#endif // PATH_H
