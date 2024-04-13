//Almost done
#include <ncurses.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

void mapdisplay(WINDOW* mapwin, int count){
  ifstream mapfile;
  mapfile.open("map_" + to_string(count) + ".txt");
  string line;
  int y = 0;
  while(getline(mapfile, line)){
    mvwprintw(mapwin, y, 0, line.c_str());
    y++;
  }
}



void mainscreen(WINDOW* titlewin, int highlight = 0, int count = 0) {
    // Print "Choose a map" title
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    string title1 = "    ___ _                              _                         ";
    string title2 = "   / __\\ |__   ___   ___  ___  ___    /_\\     /\\/\\   __ _ _ __   ";
    string title3 = "  / /  | '_ \\ / _ \\ / _ \\/ __|/ _ \\  //_\\\\   /    \\ / _` | '_ \\  ";
    string title4 = " / /___| | | | (_) | (_) \\__ \\  __/ /  _  \\ / /\\/\\ \\ (_| | |_) | ";
    string title5 = " \\____/|_| |_|\\___/ \\___/|___/\\___| \\_/ \\_/ \\/    \\/\\__,_| .__/  ";
    string title6 = "                                                         |_|     ";

    int titleX = (xMax - title1.length()) / 2;

    mvwprintw(titlewin, 0, titleX, title1.c_str());
    mvwprintw(titlewin, 1, titleX, title2.c_str());
    mvwprintw(titlewin, 2, titleX, title3.c_str());
    mvwprintw(titlewin, 3, titleX, title4.c_str());
    mvwprintw(titlewin, 4, titleX, title5.c_str());
    mvwprintw(titlewin, 5, titleX, title6.c_str());

    // Refresh the title window
    wrefresh(titlewin);

    // Create a window for the map display
    WINDOW* mapwin = newwin(11, 32, 8, xMax/2 - 16);
    mapdisplay(mapwin, count);
    wrefresh(mapwin);

    // Create a window for the menu
    WINDOW* menuwin = newwin(7, xMax - 12, yMax - 17, 5);
    box(menuwin, 0, 0);

    // For arrow keys
    keypad(menuwin, true);

    string choices[3] = {"Next", "Previous", "Select"};
    int choice;

    while (1) {
        // Print the menu options
        for (int i = 0; i < 3; i++) {
            if (i == highlight)
                wattron(menuwin, A_REVERSE);
            mvwprintw(menuwin, i + 2, (xMax - 17) / 2, choices[i].c_str());
            wattroff(menuwin, A_REVERSE);
        }

        // Refresh the menu window
        wrefresh(menuwin);

        // Get user input
        choice = wgetch(menuwin);

        switch (choice) {
            case KEY_UP:
                highlight--;
                if (highlight == -1) {
                    highlight = 0;
                }
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight == 3) {
                    highlight = 2;
                }
                break;
            default:
                break;
        }
        if (choice == 10) {
            if (highlight == 0) {
                count++;
                if (count == 6) {
                    count = 0;
                }
            }
            else if (highlight == 1) {
                count--;
                if (count == -1) {
                    count = 5;
                }
            }
            else {
                exit(1);
            }

            wrefresh(mapwin);
            mainscreen(titlewin, highlight, count);  
        }
    }

    delwin(mapwin);
    delwin(menuwin);
}

int main(int argc, char** argv) {
    initscr();
    noecho();
    cbreak();
    curs_set(0);

    // Get screen size
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    
    // Create a window for the title
    WINDOW* titlewin = newwin(6, xMax, 0, 0);
    mainscreen(titlewin);

    getch();
    endwin();
    return 0;
}
