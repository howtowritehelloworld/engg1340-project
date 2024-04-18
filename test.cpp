#include <ncurses.h>
#include <iostream>
#include <cmath>
#include <string>
#include <unistd.h>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>
#include "map.h"
#include "path.h"
#include "tower.h"
#include "enemy.h"
#include "chooseMap.h"

struct Coords{ // I didnt know pair existed and this looks nicer (to me)
    int y;
    int x;
};

int mainmenu(WINDOW *);
int playscreen(WINDOW *);
int helpscreen(WINDOW *);

std::vector<std::string> wave(int wave_num)
{
    std::vector<std::vector<std::string>> wave = 
    {
        {"K1"}, 
        {"K1", "K1"}, 
        {"K1", "K1", "K1"},
        {"D1"},
        {"D1", "K2"},
        {"D1", "D1", "K2"},
        {"G1", "G1"},
        {"G2", "D2", "K3"},
        {"G1", "G2", "D2", "K3"},
        {"V1", "V1"},
        {"V1", "V2", "G2", "D3", "K3"},
        {"V3", "V3", "G3", "G3"},
        {"K3", "K3", "K3", "D3", "D3", "D3"},
        {"K3", "K3", "D3", "D3", "G3", "G3", "V3", "V3"},
    };
    return wave[wave_num];
}

std::string getString(char x)
{
    std::string s(1, x);
 
    return s;   
}

void printMap(WINDOW *mainBox, tile map[9][16]) // Print the map of the game inside of the main window
{   
    // Define background colors for map
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    init_pair(2, COLOR_WHITE, COLOR_CYAN);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(5, COLOR_WHITE, COLOR_YELLOW);
    init_pair(6, COLOR_WHITE, COLOR_RED);

    int enemies = 0;
    // Looping each square to print the map
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 16; col++)
        {   
            
            if (map[row][col].is_empty()){
                wattron(mainBox, COLOR_PAIR(1)); // Turn on the color effect
                for (int i = 0; i < 3; i++){
                    for (int k = 0; k < 5; k++){
                        mvwprintw(mainBox, 3*row+i+1, 5*col+k+1, " ");
                    }
                }
                wattroff(mainBox, COLOR_PAIR(1)); // Turn off the color effect
            }
            else if (map[row][col].is_enemy()){
                mvwprintw(mainBox, 3*row+1+1, 5*col+1+1, getString(map[row][col].enemy_on_top->icon).c_str());
                mvwprintw(mainBox, 3*row+1+1, 5*col+2+1, getString(map[row][col].enemy_on_top->icon).c_str());
                mvwprintw(mainBox, 3*row+1+1, 5*col+3+1, getString(map[row][col].enemy_on_top->icon).c_str());
            }
            else if (map[row][col].is_path){
                for (int i = 0; i < 3; i++){
                    for (int k = 0; k < 5; k++){
                        mvwprintw(mainBox, 3*row+i+1, 5*col+k+1, " ");
                    }
                }
            }
            else if (map[row][col].is_tower()){
                wattron(mainBox, COLOR_PAIR(map[row][col].tower_on_top->color_id));
                for (int i = 0; i < 3; i++){
                    for (int k = 0; k < 5; k++){
                        mvwprintw(mainBox, 3*row+i+1, 5*col+k+1, " ");
                    }
                }
                wattroff(mainBox, COLOR_PAIR(map[row][col].tower_on_top->color_id));
                mvwprintw(mainBox, 3*row+1+1, 5*col+1+1, getString(map[row][col].tower_on_top->icon).c_str());
                mvwprintw(mainBox, 3*row+1+1, 5*col+2+1, getString(map[row][col].tower_on_top->icon).c_str());
                mvwprintw(mainBox, 3*row+1+1, 5*col+3+1, getString(map[row][col].tower_on_top->icon).c_str());
            }
        }
    }
}


int main(int agrc, char **argv) 
{
    initscr();
    refresh();
    start_color();
    int screenchoice = 0;

    while (screenchoice != 3)
    {   
        switch (screenchoice)
        {
            case 0: // mainmenu
                screenchoice = mainmenu(stdscr);
                break;
            case 1: // play screen
                screenchoice = playscreen(stdscr);
                break;
            case 2: // help screen
                screenchoice = helpscreen(stdscr);
                break;
            case 3:
                // quit W
                break;
        }
        clear();
    }
    

    getch();
    endwin();

    return 0;
}

Coords selectSquare(WINDOW *win) // Allow player to control cursor to select the tile they want to interact with
{   
    keypad(win, true);
    int ch;
    Coords selected = {0, 0};
    
    curs_set(1);
    wmove(win, 3*selected.y+2, 6*selected.x+4);
    while (1) {
        ch = wgetch(win);
        switch(ch) {
            case KEY_UP:
                selected.y = std::max(0, selected.y-1);
                break;
            case KEY_DOWN:
                selected.y = std::min(8, selected.y+1);
                break;
            case KEY_LEFT:
                selected.x = std::max(0, selected.x-1);
                break;
            case KEY_RIGHT:
                selected.x = std::min(15, selected.x+1);
                break;
        }
        wmove(win, 3*selected.y+2, 5*selected.x+4);
        wrefresh(win);
        if (ch == 10)
            break;
    }
    curs_set(0);
    return selected;
}

int mainmenu(WINDOW *win)
{   
    std::string title1 = " _____                        ____        __                     ";
    std::string title2 = "|_   _|____      _____ _ __  |  _ \\  ___ / _| ___ _ __  ___  ___ ";
    std::string title3 = "  | |/ _ \\ \\ /\\ / / _ \\ '__| | | | |/ _ \\ |_ / _ \\ '_ \\/ __|/ _ \\";
    std::string title4 = "  | | (_) \\ V  V /  __/ |    | |_| |  __/  _|  __/ | | \\__ \\  __/";
    std::string title5 = "  |_|\\___/ \\_/\\_/ \\___|_|    |____/ \\___|_|  \\___|_| |_|___/\\___|";
    int mid_x = win->_maxx / 2;
    int mid_y = win->_maxy / 2;

    mvwprintw(win, mid_y - 10, (mid_x - title1.length() / 2), title1.c_str());
    mvwprintw(win, mid_y - 9, (mid_x - title2.length() / 2), title2.c_str());
    mvwprintw(win, mid_y - 8, (mid_x - title3.length() / 2), title3.c_str());
    mvwprintw(win, mid_y - 7, (mid_x - title4.length() / 2), title4.c_str());
    mvwprintw(win, mid_y - 6, (mid_x - title5.length() / 2), title5.c_str());

    WINDOW * menuwin= newwin(5, 16, mid_y, mid_x - 8);
    box(menuwin, 0, 0);
    refresh();
    wrefresh(menuwin);

    keypad(menuwin, true);
    std::string choices[3] = {"Play", "Help", "Quit"};
    int choice;
    int highlight = 0;

    noecho();
    curs_set(0);

    while(1)
    {   
        for(int i = 0; i < 3; i++)
        {
            if (i == highlight)
                wattron(menuwin, A_REVERSE);
            mvwprintw(menuwin, i+1, 6, choices[i].c_str());
            wattroff(menuwin, A_REVERSE);
        }
        choice = wgetch(menuwin);
        switch(choice)
        {
            case KEY_UP:
                highlight = std::max(0, highlight-1);
                break;
            case KEY_DOWN:
                highlight = std::min(2, highlight+1);
                break;
            default:
                break;
        }
        if (choice == 10) 
            break;
    }

    return highlight+1;
}

int playscreen(WINDOW *win)
{   
    int mid_x = win->_maxx / 2;
    int mid_y = win->_maxy / 2;
    WINDOW * mainBox = newwin(29, 82, 0, mid_x - 41 - 5);
    WINDOW * actionBox = newwin(10, 20, 0, mid_x + 41 - 5);
    WINDOW * towerBox = newwin(19, 20, 10, mid_x + 41 - 5);
    WINDOW * statsBox = newwin(5, 82, 29, mid_x - 41 - 5);
    WINDOW * confirmBox = newwin(5, 20, 29, mid_x + 41 - 5);
    
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    WINDOW* titlewin = newwin(8, xMax - 12, 1, 5);
    refresh();
    int mapnum = mainscreen(titlewin);

    box(mainBox, ACS_VLINE, ACS_HLINE);
    box(actionBox, ACS_VLINE, ACS_HLINE);
    box(towerBox, ACS_VLINE, ACS_HLINE);
    box(statsBox, ACS_VLINE, ACS_HLINE);
    box(confirmBox, ACS_VLINE, ACS_HLINE);
    refresh();
    wrefresh(mainBox);
    wrefresh(actionBox);
    wrefresh(towerBox);
    wrefresh(statsBox);
    wrefresh(confirmBox);
    
    tile map[9][16];
    tile* path_start = new tile;
    readmap(map, mapnum, path_start);
    configpath(map, path_start);
    printMap(mainBox, map);
    
    wrefresh(mainBox);

    std::string options[3] = {"Start Wave", "Edit", "Quit"};
    std::string choices[5] = {"Place Tower", "Upgrade Tower", "Move Tower", "Sell Tower", "Quit"};
    int actionChoice = 0;
    int towerChoice = 0;
    int highlight = 0;

    int health = 3;
    int wave_num = 1;
    int money = 500;

    noecho();
    curs_set(0);

    nodelay(mainBox, TRUE);
    nodelay(actionBox, TRUE);
    nodelay(towerBox, TRUE);
    nodelay(statsBox, TRUE);
    nodelay(confirmBox, TRUE);

    Coords selected;
    Coords selected2;

    keypad(actionBox, true);

    bool wave_state = false;

    while(1)
    {
        //Print the Map
        printMap(mainBox, map);
        
        // update stats, enemies, towers, the fun stuff ig, but they dont do anything rn
        mvwprintw(statsBox, 2, 2, "Health: (%d)", health);
        mvwprintw(statsBox, 2, 22, "Money: (%d)", money);
        mvwprintw(statsBox, 2, 42, "Wave: (%d)", wave_num);

        for (int i = 0; i < 3; i++) // action box
        {
            if (i == highlight) // highlight the choice being selected by the player
                wattron(actionBox, A_REVERSE);
            mvwprintw(actionBox, i+2, 4, options[i].c_str());
            wattroff(actionBox, A_REVERSE);
        }


        

        // for(int i = 0; i < 5; i++) // action box
        // {   
        //     if (i == highlight) // highlight the choice being selected by the player
        //         wattron(actionBox, A_REVERSE);
        //     mvwprintw(actionBox, i+2, 4, choices[i].c_str());
        //     wattroff(actionBox, A_REVERSE);
        // }
        // if (wave_state == false) {
        //     if (5 == highlight) // highlight the choice being selected by the player
        //         wattron(actionBox, A_REVERSE);
        //     mvwprintw(actionBox, 7, 4, "Start Wave");
        //     wattroff(actionBox, A_REVERSE);
        //     wave_state == true;
        // }
        
        actionChoice = wgetch(actionBox);
        
        wrefresh(mainBox);
        wrefresh(actionBox);
        wrefresh(towerBox);
        wrefresh(statsBox);
        wrefresh(confirmBox);

        switch(actionChoice)
        {
            case KEY_UP:
                highlight = std::max(0, highlight-1);
                break;
            case KEY_DOWN:
                highlight = std::min(2, highlight+1);
                break;
            default:
                break;
        }

        // depending on key pressed, change the choice of the player
        // switch(actionChoice)
        // {
        //     case KEY_UP:
        //         highlight--;
        //         if (highlight == -1)
        //             highlight = 0;
        //         break;
        //     case KEY_DOWN:
        //         highlight++;
        //         if (highlight == 5 && wave_state == true) {
        //             highlight = 4;
        //         }
        //         else if (highlight == 6 && wave_state == false) {
        //             highlight = 5;
        //         }
        //         break;
        //     default:
        //         break;
        // }

        if (actionChoice == 10){
            actionChoice = 0;
            switch(highlight)
            {
                case 0:
                {
                    wave_state = true; // Start Wave
                    wclear(actionBox);
                    box(actionBox, ACS_VLINE, ACS_HLINE);
                    int i = 0;
                    int killed_enemies = 0;
                    while (killed_enemies < wave(wave_num).size() && health > 0 && i<100){
                        spawn_enemy(path_start, i, wave(wave_num));
                        printMap(mainBox, map);
                        mvwprintw(statsBox, 2, 2, "Health: (%d)", health);
                        mvwprintw(statsBox, 2, 22, "Money: (%d)", money);
                        mvwprintw(statsBox, 2, 42, "Wave: (%d)", wave_num);
                        wrefresh(mainBox);
                        wrefresh(actionBox);
                        wrefresh(towerBox);
                        wrefresh(statsBox);
                        wrefresh(confirmBox);
                        
                        i++;
                        std::this_thread::sleep_for(std::chrono::milliseconds(500));
                        // attack
                        move(map, path_start, killed_enemies, health);
                    }
                    wave_num++;
                    wave_state = false;
                    break;
                }
                case 1:
                {
                    selected = selectSquare(mainBox);
                    if (map[selected.y][selected.x].is_empty()){
                        wclear(towerBox);
                        box(towerBox, ACS_VLINE, ACS_HLINE);
                        mvwprintw(towerBox, 2, 5, "Empty Tile");
                        wrefresh(towerBox);
                        wclear(actionBox);
                        box(actionBox, ACS_VLINE, ACS_HLINE);
                        std::string choices[] = {"Place Tower", "Cancel"};
                        int choice = 0;
                        int highlight = 0;
                        while (choice != 10)
                        {
                            for(int i = 0; i < 2; i++) // tower box
                            {
                                if (i == highlight){
                                    wattron(actionBox, A_REVERSE);
                                }    
                                mvwprintw(actionBox, i+2, 4, choices[i].c_str());
                                wattroff(actionBox, A_REVERSE);
                                
                            }
                            choice = wgetch(actionBox);
                            
                            switch(choice)
                            {
                                case KEY_UP:
                                    highlight = std::max(0, highlight-1);
                                    break;
                                case KEY_DOWN:
                                    highlight = std::min(1, highlight+1);
                                    break;
                                default:
                                    break;
                            }
                        }
                        switch(highlight)
                        {
                            case 0:
                            {
                                
                                wclear(actionBox);
                                box(actionBox, ACS_VLINE, ACS_HLINE); 
                                std::string tower_options[] = {"Mage", "Archer", "Sniper", "Cannon"};
                                highlight = 0;
                                while (towerChoice != 10)
                                {   
                                    printMap(mainBox, map);
                                    for(int i = 0; i < 4; i++) // tower box
                                    {
                                        if (i == highlight){
                                            wattron(actionBox, A_REVERSE);
                                        }    
                                        mvwprintw(actionBox, i+2, 4, tower_options[i].c_str());
                                        wattroff(actionBox, A_REVERSE);
                                        
                                    }
                                    towerChoice = wgetch(actionBox);
                                    
                                    switch(towerChoice)
                                    {
                                        case KEY_UP:
                                            highlight = std::max(0, highlight-1);
                                            break;
                                        case KEY_DOWN:
                                            highlight = std::min(3, highlight+1);
                                            break;
                                        default:
                                            break;
                                    }
                                }

                                map[selected.y][selected.x].create_new_tower(tower_options[highlight], 1, path_start);

                                wclear(actionBox);
                                box(actionBox, ACS_VLINE, ACS_HLINE);
                                wclear(towerBox);
                                box(towerBox, ACS_VLINE, ACS_HLINE);
                                towerChoice = 0;
                                highlight = 0;
                                break;
                            }
                            case 1:
                            {
                                break;
                            }

                        }
                            

                    }
                    else if (map[selected.y][selected.x].is_path){
                        wclear(towerBox);
                        box(towerBox, ACS_VLINE, ACS_HLINE);
                        mvwprintw(towerBox, 2, 7, "Path");
                        
                    }
                    else if (map[selected.y][selected.x].is_tower()){
                        wclear(towerBox);
                        box(towerBox, ACS_VLINE, ACS_HLINE);
                        mvwprintw(towerBox, 2, 5, map[selected.y][selected.x].tower_on_top->name.c_str());
                    }
                    else {
                        wclear(towerBox);
                        box(towerBox, ACS_VLINE, ACS_HLINE);
                        mvwprintw(towerBox, 2, 5, "Unknown");
                    }
                    break;
                }
                case 2:
                {
                    return 0;
                }
            }
        }
        
        // if (actionChoice == 10) {
        //     actionChoice = 0;
        //     switch(highlight)
        //     {
        //         case 0: // Place Tower Sequence
        //         {   
                    
        //             keypad(actionBox, false);
        //             keypad(towerBox, true);
        //             std::string tower_options[] = {"Mage", "Archer", "Sniper", "Cannon"};
        //             highlight = 0;
        //             while (towerChoice != 10)
        //             {   
        //                 printMap(mainBox, map);
        //                 for(int i = 0; i < 4; i++) // tower box
        //                 {
        //                     if (i == highlight){
        //                         wattron(towerBox, A_REVERSE);
        //                     }    
        //                     mvwprintw(towerBox, i+2, 4, tower_options[i].c_str());
        //                     wattroff(towerBox, A_REVERSE);
                            
        //                 }
        //                 towerChoice = wgetch(towerBox);
                        
        //                 switch(towerChoice)
        //                 {
        //                     case KEY_UP:
        //                         highlight = std::max(0, highlight-1);
        //                         break;
        //                     case KEY_DOWN:
        //                         highlight = std::min(3, highlight+1);
        //                         break;
        //                     default:
        //                         break;
        //                 }
        //             }

        //             selected = selectSquare(mainBox);
        //             map[selected.y][selected.x].create_new_tower(tower_options[highlight], 1, path_start);

        //             wclear(towerBox);
        //             box(towerBox, ACS_VLINE, ACS_HLINE);
        //             keypad(towerBox, false);
        //             keypad(actionBox, true);
        //             towerChoice = 0;
        //             highlight = 0;
        //             break;
        //         }

        //         case 1:
        //             selected = selectSquare(mainBox); // Upgrade Tower Sequence
        //             if (map[selected.y][selected.x].is_tower()) {
        //                 money -= map[selected.y][selected.x].tower_on_top->cost;
        //                 map[selected.y][selected.x].upgrade_tower(path_start);
        //             }
        //             break;
        //         // case 2:
        //         //     selected = selectSquare(mainBox); // Move Tower Sequence
        //         //     if (gameMap[selected.y][selected.x].type == "Tower") {
        //         //         selected2 = selectSquare(mainBox);
        //         //         if (gameMap[selected2.y][selected2.x].name == "ground") {
        //         //             gameMap[selected2.y][selected2.x] = gameMap[selected.y][selected.x];
        //         //             gameMap[selected.y][selected.x] = ground;
        //         //         }
        //         //     }
        //         //     break;
        //         // case 3: {
        //         //     selected = selectSquare(mainBox);  // Sell Tower Sequence
        //         //     if (gameMap[selected.y][selected.x].type == "Tower"){
        //         //         gameMap[selected.y][selected.x] = ground;
        //         //     }                        
        //         //     break;
        //         // }
                    
        //         case 4:
        //             return 0; // Quit Sequence

        //         case 5:
        //             wave_state = true; // Start Wave
        //             highlight = 4;
        //             wclear(actionBox);
        //             box(actionBox, ACS_VLINE, ACS_HLINE);
        //             int i = 0;
        //             int killed_enemies = 0;
        //             while (killed_enemies < wave(wave_num).size() && health > 0 && i<100){
        //                 spawn_enemy(path_start, i, wave(wave_num));
        //                 printMap(mainBox, map);
        //                 mvwprintw(statsBox, 2, 2, "Health: (%d)", health);
        //                 mvwprintw(statsBox, 2, 22, "Money: (%d)", money);
        //                 mvwprintw(statsBox, 2, 42, "Wave: (%d)", wave_num);
        //                 wrefresh(mainBox);
        //                 wrefresh(actionBox);
        //                 wrefresh(towerBox);
        //                 wrefresh(statsBox);
        //                 wrefresh(confirmBox);
                        
        //                 i++;
        //                 std::this_thread::sleep_for(std::chrono::milliseconds(500));
        //                 // attack
        //                 move(map, path_start, killed_enemies, health);
        //             }
        //             wave_num++;
        //             wave_state = false;
        //             break;

        //     }
        // }
        wrefresh(mainBox);
        wrefresh(actionBox);
        wrefresh(towerBox);
        wrefresh(statsBox);
        wrefresh(confirmBox);
    }

    return 0;
}

int helpscreen(WINDOW *win)
{
    return 0;
}
