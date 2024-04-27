#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void printgametitle(WINDOW* titlewin, string name) {
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    ifstream inputfile(name + ".txt");
    vector lines;
    
    string line;
    while (getline(inputfile, line)) {
        lines.push_back(line);
    }

    int titleX = (xMax - lines[0].length()) / 2 - 3;
    int y=1;
    for (const auto& line : lines) {
        mvwprintw(titlewin, y, titleX, line.c_str());
        y++;
    }
    // Refresh the title window
    wrefresh(titlewin);

    inputfile.close();
}
