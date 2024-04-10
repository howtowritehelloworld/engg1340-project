#ifndef PATH_H
#define PATH_H
#include "enemy.h"
struct pathtile {
    int row, col;
    pathtile* next;
    enemy* on_top = NULL;
};
void set_start(char map[9][16], char target, pathtile*& pathhead);
void get_next(char map[9][16], pathtile*& current, pathtile*& previous);
int configpath(char map[9][16], pathtile*& pathhead);

#endif // PATH_H
