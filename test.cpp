#include <ncurses.h>
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
#include "save.h"

std::string getString(char x)
{
    std::string s(1, x);
 
    return s;   
}

int mainmenu(WINDOW *);
int playscreen(WINDOW *, bool load);
int helpscreen(WINDOW *);
int storyscreen(WINDOW *);
int endscreen();
int mapscreen(WINDOW* titlewin);
void mapdisplay(WINDOW* mapwin, int count);
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
        int stage = wave_num/5;
        int max_weight = wave_num*(stage+4);
        int total_weight = 0;
        std::vector<std::string> enemy_lst= {};
        while (total_weight <= max_weight)
        { 
            int enemytype = rand()%4;
            int lev = rand()%(2)+stage;
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




void printgametitle(WINDOW* titlewin, std::string name, int row) {
    int yMax, xMax;
    getmaxyx(titlewin, yMax, xMax);
    std::ifstream inputfile("art/" + name + ".txt");
    std::string line;
    while (std::getline(inputfile, line)) {
        mvwprintw(titlewin, row, (xMax - line.length()) / 2, line.c_str());
        row++;
    }
    inputfile.close();
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

std::pair<int, int> selectSquare(WINDOW *win, WINDOW* actionBox) // Allow player to control cursor to select the tile they want to interact with
{   
    wclear(actionBox);
    box(actionBox, ACS_VLINE, ACS_HLINE);
    mvwprintw(actionBox, 3, 2, "Move: Arrow Keys");
    mvwprintw(actionBox, 5, 3, "Select: Enter");
    mvwprintw(actionBox, 7, 1, "Cancel: Backspace");
    wrefresh(actionBox);
    keypad(win, true);
    int ch;
    std::pair<int, int> selected = {0, 0};
    
    curs_set(1);
    wmove(win, 3*selected.first+2, 6*selected.second+4);
    while (1) {
        ch = wgetch(win);
        switch(ch) {
            case KEY_UP:
                selected.first = std::max(0, selected.first-1);
                break;
            case KEY_DOWN:
                selected.first = std::min(8, selected.first+1);
                break;
            case KEY_LEFT:
                selected.second = std::max(0, selected.second-1);
                break;
            case KEY_RIGHT:
                selected.second = std::min(15, selected.second+1);
                break;
            case KEY_BACKSPACE:
                curs_set(0);
                return {-1, -1};
        }
        wmove(win, 3*selected.first+2, 5*selected.second+3);
        wrefresh(win);
        if (ch == 10)
            break;
    }
    curs_set(0);
    return selected;
}

void print_tower(WINDOW* win, tower* tower_on_top){
    for (int i = 2; i < 18; i++){
        mvwprintw(win, i, 4, "               ");
    }
    mvwprintw(win, 2, 4, "%s", tower_on_top->name.c_str());
    mvwprintw(win, 4, 4, "Level: %d", tower_on_top->level);
    mvwprintw(win, 5, 4, "Damage: %d", tower_on_top->damage);
    mvwprintw(win, 6, 4, "Range: %d", tower_on_top->range);
    mvwprintw(win, 7, 4, "Cost: %d", tower_on_top->cost);
    std::string speeds[3] = {"Fast", "Medium", "Slow"};
    mvwprintw(win, 8, 4, "Speed: %s", speeds[tower_on_top->attackspeed-1].c_str());
    for (int i = 0; i < 4; i++){
        mvwprintw(win, 10+i, 4, tower_on_top->type[i].c_str());
    }
}

void mapdisplay(WINDOW* mapwin, int count) {
    wclear(mapwin);
    std::ifstream mapfile("map/map_" + std::to_string(count) + ".txt");
    std::string line;
    int y = 0;
    while (getline(mapfile, line)) {
        mvwprintw(mapwin, y, 0, line.c_str());
        y++;
    }
    mapfile.close();
}

int mapscreen(WINDOW* titlewin) {
    // Print "Choose a map" title
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    printgametitle(titlewin, "choosemap", 1);

    // Refresh the title window
    wrefresh(titlewin);

    // Create a window for the map display
    WINDOW* mapwin = newwin(11, 32, 8, xMax/2 - 16);
    mapdisplay(mapwin, 0);
    wrefresh(mapwin);

    // Create a window for the menu
    WINDOW* menuwin = newwin(7, xMax - 12, yMax - 17, 5);
    box(menuwin, 0, 0);

    // For arrow keys
    keypad(menuwin, true);

    int choice;
    int count = 1;
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
        mvprintw(yMax/2, xMax/2 - 5, std::to_string(count).c_str());
        refresh();
    }

    // Clear the screen and print the count
    clear();
    refresh();
    delwin(mapwin);
    delwin(menuwin);
    return count;     
}

int chooseOption(WINDOW *win, std::vector<std::string> choices, bool box_on = true){
    keypad(win, true);
    wclear(win);
    if (box_on){
        box(win, ACS_VLINE, ACS_HLINE);
    }
    
    int highlight = 0;
    int keyboard_input = 0;
    int num_of_choices = choices.size();

    int yMax, xMax;
    getmaxyx(win, yMax, xMax);
    int x, y;
    int maxLen = 0;
    for (int i = 0; i < num_of_choices; i++){
        if (choices[i].length() > maxLen){
            maxLen = choices[i].length();
        }
    }
    x = (xMax - maxLen)/2;
    y = (yMax-num_of_choices)/2;

    while (keyboard_input != 10){
        for (int i = 0; i < num_of_choices; i++){
            if (i == highlight) {
                wattron(win, A_REVERSE);
            }
            mvwprintw(win, i + y, x, choices[i].c_str());
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
                if (i != num_of_choices-1){
                    tower* temp_tower = new tower;
                    temp_tower->sample_tower(tower_options[i]);
                    print_tower(towerBox, temp_tower);
                    delete temp_tower;
                }
                else {
                    for (int i = 2; i < 18; i++){
                        mvwprintw(towerBox, i, 4, "               ");
                    }
                }
                wrefresh(towerBox);
            }
            mvwprintw(actionBox, i + 2, 4, tower_options[i].c_str());
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
 
    int mid_x = win->_maxx / 2;
    int mid_y = win->_maxy / 2;

    printgametitle(win, "gametitle", mid_y - 10);

    WINDOW * menuwin= newwin(6, 16, mid_y, mid_x - 8);
    refresh();
    wrefresh(menuwin);

    keypad(menuwin, true);
    std::vector <std::string> choices = {"New Game", "Load Game", "Tutorial", "Quit"};
    int choice;
    int highlight = 0;

    noecho();
    curs_set(0);

    return chooseOption(menuwin, choices, false) + 1;
}

int loseScreen() {
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    printgametitle(stdscr, "youlose", yMax / 2 - 7);

    refresh();

    WINDOW* menuwin = newwin(7, xMax - 12, yMax - 10, 5);
    box(menuwin, 0, 0);


    keypad(menuwin, true);

    std::vector<std::string> choices = {"Main Menu", "Quit"};
    int choice = chooseOption(menuwin, choices, false);
    
    // If the user chooses the main menu
    erase();
    if (choice == 0) {
        return 0;
    }
    // If the user chooses to quit
    else if (choice == 1) {
        return 4;
    }
    return 4;
}

int chestscreen()
{
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    printgametitle(stdscr, "openachest", yMax/2 - 10);
    printgametitle(stdscr, "chest", yMax/2 - 3);

    refresh();

    WINDOW* menuwin = newwin(7, xMax - 12, yMax - 10, 5);
    box(menuwin, 0, 0);


    keypad(menuwin, true);

    std::vector<std::string> choices = {"CHEST 1", "CHEST 2", "CHEST 3"};
    int choice = chooseOption(menuwin, choices, false);

    erase();
    clear();
    refresh();
    return choice;
}

int prizescreen(int dollars) 
{
	initscr();
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

	int middleCol = (xMax - 18) / 2;

    printgametitle(stdscr, "prizescreen", yMax / 2 - 7);
	
	mvprintw(yMax / 2 + 4, middleCol, "You got %d dollars!", dollars);

	mvprintw(yMax / 2 + 8, middleCol + 12, "Press any key to continue...");

	refresh();
    noecho();
	getch(); 
	clear();
    refresh();
    return 0;
}

int winScreen() {
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    printgametitle(stdscr, "youwin", yMax / 2 - 7);

    refresh();

    WINDOW* menuwin = newwin(7, xMax - 12, yMax - 10, 5);
    box(menuwin, 0, 0);


    keypad(menuwin, true);

    std::vector<std::string> choices = {"Continue (infinite waves)", "Main Menu", "Quit"};
    int choice = chooseOption(menuwin, choices, false);
    int options[] = {-1, 0, 4};
    clear();
    refresh();
    return options[choice];
}

int endscreen()
{
	initscr();
	cbreak();
	noecho();

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    printgametitle(stdscr, "seeyouagain", yMax / 2 - 7);
	mvprintw(yMax / 2 + 15, (xMax-12)/2-3, "Press any key to exit...");

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
        mapnum = mapscreen(titlewin);
        health = 3;
        wave_num = 1;
        money = 100;
        readmap(map, mapnum, path_start);
        configpath(map, path_start);

    }
    else {
        loadGame(health, wave_num, money, mapnum, towers);
        if (health == -1){
            return 0;
        }
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

    std::pair<int, int> selected;

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
                if (map[selected.first][selected.second] == -1 && selected.second != -1){ // Empty Tile
                    wclear(towerBox);
                    box(towerBox, ACS_VLINE, ACS_HLINE);
                    mvwprintw(towerBox, 2, 4, "Empty Tile");
                    wrefresh(towerBox);
                    switch(chooseOption(actionBox, {"Place Tower", "Cancel"}))
                    {
                        case 0: // Place Tower
                        {
                            std::vector<std::string> tower_options = {"Mage", "Archer", "Sniper", "Cannon", "Cancel"};
                            int tower_option = choose_tower_option(actionBox, towerBox, tower_options);
                            
                            tower* t = new tower;
                            t->coordinates = selected;
                            t->create_new_tower(tower_options[tower_option], 1, path_start, money);
                            if (t->name != ""){
                                towers.push_back(t);
                                map[selected.first][selected.second] = towers.size()-1;
                            }
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
                if (map[selected.first][selected.second] >= 0 && selected.second != -1){ // Tower
                    bool editing = true;
                    do 
                    {
                        wclear(towerBox);
                        box(towerBox, ACS_VLINE, ACS_HLINE);
                        int index = map[selected.first][selected.second];
                        tower* selected_tower = towers[index];
                        print_tower(towerBox, selected_tower);
                        wrefresh(towerBox);
                        

                        switch (chooseOption(actionBox, {"Upgrade", "Sell", "Cancel"}))
                        {
                            case 0: // Upgrade
                            {
                                if ( money - selected_tower->cost < 0){
                                    break;
                                }
                                selected_tower->upgrade_tower(selected_tower->name, selected_tower->level, path_start, money);
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
                                map[selected.first][selected.second] = -1;

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
            int choice = winScreen();
            if (choice != -1){
                return choice;
            }
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

    std::pair<int, int> selected;

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
                if (map[selected.first][selected.second] == -1 && selected.second != -1){ // Empty Tile
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
                            t->coordinates = std::make_pair(selected.first, selected.second);
                            t->create_new_tower(tower_options[tower_option], 1, path_start, money);
                            towers.push_back(t);
                            map[selected.first][selected.second] = towers.size()-1;
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
                if (map[selected.first][selected.second] >= 0 && selected.second != -1){ // Tower
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
                        int index = map[selected.first][selected.second];
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
                                selected_tower->upgrade_tower(selected_tower->name, selected_tower->level, path_start, money);
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
                if (map[selected.first][selected.second] == -1 && selected.second != -1){ // Empty Tile
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
                            t->coordinates = std::make_pair(selected.first, selected.second);
                            t->create_new_tower(tower_options[tower_option], 1, path_start, money);
                            towers.push_back(t);
                            map[selected.first][selected.second] = towers.size()-1;
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
                if (map[selected.first][selected.second] >= 0 && selected.second != -1){ // Tower
                    bool editing = true;
                    do 
                    {
                        wclear(towerBox);
                        box(towerBox, ACS_VLINE, ACS_HLINE);
                        int index = map[selected.first][selected.second];
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
                                selected_tower->upgrade_tower(selected_tower->name, selected_tower->level, path_start, money);
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
                                map[selected.first][selected.second] = -1;

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
