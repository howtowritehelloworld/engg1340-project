//Not yet done
#include <ncurses.h>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char **argv) {
    initscr();
    noecho();
    cbreak();
    curs_set(0);

    // Get screen size
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    // Create a window for the title
    WINDOW *titlewin = newwin(6, xMax, 0 , 0);

    // Print "Choose a map" title
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
    WINDOW *mapwin = newwin(9, 16, 9, (xMax - 17) /2);
    box(mapwin, 0, 0);
    wrefresh(mapwin);



  
    // Create a window for the menu
    WINDOW *menuwin = newwin(7, xMax - 12, yMax -17, 5);
    box(menuwin, 0, 0);

    // For arrow keys
    keypad(menuwin, true);

    string choices[3] = {"Next", "Previous", "Select"};
    int choice;
    int highlight = 0;

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
            break;
        }
    }

    getch();
    endwin();
    return 0;
}
