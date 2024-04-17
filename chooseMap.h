#ifndef CHOOSEMAP_H
#define CHOOSEMAP_H

#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

void mapdisplay(WINDOW* mapwin, int count);

int mainscreen(WINDOW* titlewin, int highlight = 0, int count = 1);

#endif