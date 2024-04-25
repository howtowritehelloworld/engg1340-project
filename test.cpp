#include <ncurses.h>
#include <iostream>
#include <cmath>
#include <string>
#include <unistd.h>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <time.h>
#include "map.h"
#include "path.h"
#include "tower.h"
#include "enemy.h"
#include "chooseMap.h"
#include "save.h"

struct Coords{ // I didnt know pair existed and this looks nicer (to me)
    int y;
    int x;
};


int mainmenu(WINDOW *);
int playscreen(WINDOW *, bool load);
int helpscreen(WINDOW *);
int storyscreen(WINDOW *);
int endscreen();

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
    if (wave_num <= 14)
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
    else
    {
        srand(time(0)); 
        int stage = wave_num/10;
        int max_weight = wave_num*(stage+5);
        int total_weight = 0;
        std::vector<std::string> enemy_lst= {};
        while (total_weight <= max_weight)
        { 
            int enemytype = rand()%4;
            int lev = rand()%(stage+2) + 1;
            switch(enemytype)
            {
                case(0):
                    enemy_lst.push_back("K"+std::to_string(lev));
                    total_weight +=  2*lev;
                    break;
                case(1):
                    enemy_lst.push_back("D"+std::to_string(lev));
                    total_weight +=  3*lev;
                    break;
                case(2):
                    enemy_lst.push_back("G"+std::to_string(lev));
                    total_weight +=  3*lev;
                    break;
                case(3):
                    enemy_lst.push_back("V"+std::to_string(lev));
                    total_weight +=  4*lev;
                    break;
            }
        }
        return enemy_lst;
    }        
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

    endscreen();
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
        wmove(win, 3*selected.y+2, 5*selected.x+3);
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
    for (int i = 2; i < 18; i++){
        mvwprintw(win, i, 4, "               ");
    }
    mvwprintw(win, 2, 4, "Enemies");
    int row = 3;
    while (current && row < 19){
        if (current->enemy_on_top != NULL){
            mvwprintw(win, row, 4, "%s : %d", current->enemy_on_top->name.c_str(), current->enemy_on_top->health);
            row++;
        }
        current = current->next;
    }
}



void print_wave(WINDOW* win, int wave_num, std::vector<std::string> next_wave){
    mvwprintw(win, 2, 6, "Wave %d", wave_num); 
    for (int i = 0; i < 19 && i < next_wave.size(); i++){
        mvwprintw(win, 4+i, 4, next_wave[i].c_str());
    }
}

int mainmenu(WINDOW *win)
{   
std::string title1 = " _  ___                 _                          __   ______ _     _            _       ";
std::string title2 = "| |/ (_)               | |                        / _| |  ____| |   | |          (_)      ";
std::string title3 = "| ' / _ _ __   __ _  __| | ___  _ __ ___     ___ | |_  | |__  | | __| | ___  _ __ _  __ _ ";
std::string title4 = "|  < | | '_ \\ / _` |/ _` |/ _ \\| '_ ` _ \\   / _ \\|  _| |  __| | |/ _` |/ _ \\| '__| |/ _` |";
std::string title5 = "| . \\| | | | | (_| | (_| | (_) | | | | | | | (_) | |   | |____| | (_| | (_) | |  | | (_| |";
std::string title6 = "|_|\\_\\_|_| |_|\\__, |\\__,_|\\___/|_| |_| |_|  \\___/|_|   |______|_|\\__,_|\\___/|_|  |_|\\__,_|";
std::string title7 = "               __/ |                                                                      ";
std::string title8 = "              |___/                                                                       ";

 
    int mid_x = win->_maxx / 2;
    int mid_y = win->_maxy / 2;

    mvwprintw(win, mid_y - 10, (mid_x - title1.length() / 2), title1.c_str());
    mvwprintw(win, mid_y - 9, (mid_x - title2.length() / 2), title2.c_str());
    mvwprintw(win, mid_y - 8, (mid_x - title3.length() / 2), title3.c_str());
    mvwprintw(win, mid_y - 7, (mid_x - title4.length() / 2), title4.c_str());
    mvwprintw(win, mid_y - 6, (mid_x - title5.length() / 2), title5.c_str());
    mvwprintw(win, mid_y - 5, (mid_x - title6.length() / 2), title6.c_str());
    mvwprintw(win, mid_y - 4, (mid_x - title7.length() / 2), title7.c_str());
    mvwprintw(win, mid_y - 3, (mid_x - title8.length() / 2), title8.c_str());

    WINDOW * menuwin= newwin(6, 16, mid_y, mid_x - 8);
    refresh();
    wrefresh(menuwin);

    keypad(menuwin, true);
    std::vector <std::string> choices = {"New Game", "Load Game", "Tutorial", "Quit"};
    int choice;
    int highlight = 0;

    noecho();
    curs_set(0);

    while(1)
    {   
        for(int i = 0; i < 4; i++)
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
                highlight = std::min(3, highlight+1);
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
                return 4;
            }
        }
    }
}

int chestscreen(int highlight = 0, int count = 1)
{
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    std::string title1 = "   ____  _____  ______ _   _                   _____ _    _ ______  _____ _______ ";
    std::string title2 = "  / __ \\|  __ \\|  ____| \\ | |       /\\        / ____| |  | |  ____|/ ____|__   __|";
    std::string title3 = " | |  | | |__) | |__  |  \\| |      /  \\      | |    | |__| | |__  | (___    | |   ";
    std::string title4 = " | |  | |  ___/|  __| | . ` |     / /\\ \\     | |    |  __  |  __|  \\___ \\   | |   ";
    std::string title5 = " | |__| | |    | |____| |\\  |    / ____ \\    | |____| |  | | |____ ____) |  | |   ";
    std::string title6 = "  \\____/|_|    |______|_| \\_|   /_/    \\_\\    \\_____|_|  |_|______|_____/   |_|   ";

    std::string chest1 = "       ____________          ____________          ____________       ";
	std::string chest2 = "      /            \\        /            \\        /            \\     ";
	std::string chest3 = "     /______________\\      /______________\\      /______________\\    ";
	std::string chest4 = "     |     ___      |      |     ___      |      |     ___      |     ";
	std::string chest5 = "     |____| 1 |_____|      |____| 2 |_____|      |____| 3 |_____|     ";
	std::string chest6 = "     |    |___|     |      |    |___|     |      |    |___|     |     ";
	std::string chest7 = "     |______________|      |______________|      |______________|     ";

    int titleX = (xMax - title1.length()) / 2 - 3;
    int chestX = ((xMax - chest1.length()) / 2 - 3);

    mvprintw(yMax / 2 - 10, titleX, title1.c_str());
    mvprintw(yMax / 2 - 9, titleX, title2.c_str());
    mvprintw(yMax / 2 - 8, titleX, title3.c_str());
    mvprintw(yMax / 2 - 7, titleX, title4.c_str());
    mvprintw(yMax / 2 - 6, titleX, title5.c_str());
    mvprintw(yMax / 2 - 5, titleX, title6.c_str());

    mvprintw(yMax / 2 - 3, chestX, chest1.c_str());
    mvprintw(yMax / 2 - 2, chestX, chest2.c_str());
    mvprintw(yMax / 2 - 1, chestX, chest3.c_str());
    mvprintw(yMax / 2 - 0, chestX, chest4.c_str());
    mvprintw(yMax / 2 + 1, chestX, chest5.c_str());
    mvprintw(yMax / 2 + 2, chestX, chest6.c_str());
    mvprintw(yMax / 2 + 3, chestX, chest7.c_str());

    refresh();

    WINDOW* menuwin = newwin(7, xMax - 12, yMax - 10, 5);
    box(menuwin, 0, 0);


    keypad(menuwin, true);

    std::string choices[3] = {"CHEST 1", "CHEST 2", "CHEST 3"};
    int choice;

    while (1)
    {
  
        for (int i = 0; i < 3; i++) {
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
                if (highlight == 3) {
                    highlight = 2;
                }
                break;
            default:
                break;
        }

        // When pressing Enter
        if (choice == 10) {

            if (highlight == 0) {
                erase();
                clear();
                refresh();
                return 0;
            }

            else if (highlight == 1) {
                erase();
                clear();
                refresh();
                return 1;
            }

            else if (highlight == 2){
                erase();
                clear();
                refresh();
                return 2;
            }
        }
    }
}

int prizescreen(int dollars) 
{
	initscr();
	int rows, cols;
	getmaxyx(stdscr, rows, cols); 

	int middleRow = rows / 2;
	int middleCol = (cols - 16) / 2; 

	
	mvprintw(middleRow, middleCol, "You got %d dollars", dollars);

	mvprintw(middleRow + 6, middleCol + 8, "Press any key to continue...");

	refresh();
    noecho();
	getch(); 
	clear();
    refresh();
    return 0;
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

    std::string choices[3] = {"Continue (infinite waves)", "Main Menu", "Quit"};
    int choice;

    while (1) {
  
        for (int i = 0; i < 3; i++) {
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
                if (highlight == 3) {
                    highlight = 2;
                }
                break;
            default:
                break;
        }

        // When pressing Enter
        if (choice == 10) {
            // main menu
            if (highlight == 1) {
                erase();
                return 0;
            }
            // quit
            else if (highlight == 2) {
                erase();
                return 3;
            }
            // continue
            else if (highlight == 0){
                erase();
                clear();
                refresh();
                return 4;
            }
        }
    }
}

int endscreen()
{
	initscr();
	cbreak();
	noecho();

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

	std::string title1 = "  _____             __     __                                _          _ ";
	std::string title2 = " / ____|            \\ \\   / /               /\\              (_)        | |";
	std::string title3 = "| (___   ___  ___    \\ \\_/ /__  _   _      /  \\   __ _  __ _ _ _ __    | |";
	std::string title4 = " \\___ \\ / _ \\/ _ \\    \\   / _ \\| | | |    / /\\ \\ / _` |/ _` | | '_ \\   | |";
	std::string title5 = " ____) |  __/  __/     | | (_) | |_| |   / ____ \\ (_| | (_| | | | | |  |_|";
	std::string title6 = "|_____/ \\___|\\___|     |_|\\___/ \\__,_|  /_/    \\_\\__, |\\__,_|_|_| |_|  (_)";
	std::string title7 = "                                                   __/ |                   ";
	std::string title8 = "                                                  |___/                    ";

    	int titleX = (xMax - title1.length()) / 2 - 3;

    mvprintw(yMax / 2 - 7, titleX, title1.c_str());
    mvprintw(yMax / 2 - 6, titleX, title2.c_str());
    mvprintw(yMax / 2 - 5, titleX, title3.c_str());
    mvprintw(yMax / 2 - 4, titleX, title4.c_str());
    mvprintw(yMax / 2 - 3, titleX, title5.c_str());
    mvprintw(yMax / 2 - 2, titleX, title6.c_str());
    mvprintw(yMax / 2 - 1, titleX, title7.c_str());
	mvprintw(yMax / 2    , titleX, title8.c_str());
	mvprintw(yMax / 2 - 15, titleX, "Press any key to exit...");

	// Wait for user input
	getch();

	// End ncurses
	endwin();

	return 0;
}

int playscreen(WINDOW *win, bool load = false)
{   
    int mid_x = win->_maxx / 2;
    int mid_y = win->_maxy / 2;
    WINDOW * mainBox = newwin(29, 82, 0, mid_x - 41 - 5);
    WINDOW * actionBox = newwin(10, 20, 0, mid_x + 41 - 5);
    WINDOW * towerBox = newwin(24, 20, 10, mid_x + 41 - 5);
    WINDOW * statsBox = newwin(5, 82, 29, mid_x - 41 - 5);
    
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    int health, wave_num, money, mapnum;
    int map[9][16];
    std::vector<tower*> towers;
    path* path_start = new path;
    if (!load){
        WINDOW* titlewin = newwin(8, xMax - 12, 1, 5);
        refresh();
        mapnum = mainscreen(titlewin);
        health = 3;
        wave_num = 1;
        money = 100;
        readmap(map, mapnum, path_start);
        configpath(map, path_start);

    }
    else {
        loadGame(health, wave_num, money, mapnum, towers);
        int tempmoney = 99999999;
        readmap(map, mapnum, path_start);
        configpath(map, path_start);
        for (int i = 0; i < towers.size(); i++){
            map[towers[i]->coordinates.first][towers[i]->coordinates.second] = i;
            tower* t = new tower;
            t = towers[i];
            t->create_new_tower(t->name, t->level, path_start, tempmoney);
        }
    }
    
    int highlight = 0;

    box(mainBox, ACS_VLINE, ACS_HLINE);
    box(actionBox, ACS_VLINE, ACS_HLINE);
    box(towerBox, ACS_VLINE, ACS_HLINE);
    box(statsBox, ACS_VLINE, ACS_HLINE);
    refresh();
    wrefresh(mainBox);
    wrefresh(actionBox);
    wrefresh(towerBox);
    wrefresh(statsBox);
    
    

    noecho();
    curs_set(0);

    nodelay(mainBox, TRUE);
    nodelay(actionBox, TRUE);
    nodelay(towerBox, TRUE);
    nodelay(statsBox, TRUE);

    Coords selected;

    keypad(actionBox, true);

    while(1)
    {
        std::vector<std::string> current_wave = wave(wave_num);

        wclear(mainBox);
        wclear(actionBox);
        wclear(towerBox);
        wclear(statsBox);

        box(mainBox, ACS_VLINE, ACS_HLINE);
        box(actionBox, ACS_VLINE, ACS_HLINE);
        box(towerBox, ACS_VLINE, ACS_HLINE);
        box(statsBox, ACS_VLINE, ACS_HLINE);

        //Print the Map
        printMap(mainBox, path_start, towers);
        
        print_wave(towerBox, wave_num, current_wave);
        
        // update stats, enemies, towers, the fun stuff ig, but they dont do anything rn
        mvwprintw(statsBox, 2, 2, "Health: (%d)", health);
        mvwprintw(statsBox, 2, 22, "Money: (%d)", money);
        mvwprintw(statsBox, 2, 42, "Wave: (%d)", wave_num);
        wrefresh(mainBox);
        wrefresh(actionBox);
        wrefresh(towerBox);
        wrefresh(statsBox);
        switch(chooseOption(actionBox, {"Start Wave", "Build/Edit", "Quit"}))
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
                while (killed_enemies < current_wave.size() && health > 0){
                    spawn_enemy(path_start, i, current_wave);


                    printMap(mainBox, path_start, towers);
                    mvwprintw(statsBox, 2, 2, "Health: (%d)", health);
                    print_current_enemy(towerBox, path_start);

                    wrefresh(towerBox);
                    wrefresh(mainBox);
                    wrefresh(statsBox);
                    
                    i++;
                    std::this_thread::sleep_for(std::chrono::milliseconds(700));

                    attack_all(towers);
                    move(path_start, killed_enemies, health);
                }
                for (int i = 0; i < towers.size(); i++) // Reset attack cooldown
                {
                    towers[i]->cd = 0;
                }
                wave_num++;
                money += 8*wave_num;
                if ((wave_num-1) % 3 == 0 && health > 0)
                {
                    srand(time(0));
                    int chest_content[3] = {(rand()%wave_num)*10+rand()%wave_num, (rand()%wave_num)*10+rand()%wave_num, (rand()%wave_num)*10+rand()%wave_num};
                    clear();
                    refresh();
                    int choice = chestscreen();
                    money += chest_content[choice];
                    prizescreen(chest_content[choice]);
                }
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
        if (health <= 0){
            clear();
            refresh();
            break;
        }
        if (wave_num == 15)
        {
            clear();
            refresh();
            int choise = winScreen();
            if (choise == 0 || choise == 3)
            {
                return choise;
            }
            else
            {
                continue;
            }
        }
        if (wave_num % 6 == 0)
        {
            clear();
            refresh();
            chestscreen();
        }
        saveGame(health, wave_num, money, mapnum, towers);
    }
    return loseScreen();
}


void storydisplay(WINDOW* storywin, int count) {
    wclear(storywin);
    std::ifstream storyfile("Story/Story_" + std::to_string(count) + ".txt");
    std::string line;
    int y = 0;
    while (getline(storyfile, line)) {
        mvwprintw(storywin, y, 0, line.c_str());
        y++;
    }
    storyfile.close();
}

int storyscreen(WINDOW *win){
    clear();
    int count = 1;
    int mid_x = win->_maxx / 2;
    int mid_y = win->_maxy / 2;
    WINDOW * mainBox = newwin(29, 82, 0, mid_x - 41 - 5);
    WINDOW * storywin = newwin(6, 76, mid_y - 6, mid_x - 37 - 5);
    box(mainBox, ACS_VLINE, ACS_HLINE);
    refresh();
    wrefresh(mainBox);
    storydisplay(storywin, count);
    wrefresh(storywin);
    while (true){
    int choice = wgetch(mainBox);
    if (choice == 10){
        if (count < 6){
            count++;
            storydisplay(storywin, count);
            wrefresh(storywin);
        } else {
            return helpscreen(stdscr);
        }
    }
  }
  return 0;
}




int helpscreen(WINDOW *win)
{
    int mid_x = win->_maxx / 2;
    int mid_y = win->_maxy / 2;
    WINDOW * mainBox = newwin(29, 82, 0, mid_x - 41 - 5);
    WINDOW * actionBox = newwin(10, 20, 0, mid_x + 41 - 5);
    WINDOW * towerBox = newwin(24, 20, 10, mid_x + 41 - 5);
    WINDOW * statsBox = newwin(5, 82, 29, mid_x - 41 - 5);
    
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    box(mainBox, ACS_VLINE, ACS_HLINE);
    box(actionBox, ACS_VLINE, ACS_HLINE);
    box(towerBox, ACS_VLINE, ACS_HLINE);
    box(statsBox, ACS_VLINE, ACS_HLINE);
    
    refresh();
    wrefresh(mainBox);
    wrefresh(actionBox);
    wrefresh(towerBox);
    wrefresh(statsBox);
    
    int map[9][16];
    path* path_start = new path;
    std::vector<tower*> towers;
    readmap(map, 7, path_start);
    configpath(map, path_start);

    printMap(mainBox, path_start, towers);

    wrefresh(mainBox);
    wrefresh(actionBox);
    wrefresh(towerBox);
    wrefresh(statsBox);

    int highlight = 0;

    int health = 99999999;
    int wave_num = 1;
    int money = 10000000;

    noecho();
    curs_set(0);

    nodelay(mainBox, TRUE);
    nodelay(actionBox, TRUE);
    nodelay(towerBox, TRUE);
    nodelay(statsBox, FALSE);

    Coords selected;

    keypad(actionBox, true);

    mvwprintw(statsBox, 1, 1, "Welcome to the tutorial of our game");
    mvwprintw(statsBox, 2, 1, "Press Any Key to continue >>");
    wrefresh(statsBox);
    wgetch(statsBox);

    wclear(statsBox);
    box(statsBox, ACS_VLINE, ACS_HLINE);
    mvwprintw(statsBox, 1, 1, "Let's build our first tower >>");
    wgetch(statsBox);
    wrefresh(statsBox);

    wclear(statsBox);
    box(statsBox, ACS_VLINE, ACS_HLINE);
    mvwprintw(statsBox, 1, 1, "On the action menu at the top right corner");
    mvwprintw(statsBox, 2, 1, "Click Build to start placing towers");
    wrefresh(statsBox);

    while (1){

        box(mainBox, ACS_VLINE, ACS_HLINE);
        box(actionBox, ACS_VLINE, ACS_HLINE);
        box(towerBox, ACS_VLINE, ACS_HLINE);
        box(statsBox, ACS_VLINE, ACS_HLINE);

        printMap(mainBox, path_start, towers);
        wrefresh(mainBox);
        wrefresh(actionBox);
        wrefresh(towerBox);
        wrefresh(statsBox);

        bool built = false;

        switch(chooseOption(actionBox, {"Start Wave", "Build", "Quit"}))
        {
            case 0: // start wave
            wclear(statsBox);
            mvwprintw(statsBox, 1, 1, "Let's not start the wave right now");
            mvwprintw(statsBox, 2, 1, "Let's build a tower first");
            wrefresh(statsBox);  
            break;  
            
            case 1: // Edit
            {   
                wclear(statsBox);
                box(statsBox, ACS_VLINE, ACS_HLINE);
                mvwprintw(statsBox, 1, 1, "Now select the tile you want to place the tower on");
                mvwprintw(statsBox, 2, 1, "Use arrow keys to move the cursor and press enter to select");
                wrefresh(statsBox); 
                selected = selectSquare(mainBox, actionBox);
                if (map[selected.y][selected.x] == -1 && selected.x != -1){ // Empty Tile
                    wclear(statsBox);
                    box(statsBox, ACS_VLINE, ACS_HLINE);
                    mvwprintw(statsBox, 2, 1, "Good Spot! Now click Place Tower");
                    wrefresh(statsBox); 
                    wclear(towerBox);
                    box(towerBox, ACS_VLINE, ACS_HLINE);
                    mvwprintw(towerBox, 2, 4, "Empty Tile");
                    wrefresh(towerBox);
                    switch(chooseOption(actionBox, {"Place Tower", "Cancel"}))
                    {
                        case 0: // Place Tower
                        {   
                            wclear(statsBox);
                            box(statsBox, ACS_VLINE, ACS_HLINE);
                            mvwprintw(statsBox, 2, 1, "Now you can select any tower you want to place!");
                            wrefresh(statsBox); 
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
                            // mvwprintw(statsBox, 2, 22, "Money: (%d)", money);
                            wrefresh(mainBox);
                            wrefresh(towerBox);
                            // wrefresh(statsBox);
                            break;
                        }
                        case 1: // Cancel
                        {  
                            wclear(statsBox);
                            box(statsBox, ACS_VLINE, ACS_HLINE);
                            mvwprintw(statsBox, 2, 1, "Why did you cancel? Go back please");
                            wrefresh(statsBox); 
                            break;
                        }
                    }
                }
                if (map[selected.y][selected.x] >= 0 && selected.x != -1){ // Tower
                    wclear(statsBox);
                    box(statsBox, ACS_VLINE, ACS_HLINE);
                    mvwprintw(statsBox, 1, 1, "Here is the upgrade screen");
                    mvwprintw(statsBox, 2, 1, "To reopen it just select a tower after you click Build");
                    mvwprintw(statsBox, 3, 1, "Click cancel to move on to the next part");
                    wrefresh(statsBox); 
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
                                wclear(statsBox);
                                box(statsBox, ACS_VLINE, ACS_HLINE);
                                mvwprintw(statsBox, 1, 1, "You've upgraded your tower! Normally it costs money");
                                mvwprintw(statsBox, 2, 1, "but it's the tutorial right now so I'll let it fly this time");
                                wrefresh(statsBox); 
                                break;
                            }
                            case 1: // Sell
                            {
                                wclear(statsBox);
                                box(statsBox, ACS_VLINE, ACS_HLINE);
                                mvwprintw(statsBox, 2, 1, "Bruh don't sell your tower, click cancel");
                                wrefresh(statsBox); 
                                
                                break;
                            }
                            case 2: // Cancel
                            {
                                editing = false;
                                built = true;
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

        if (built)
            break;

        // loaded map
        // to do list:
        // welcome
        // build tutorial
    }

    wclear(statsBox);
    box(statsBox, ACS_VLINE, ACS_HLINE);
    mvwprintw(statsBox, 2, 1, "Well done! You've placed down your first tower!");
    mvwprintw(statsBox, 2, 1, "You can go ahead and start the wave or place more towers!");
    wrefresh(statsBox);

    bool finishTutorial = false;

    while(1)
    {

        wclear(mainBox);
        wclear(actionBox);
        wclear(towerBox);
        wclear(statsBox);

        box(mainBox, ACS_VLINE, ACS_HLINE);
        box(actionBox, ACS_VLINE, ACS_HLINE);
        box(towerBox, ACS_VLINE, ACS_HLINE);
        box(statsBox, ACS_VLINE, ACS_HLINE);

        //Print the Map
        printMap(mainBox, path_start, towers);

        // print_wave(towerBox, wave_num);
        
        // update stats, enemies, towers, the fun stuff ig, but they dont do anything rn
        // mvwprintw(statsBox, 2, 2, "Health: (%d)", health);
        // mvwprintw(statsBox, 2, 22, "Money: (%d)", money);
        // mvwprintw(statsBox, 2, 42, "Wave: (%d)", wave_num);
        wrefresh(mainBox);
        wrefresh(actionBox);
        wrefresh(towerBox);
        // wrefresh(statsBox);
        switch(chooseOption(actionBox, {"Start Wave", "Build", "Quit"}))
        {
            case 0: // Start Wave
            {   
                switch(wave_num)
                {
                    case 1:
                    {
                        wclear(statsBox);
                        box(statsBox, ACS_VLINE, ACS_HLINE);
                        mvwprintw(statsBox, 1, 1, "The first enemy here is a Knight.");
                        mvwprintw(statsBox, 2, 1, "It's pretty basic so I'm sure you're able to handle it.");
                        wrefresh(statsBox);
                        break;
                    }
                    case 2:
                    {
                        wclear(statsBox);
                        box(statsBox, ACS_VLINE, ACS_HLINE);
                        mvwprintw(statsBox, 1, 1, "This enemy is a Dragon.");
                        mvwprintw(statsBox, 2, 1, "It's flying so cannons cannot hit it.");
                        wrefresh(statsBox);
                        break;
                    }
                    case 3:
                    {
                        wclear(statsBox);
                        box(statsBox, ACS_VLINE, ACS_HLINE);
                        mvwprintw(statsBox, 1, 1, "Next up is a Ghost.");
                        mvwprintw(statsBox, 2, 1, "Ghosts are camoflauged. Only 2 towers can hit it.");
                        wrefresh(statsBox);
                        break;
                    }
                    case 4:
                    {
                        wclear(statsBox);
                        box(statsBox, ACS_VLINE, ACS_HLINE);
                        mvwprintw(statsBox, 1, 1, "The last enemy here is a Vampire.");
                        mvwprintw(statsBox, 2, 1, "It's both flying and camoflauged.");
                        wrefresh(statsBox);
                        break;
                    }
                }
                wclear(towerBox);
                wclear(actionBox);
                box(towerBox, ACS_VLINE, ACS_HLINE);
                box(actionBox, ACS_VLINE, ACS_HLINE);
                wrefresh(actionBox);
                int i = 0;
                int killed_enemies = 0;
                while (killed_enemies < tutor_wave(wave_num).size() && health > 0){
                    spawn_enemy(path_start, i, tutor_wave(wave_num));


                    printMap(mainBox, path_start, towers);
                    // mvwprintw(statsBox, 2, 2, "Health: (%d)", health);
                    print_current_enemy(towerBox, path_start);

                    wrefresh(towerBox);
                    wrefresh(mainBox);
                    // wrefresh(statsBox);
                    
                    i++;
                    std::this_thread::sleep_for(std::chrono::milliseconds(700));

                    attack_all(towers);
                    move(path_start, killed_enemies, health);
                }
                for (int i = 0; i < towers.size(); i++) // Reset attack cooldown
                {
                    towers[i]->cd = 0;
                }
                wave_num++;
                if (wave_num == 5) {
                    finishTutorial = true;
                }
                money += 10*wave_num;
                break;
            }
            case 1: // Build
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
                            // mvwprintw(statsBox, 2, 22, "Money: (%d)", money);
                            wrefresh(mainBox);
                            wrefresh(towerBox);
                            // wrefresh(statsBox);
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

        if (finishTutorial){
            wclear(mainBox);
            wclear(actionBox);
            wclear(towerBox);
            wclear(statsBox);

            box(mainBox, ACS_VLINE, ACS_HLINE);
            box(actionBox, ACS_VLINE, ACS_HLINE);
            box(towerBox, ACS_VLINE, ACS_HLINE);
            box(statsBox, ACS_VLINE, ACS_HLINE);

            printMap(mainBox, path_start, towers);

            wrefresh(mainBox);
            wrefresh(actionBox);
            wrefresh(towerBox);
            box(statsBox, ACS_VLINE, ACS_HLINE);
            mvwprintw(statsBox, 1, 1, "Well done! You've finshed the tutorial!");
            mvwprintw(statsBox, 2, 1, "You now know all the things you need to play! >>");
            wrefresh(statsBox);
            wgetch(statsBox);
            clear();
            return 0;
        }
    }

    return 0;
}
