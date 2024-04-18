#include "chooseMap.h"

using namespace std;

void mapdisplay(WINDOW* mapwin, int count) {
    wclear(mapwin);
    ifstream mapfile("map/map_" + to_string(count) + ".txt");
    string line;
    int y = 0;
    while (getline(mapfile, line)) {
        mvwprintw(mapwin, y, 0, line.c_str());
        y++;
    }
    mapfile.close();
}

int mainscreen(WINDOW* titlewin, int highlight, int count) {
    // Print "Choose a map" title
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    string title1 = "    ___ _                              _                         ";
    string title2 = "   / __\\ |__   ___   ___  ___  ___    /_\\     /\\/\\   __ _ _ __   ";
    string title3 = "  / /  | '_ \\ / _ \\ / _ \\/ __|/ _ \\  //_\\\\   /    \\ / _` | '_ \\  ";
    string title4 = " / /___| | | | (_) | (_) \\__ \\  __/ /  _  \\ / /\\/\\ \\ (_| | |_) | ";
    string title5 = " \\____/|_| |_|\\___/ \\___/|___/\\___| \\_/ \\_/ \\/    \\/\\__,_| .__/  ";
    string title6 = "                                                         |_|     ";

    int titleX = (xMax - title1.length()) / 2 - 3;

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

    int choice;

    while (1) {

        mapdisplay(mapwin, count);
        wrefresh(mapwin);
        // Print the menu options
        wclear(menuwin);
        mvwprintw(menuwin, 3, xMax/2 - 16, "Press Enter to select");
        if (count != 1)
            mvwprintw(menuwin, 3, xMax/2 - 21, "<==");
        if (count != 6)
            mvwprintw(menuwin, 3, xMax/2 + 7, "==>");

        // Refresh the menu window
        wrefresh(menuwin);

        // Get user input
        choice = wgetch(menuwin);

        switch (choice) {
            case KEY_LEFT:
                count--;
                if (count == 0) {
                    count = 1;
                }
                break;
            case KEY_RIGHT:
                count++;
                if (count == 7) {
                    count = 6;
                }
                break;
            default:
                break;
            }
        if (choice == 10) 
            break;
    }

    if (count == 6) {
        srand(time(0));
        count = rand() % 5 + 1;
        werase(mapwin);
        werase(menuwin);
        werase(titlewin);
        mvprintw(yMax/2, xMax/2 - 5, to_string(count).c_str());
        refresh();
    }

    // Clear the screen and print the count
    clear();
    refresh();
    delwin(mapwin);
    delwin(menuwin);
    return count;     
}