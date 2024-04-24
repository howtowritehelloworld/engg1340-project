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

std::vector<std::string> tutor_wave(int wave_num)
{
    std::vector<std::vector<std::string>> tutor_wave = 
    {
        {"K1"},
        {"D1"},
        {"G1"},
        {"V1"},
    };
    return tutor_wave[wave_num-1];
}

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
    return wave[wave_num-1];
}

std::string getString(char x)
{
    std::string s(1, x);
 
    return s;   
}

void printMap(WINDOW *mainBox, path*& path_start, std::vector<tower*> towers) // Print the map of the game inside of the main window
{   
    // Define background colors for map
    use_default_colors();
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    init_pair(2, COLOR_WHITE, COLOR_CYAN);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(5, COLOR_WHITE, COLOR_YELLOW);
    init_pair(6, COLOR_WHITE, COLOR_RED);
    init_pair(7, COLOR_GREEN, -1);

    int enemies = 0;
    // Looping each square to print the map
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 16; col++)
        {   
            
            wattron(mainBox, COLOR_PAIR(1)); // Turn on the color effect
            for (int i = 0; i < 3; i++){
                for (int k = 0; k < 5; k++){
                    mvwprintw(mainBox, 3*row+i+1, 5*col+k+1, " ");
                }
            }
            wattroff(mainBox, COLOR_PAIR(1)); // Turn off the color effect

        }
    }

    for (int i = 0; i < towers.size(); i++)
    {
        tower* current_tower = towers[i];
        int row = current_tower->coordinates.first;
        int col = current_tower->coordinates.second;
        int cooldownbar = 5* (current_tower->attackspeed - current_tower->cd) / current_tower->attackspeed;
        wattron(mainBox, COLOR_PAIR(current_tower->color_id));
        for (int i = 0; i < 3; i++){
            for (int k = 0; k < cooldownbar; k++){
                mvwprintw(mainBox, 3*row+i+1, 5*col+k+1, " ");
            }
        }
        wattroff(mainBox, COLOR_PAIR(current_tower->color_id));
        mvwprintw(mainBox, 3*row+1+1, 5*col+1+1, getString(current_tower->icon).c_str());
        mvwprintw(mainBox, 3*row+1+1, 5*col+2+1, getString(current_tower->icon).c_str());
        mvwprintw(mainBox, 3*row+1+1, 5*col+3+1, getString(current_tower->icon).c_str());
    }

    path* current = path_start;
    while (current)
    {
        int row = current->coordinates.first;
        int col = current->coordinates.second;
        for (int i = 0; i < 3; i++)
        {
            for (int k = 0; k < 5; k++)
            {
                mvwprintw(mainBox, 3*row+i+1, 5*col+k+1, " ");
            }
        }
        if (current->enemy_on_top != NULL)
        {   
            if (current->enemy_on_top->type[1] == "Camo")
                wattron(mainBox, COLOR_PAIR(7));
            if (current->enemy_on_top->type[0] == "Air") {
                mvwprintw(mainBox, 3*row+1+1, 5*col+1+1, "^");
                mvwprintw(mainBox, 3*row+1+1, 5*col+2+1, getString(current->enemy_on_top->icon).c_str());
                mvwprintw(mainBox, 3*row+1+1, 5*col+3+1, "^");
            } else {
                mvwprintw(mainBox, 3*row+1+1, 5*col+1+1, getString(current->enemy_on_top->icon).c_str());
                mvwprintw(mainBox, 3*row+1+1, 5*col+2+1, getString(current->enemy_on_top->icon).c_str());
                mvwprintw(mainBox, 3*row+1+1, 5*col+3+1, getString(current->enemy_on_top->icon).c_str());
            }
            enemies++;
            wattroff(mainBox, COLOR_PAIR(7));
        }
        current = current->next;
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

Coords selectSquare(WINDOW *win, WINDOW* actionBox) // Allow player to control cursor to select the tile they want to interact with
{   
    wclear(actionBox);
    box(actionBox, ACS_VLINE, ACS_HLINE);
    mvwprintw(actionBox, 3, 2, "Move: Arrow Keys");
    mvwprintw(actionBox, 5, 3, "Select: Enter");
    mvwprintw(actionBox, 7, 1, "Cancel: Backspace");
    wrefresh(actionBox);
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
            case KEY_BACKSPACE:
                curs_set(0);
                return {-1, -1};
        }
        wmove(win, 3*selected.y+2, 5*selected.x+4);
        wrefresh(win);
        if (ch == 10)
            break;
    }
    curs_set(0);
    return selected;
}

void print_tower(WINDOW* win, tower* tower_on_top){
    for (int i = 2; i < 13; i++){
        mvwprintw(win, i, 4, "               ");
    }
    mvwprintw(win, 2, 4, "%s", tower_on_top->name.c_str());
    mvwprintw(win, 4, 4, "Level: %d", tower_on_top->level);
    mvwprintw(win, 5, 4, "Damage: %d", tower_on_top->damage);
    mvwprintw(win, 6, 4, "Range: %d", tower_on_top->range);
    mvwprintw(win, 7, 4, "Cost: %d", tower_on_top->cost);
    for (int i = 0; i < 4; i++){
        mvwprintw(win, 9+i, 4, tower_on_top->type[i].c_str());
    }
}

int chooseOption(WINDOW *win, std::vector<std::string> choices){
    keypad(win, true);
    wclear(win);
    box(win, ACS_VLINE, ACS_HLINE);
    int highlight = 0;
    int keyboard_input = 0;
    int num_of_choices = choices.size();
    while (keyboard_input != 10){
        for (int i = 0; i < num_of_choices; i++){
            if (i == highlight)
                wattron(win, A_REVERSE);
            mvwprintw(win, i+2, 4, choices[i].c_str());
            wattroff(win, A_REVERSE);
        }
        keyboard_input = wgetch(win);
        switch(keyboard_input)
        {
            case KEY_UP:
                highlight = std::max(0, highlight-1);
                break;
            case KEY_DOWN:
                highlight = std::min(num_of_choices-1, highlight+1);
                break;
            default:
                break;
        }
    }
    return highlight;
}

int choose_tower_option(WINDOW* actionBox, WINDOW* towerBox, std::vector<std::string> tower_options){
    keypad(actionBox, true);
    wclear(actionBox);
    box(actionBox, ACS_VLINE, ACS_HLINE);
    int highlight = 0;
    int keyboard_input = 0;
    int num_of_choices = tower_options.size();
    while (keyboard_input != 10){
        for (int i = 0; i < num_of_choices; i++){
            if (i == highlight){
                wattron(actionBox, A_REVERSE);
                tower* temp_tower = new tower;
                temp_tower->sample_tower(tower_options[i]);
                print_tower(towerBox, temp_tower);
                wrefresh(towerBox);
                delete temp_tower;
            }
            mvwprintw(actionBox, i+2, 4, tower_options[i].c_str());
            wattroff(actionBox, A_REVERSE);
            
        }
        keyboard_input = wgetch(actionBox);
        switch(keyboard_input)
        {
            case KEY_UP:
                highlight = std::max(0, highlight-1);
                break;
            case KEY_DOWN:
                highlight = std::min(num_of_choices-1, highlight+1);
                break;
            default:
                break;
        }
    }
    return highlight;
}

void print_current_enemy(WINDOW *win, path*& path_start){
    path* current = path_start;
    mvwprintw(win, 2, 4, "Enemies");
    int row = 3;
    while (current && row < 19){
        if (current->enemy_on_top != NULL){
            mvwprintw(win, row, 4, "%s : %d", current->enemy_on_top->name.c_str(), current->enemy_on_top->health);
            row++;
        }
        current = current->next;
    }
    for (int i = row; i < 18; i++){
        mvwprintw(win, i, 4, "               ");
    }
}



void print_wave(WINDOW* win , int wave_num){
    std::vector <std::string> next_wave = wave(wave_num);
    mvwprintw(win, 2, 6, "Wave %d", wave_num);
    for (int i = 0; i < next_wave.size(); i++){
        mvwprintw(win, 4+i, 4, next_wave[i].c_str());
    }
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
    std::vector <std::string> choices = {"Play", "Help", "Quit"};
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

    return highlight + 1;
}

int loseScreen(int highlight = 0, int count = 1) {
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    std::string title1 = " __   __  _______  __   __    ___      _______  _______  _______ ";
    std::string title2 = "|  | |  ||       ||  | |  |  |   |    |       ||       ||       |";
    std::string title3 = "|  |_|  ||   _   ||  | |  |  |   |    |   _   ||  _____||    ___|";
    std::string title4 = "|       ||  | |  ||  |_|  |  |   |    |  | |  || |_____ |   |___ ";
    std::string title5 = "|_     _||  |_|  ||       |  |   |___ |  |_|  ||_____  ||    ___|";
    std::string title6 = "  |   |  |       ||       |  |       ||       | _____| ||   |___ ";
    std::string title7 = "  |___|  |_______||_______|  |_______||_______||_______||_______|";

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

    std::string choices[2] = {"Main Menu", "Quit"};
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
                return 0;
            }
            // If the user chooses to quit
            else if (highlight == 1) {
                erase();
                return 3;
            }
        }
    }
}

int winScreen(int highlight = 0, int count = 1) {
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    std::string title1 = "__   _____  _   _  __        _____ _   _ ";
    std::string title2 = "\\ \\ / / _ \\| | | | \\ \\      / /_ _| \\ | |";
    std::string title3 = " \\ V / | | | | | |  \\ \\ /\\ / / | ||  \\| |";
    std::string title4 = "  | || |_| | |_| |   \\ V  V /  | || |\\  |";
    std::string title5 = "  |_| \\___/ \\___/     \\_/\\_/  |___|_| \\_|";
    // std::string title6 = "  |   |  |       ||       |  |       ||       | _____| ||   |___ ";
    // std::string title7 = "  |___|  |_______||_______|  |_______||_______||_______||_______|";

    int titleX = (xMax - title1.length()) / 2 - 3;

    mvprintw(yMax / 2 - 7, titleX, title1.c_str());
    mvprintw(yMax / 2 - 6, titleX, title2.c_str());
    mvprintw(yMax / 2 - 5, titleX, title3.c_str());
    mvprintw(yMax / 2 - 4, titleX, title4.c_str());
    mvprintw(yMax / 2 - 3, titleX, title5.c_str());
    // mvprintw(yMax / 2 - 2, titleX, title6.c_str());
    // mvprintw(yMax / 2 - 1, titleX, title7.c_str());

    refresh();

    WINDOW* menuwin = newwin(7, xMax - 12, yMax - 10, 5);
    box(menuwin, 0, 0);


    keypad(menuwin, true);

    std::string choices[2] = {"Main Menu", "Quit"};
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
                return 0;
            }
            // If the user chooses to quit
            else if (highlight == 1) {
                erase();
                return 3;
            }
        }
    }
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
    
    int map[9][16];
    path* path_start = new path;
    std::vector<tower*> towers;
    readmap(map, mapnum, path_start);
    configpath(map, path_start);

    
    int highlight = 0;

    int health = 3;
    int wave_num = 1;
    int money = 100;

    noecho();
    curs_set(0);

    nodelay(mainBox, TRUE);
    nodelay(actionBox, TRUE);
    nodelay(towerBox, TRUE);
    nodelay(statsBox, TRUE);
    nodelay(confirmBox, TRUE);

    Coords selected;

    keypad(actionBox, true);

    while(1)
    {

        wclear(mainBox);
        wclear(actionBox);
        wclear(towerBox);
        wclear(statsBox);
        wclear(confirmBox);

        box(mainBox, ACS_VLINE, ACS_HLINE);
        box(actionBox, ACS_VLINE, ACS_HLINE);
        box(towerBox, ACS_VLINE, ACS_HLINE);
        box(statsBox, ACS_VLINE, ACS_HLINE);
        box(confirmBox, ACS_VLINE, ACS_HLINE);

        //Print the Map
        printMap(mainBox, path_start, towers);

        print_wave(towerBox, wave_num);
        
        // update stats, enemies, towers, the fun stuff ig, but they dont do anything rn
        mvwprintw(statsBox, 2, 2, "Health: (%d)", health);
        mvwprintw(statsBox, 2, 22, "Money: (%d)", money);
        mvwprintw(statsBox, 2, 42, "Wave: (%d)", wave_num);
        wrefresh(mainBox);
        wrefresh(actionBox);
        wrefresh(towerBox);
        wrefresh(statsBox);
        wrefresh(confirmBox);
        switch(chooseOption(actionBox, {"Start Wave", "Build", "Quit"}))
        {
            case 0: // Start Wave
            {   
                
                wclear(towerBox);
                wclear(actionBox);
                box(towerBox, ACS_VLINE, ACS_HLINE);
                box(actionBox, ACS_VLINE, ACS_HLINE);
                wrefresh(actionBox);
                int i = 0;
                int killed_enemies = 0;
                while (killed_enemies < wave(wave_num).size() && health > 0){
                    spawn_enemy(path_start, i, wave(wave_num));


                    printMap(mainBox, path_start, towers);
                    mvwprintw(statsBox, 2, 2, "Health: (%d)", health);
                    print_current_enemy(towerBox, path_start);

                    wrefresh(towerBox);
                    wrefresh(mainBox);
                    wrefresh(statsBox);
                    
                    i++;
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

                    attack_all(towers);
                    move(path_start, killed_enemies, health);
                }
                for (int i = 0; i < towers.size(); i++) // Reset attack cooldown
                {
                    towers[i]->cd = 0;
                }
                wave_num++;
                money += 10*wave_num;
                break;
            }
            case 1: // Edit
            {
                selected = selectSquare(mainBox, actionBox);
                if (map[selected.y][selected.x] == -1 && selected.x != -1){ // Empty Tile
                    wclear(towerBox);
                    box(towerBox, ACS_VLINE, ACS_HLINE);
                    mvwprintw(towerBox, 2, 4, "Empty Tile");
                    wrefresh(towerBox);
                    switch(chooseOption(actionBox, {"Place Tower", "Cancel"}))
                    {
                        case 0: // Place Tower
                        {
                            std::vector<std::string> tower_options = {"Mage", "Archer", "Sniper", "Cannon"};
                            int tower_option = choose_tower_option(actionBox, towerBox, tower_options);
                            
                            tower* t = new tower;
                            t->coordinates = std::make_pair(selected.y, selected.x);
                            t->create_new_tower(tower_options[tower_option], 1, path_start, money);
                            towers.push_back(t);
                            map[selected.y][selected.x] = towers.size()-1;
                            wclear(towerBox);
                            box(towerBox, ACS_VLINE, ACS_HLINE);
                            printMap(mainBox, path_start, towers);
                            mvwprintw(statsBox, 2, 22, "Money: (%d)", money);
                            wrefresh(mainBox);
                            wrefresh(towerBox);
                            wrefresh(statsBox);
                            break;
                        }
                        case 1: // Cancel
                        {  
                            break;
                        }
                    }
                }
                if (map[selected.y][selected.x] >= 0 && selected.x != -1){ // Tower
                    bool editing = true;
                    do 
                    {
                        wclear(towerBox);
                        box(towerBox, ACS_VLINE, ACS_HLINE);
                        int index = map[selected.y][selected.x];
                        tower* selected_tower = towers[index];
                        print_tower(towerBox, selected_tower);
                        wrefresh(towerBox);
                        

                        switch (chooseOption(actionBox, {"Upgrade", "Sell", "Cancel"}))
                        {
                            case 0: // Upgrade
                            {
                                if (money - selected_tower->cost < 0){
                                    break;
                                }
                                selected_tower->upgrade_tower(path_start, money);
                                wclear(towerBox);
                                mvwprintw(statsBox, 2, 22, "Money: (%d)", money);
                                wrefresh(statsBox);
                                box(towerBox, ACS_VLINE, ACS_HLINE);
                                break;
                            }
                            case 1: // Sell
                            {
                                money += selected_tower->cost/2;
                                towers.erase(towers.begin() + index);
                                for (int row = 0; row < 9; row++){
                                    for (int col = 0; col < 16; col++){
                                        if (map[row][col] > index){
                                            map[row][col]--;
                                        }
                                    }
                                }
                                map[selected.y][selected.x] = -1;

                                wclear(towerBox);
                                box(towerBox, ACS_VLINE, ACS_HLINE);
                                wrefresh(towerBox);
                                wrefresh(statsBox);
                                editing = false;
                                
                                break;
                            }
                            case 2: // Cancel
                            {
                                editing = false;
                                break;
                            }
                        }
                    }
                    while (editing);
                }
                break;
            }
            case 2: // Quit
            {
                return 0;
            }
        }
        wrefresh(mainBox);
        wrefresh(actionBox);
        wrefresh(towerBox);
        wrefresh(statsBox);
        wrefresh(confirmBox);
        if (health <= 0){
            clear();
            refresh();
            break;
        }
    }
    return loseScreen();
}

int helpscreen(WINDOW *win)
{
    int mid_x = win->_maxx / 2;
    int mid_y = win->_maxy / 2;
    WINDOW * mainBox = newwin(29, 82, 0, mid_x - 41 - 5);
    WINDOW * actionBox = newwin(10, 20, 0, mid_x + 41 - 5);
    WINDOW * towerBox = newwin(19, 20, 10, mid_x + 41 - 5);
    WINDOW * statsBox = newwin(5, 82, 29, mid_x - 41 - 5);
    WINDOW * confirmBox = newwin(5, 20, 29, mid_x + 41 - 5);
    return 0;
}

