#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void printgametitle(WINDOW* titlewin, string name, int row) {
    int yMax, xMax;
    getmaxyx(titlewin, yMax, xMax);
    ifstream inputfile(name + ".txt");
    string line;
    while (getline(inputfile, line)) {
        mvwprintw(titlewin, row, (xMax - line.length()) / 2, line.c_str());
        row++;
    }
    inputfile.close();
}
