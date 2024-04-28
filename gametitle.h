#ifndef PRINTGAMETITLE_H
#define PRINTGAMETITLE_H

#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <string>

void printgametitle(WINDOW* titlewin, std::string name, int row);

#endif