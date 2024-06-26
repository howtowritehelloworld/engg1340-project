#include <iostream>
#include "game.h"
using namespace std;


int main(int agrc, char **argv) 
{
    /*
    show the main screen 
    */
    initscr();
    refresh();
    start_color();
    int screenchoice = 0;

    while (screenchoice != 4)
    {   
        switch (screenchoice)
        {
            case 0: // mainmenu
                screenchoice = mainmenu(stdscr);
                break;
            case 1: // new game
                screenchoice = playscreen(stdscr, false);
                break;
            case 2: // load game
                screenchoice = playscreen(stdscr, true);
                break;
            case 3: // help screen
                screenchoice = storyscreen(stdscr);
                break;
            case 4:
                // quit W
                break;
        }
        clear();
    }

    endscreen(); // show "seeyouagain"
    return 0;
}
