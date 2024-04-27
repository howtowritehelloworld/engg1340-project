#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void printgametitle(string name) {
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    ifstream inputfile(name + ".txt");
    vector lines;
    
    string line;
    while (getline(inputfile, line)) {
        lines.push_back(line);
    }
    WINDOW* win = newwin
    int y=1;
    for (const auto& line : lines) {
        mvwprintw(win, y, 1, line.c_str());
        y++;
    }
    getch();
    delwin(win);
    endwin();

    inputfile.close();
}
