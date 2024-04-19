#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void mainscreen(int highlight = 0, int count = 1) {
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    string title1 = " __   __  _______  __   __    ___      _______  _______  _______ ";
    string title2 = "|  | |  ||       ||  | |  |  |   |    |       ||       ||       |";
    string title3 = "|  |_|  ||   _   ||  | |  |  |   |    |   _   ||  _____||    ___|";
    string title4 = "|       ||  | |  ||  |_|  |  |   |    |  | |  || |_____ |   |___ ";
    string title5 = "|_     _||  |_|  ||       |  |   |___ |  |_|  ||_____  ||    ___|";
    string title6 = "  |   |  |       ||       |  |       ||       | _____| ||   |___ ";
    string title7 = "  |___|  |_______||_______|  |_______||_______||_______||_______|";

    int titleX = (xMax - title1.length()) / 2 - 3;

    mvprintw(yMax / 2 - 7, titleX, title1.c_str());
    mvprintw(yMax / 2 - 6, titleX, title2.c_str());
    mvprintw(yMax / 2 - 5, titleX, title3.c_str());
    mvprintw(yMax / 2 - 4, titleX, title4.c_str());
    mvprintw(yMax / 2 - 3, titleX, title5.c_str());
    mvprintw(yMax / 2 - 2, titleX, title6.c_str());
    mvprintw(yMax / 2 - 1, titleX, title7.c_str());

    refresh();

    WINDOW* menuwin = newwin(7, xMax - 12, yMax - 10, 5);
    box(menuwin, 0, 0);


    keypad(menuwin, true);

    string choices[2] = {"Main Menu", "Quit"};
    int choice;

    while (1) {
  
        for (int i = 0; i < 2; i++) {
            if (i == highlight)
                wattron(menuwin, A_REVERSE);
            mvwprintw(menuwin, i + 2, (xMax - 17) / 2, choices[i].c_str());
            wattroff(menuwin, A_REVERSE);
        }


        wrefresh(menuwin);


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
                if (highlight == 2) {
                    highlight = 1;
                }
                break;
            default:
                break;
        }

        // When pressing Enter
        if (choice == 10) {
            // If the user chooses the main menu
            if (highlight == 0) {
                erase();
                
                return;
            }
            // If the user chooses to quit
            else if (highlight == 1) {
                erase();
                return;
            }
        }
    }
}

int main(int argc, char** argv){
    initscr();
    noecho();
    cbreak();
    curs_set(0);

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    mainscreen();

    // Clear the screen
    clear();

    endwin();
    return 0;
}
