#ifndef PATH_H
#define PATH_H
#include <vector>
#include "map.h"

void set_start(struct tile map[9][16], tile*& pathhead);
void get_next(struct tile map[9][16], tile*& current, tile*& previous);
int configpath(struct tile map[9][16], tile*& pathhead);

#endif // PATH_H
