#include <ncurses.h>
#include <iostream>
#include <cmath>
#include <string>
#include <unistd.h>
#include <vector>
#include <fstream>

struct Block{ // Structure for tower/ground placed, most of these variables dont do anything yet
    char icon;
    std::string type;
    std::string name;
    int level;
    int damage;
    int range;
    int cost;
};

struct Coords{ // I didnt know pair existed and this looks nicer
    int y;
    int x;
};

// The blocks
Block tower1 = {'A', "Tower", "tower1", 1, 5, 3, 100};
Block tower2 = {'B', "Tower", "tower2", 1, 5, 3, 100};
Block tower3 = {'C', "Tower", "tower3", 1, 5, 3, 100};
Block tower4 = {'D', "Tower", "tower4", 1, 5, 3, 100};
Block tower5 = {'E', "Tower", "tower5", 1, 5, 3, 100};
Block ground = {'X', "Ground", "ground", 0, 0, 0, 0};

int mainmenu(WINDOW *);
int playscreen(WINDOW *);
int helpscreen(WINDOW *);

void printMap(WINDOW *mainBox, std::vector<std::vector<Block>> gameMap) // Print the map of the game inside of the main window
{   
    // Define background colors for map
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    init_pair(2, COLOR_WHITE, COLOR_CYAN);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(5, COLOR_WHITE, COLOR_YELLOW);
    init_pair(6, COLOR_WHITE, COLOR_RED);

    // Looping each square to print the map
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 16; col++)
        {   
            
            switch(gameMap[row][col].icon)
            {
                case 'X':
                    wattron(mainBox, COLOR_PAIR(1)); // Turn on the color effect
                    for (int i = 0; i < 3; i++){
                        for (int k = 0; k < 5; k++){
                            mvwprintw(mainBox, 3*row+i+1, 5*col+k+1, " ");
                            }
                        }
                    wattroff(mainBox, COLOR_PAIR(1)); // Turn off the color effect
                    break;
                case 'O':
                    for (int i = 0; i < 3; i++){
                        for (int k = 0; k < 5; k++){
                            mvwprintw(mainBox, 3*row+i+1, 5*col+k+1, " ");
                            }
                        }
                    break;
                case 'A':
                    wattron(mainBox, COLOR_PAIR(2));
                    for (int i = 0; i < 3; i++){
                        for (int k = 0; k < 5; k++){
                            mvwprintw(mainBox, 3*row+i+1, 5*col+k+1, " ");
                            }
                        }
                    wattroff(mainBox, COLOR_PAIR(2));
                    mvwprintw(mainBox, 3*row+1+1, 5*col+1+1, "A");
                    mvwprintw(mainBox, 3*row+1+1, 5*col+2+1, "A");
                    mvwprintw(mainBox, 3*row+1+1, 5*col+3+1, "A");
                    break;
                case 'B':
                    wattron(mainBox, COLOR_PAIR(3));
                    for (int i = 0; i < 3; i++){
                        for (int k = 0; k < 5; k++){
                            mvwprintw(mainBox, 3*row+i+1, 5*col+k+1, " ");
                            }
                        }
                    wattroff(mainBox, COLOR_PAIR(3));
                    mvwprintw(mainBox, 3*row+1+1, 5*col+1+1, "B");
                    mvwprintw(mainBox, 3*row+1+1, 5*col+2+1, "B");
                    mvwprintw(mainBox, 3*row+1+1, 5*col+3+1, "B");
                    break;
                case 'C':
                    wattron(mainBox, COLOR_PAIR(4));
                    for (int i = 0; i < 3; i++){
                        for (int k = 0; k < 5; k++){
                            mvwprintw(mainBox, 3*row+i+1, 5*col+k+1, " ");
                            }
                        }
                    wattroff(mainBox, COLOR_PAIR(4));
                    mvwprintw(mainBox, 3*row+1+1, 5*col+1+1, "C");
                    mvwprintw(mainBox, 3*row+1+1, 5*col+2+1, "C");
                    mvwprintw(mainBox, 3*row+1+1, 5*col+3+1, "C");
                    break;
                case 'D':
                    wattron(mainBox, COLOR_PAIR(5));
                    for (int i = 0; i < 3; i++){
                        for (int k = 0; k < 5; k++){
                            mvwprintw(mainBox, 3*row+i+1, 5*col+k+1, " ");
                            }
                        }
                    wattroff(mainBox, COLOR_PAIR(5));
                    mvwprintw(mainBox, 3*row+1+1, 5*col+1+1, "D");
                    mvwprintw(mainBox, 3*row+1+1, 5*col+2+1, "D");
                    mvwprintw(mainBox, 3*row+1+1, 5*col+3+1, "D");
                    break;
                case 'E':
                    wattron(mainBox, COLOR_PAIR(6));
                    for (int i = 0; i < 3; i++){
                        for (int k = 0; k < 5; k++){
                            mvwprintw(mainBox, 3*row+i+1, 5*col+k+1, " ");
                            }
                        }
                    wattroff(mainBox, COLOR_PAIR(6));
                    mvwprintw(mainBox, 3*row+1+1, 5*col+1+1, "E");
                    mvwprintw(mainBox, 3*row+1+1, 5*col+2+1, "E");
                    mvwprintw(mainBox, 3*row+1+1, 5*col+3+1, "E");
                    break;
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
                selected.y--;
                if (selected.y == -1) {selected.y = 0;}
                break;
            case KEY_DOWN:
                selected.y++;
                if (selected.y == 9) {selected.y = 8;}
                break;
            case KEY_LEFT:
                selected.x--;
                if (selected.x == -1) {selected.x = 0;}
                break;
            case KEY_RIGHT:
                selected.x++;
                if (selected.x == 16) {selected.x = 15;}
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
                highlight--;
                if (highlight == -1)
                    highlight = 0;
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight == 3)
                    highlight = 2;
                break;
            default:
                break;
        }
        if (choice == 10) 
            break;
    }

    switch(highlight)
    {
        case 0:
            return 1;
        case 1:
            return 2;
        case 2:
            return 3;
    }
    return 0;
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

    std::vector<std::vector<Block>> gameMap(9, std::vector<Block>(16, {' ', "", "", 0, 0, 0, 0}));
    
    // Input the Map into the 2D vector

    std::string line;
    std::ifstream fin ("map.txt");
    fin.setf(std::ios::skipws);
    char c;
    
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 16; col++)
        {
            
            fin.get(c);
            while (c == '\n'){
                fin.get(c);
            }
            if (c == 'X') {
                gameMap[row][col] = ground;
            }
            else {
                gameMap[row][col].icon = c;
                gameMap[row][col].name = "Road";
                gameMap[row][col].type = "GROUND";
            }
            
        }   
    }

    fin.close();

    printMap(mainBox, gameMap);
    
    wrefresh(mainBox);

    keypad(actionBox, true);
    std::string choices[5] = {"Place Tower", "Upgrade Tower", "Move Tower", "Sell Tower", "Quit"};
    int actionChoice = 0;
    int towerChoice = 0;
    int highlight = 0;

    int health = 100;
    int wave = 1;
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

    while(1)
    {
        //Print the Map
        printMap(mainBox, gameMap);
        
        // update stats, enemies, towers, the fun stuff ig, but they dont do anything rn
        mvwprintw(statsBox, 2, 2, "Health: (%d)", health);
        mvwprintw(statsBox, 2, 22, "Money: (%d)", money);
        mvwprintw(statsBox, 2, 42, "Wave: (%d)", wave);

        for(int i = 0; i < 5; i++) // action box
        {   
            if (i == highlight) // highlight the choice being selected by the player
                wattron(actionBox, A_REVERSE);
            mvwprintw(actionBox, i+2, 4, choices[i].c_str());
            wattroff(actionBox, A_REVERSE);
        }
        actionChoice = wgetch(actionBox);
        
        wrefresh(mainBox);
        wrefresh(actionBox);
        wrefresh(towerBox);
        wrefresh(statsBox);
        wrefresh(confirmBox);

        // depending on key pressed, change the choice of the player
        switch(actionChoice)
        {
            case KEY_UP:
                highlight--;
                if (highlight == -1)
                    highlight = 0;
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight == 5)
                    highlight = 4;
                break;
            default:
                break;
        }
        
        if (actionChoice == 10) {
            actionChoice = 0;
            switch(highlight)
            {
                case 0: // Place Tower Sequence
                {   
                    
                    keypad(actionBox, false);
                    keypad(towerBox, true);
                    std::string towers[5] = {"Tower 1", "Tower 2", "Tower 3", "Tower 4", "Tower 5"};
                    highlight = 0;
                    while (towerChoice != 10)
                    {   
                        printMap(mainBox, gameMap);
                        for(int i = 0; i < 5; i++) // tower box
                        {
                            if (i == highlight)
                                wattron(towerBox, A_REVERSE);
                            mvwprintw(towerBox, i+2, 4, towers[i].c_str());
                            wattroff(towerBox, A_REVERSE);
                        }
                        towerChoice = wgetch(towerBox);
                        
                        switch(towerChoice)
                        {
                            case KEY_UP:
                                highlight--;
                                if (highlight == -1)
                                    highlight = 0;
                                break;
                            case KEY_DOWN:
                                highlight++;
                                if (highlight == 5)
                                    highlight = 4;
                                break;
                            default:
                                break;
                        }
                    }

                    selected = selectSquare(mainBox);

                    switch(highlight)
                    {
                        case 0: { // place tower 1
                            gameMap[selected.y][selected.x] = tower1;
                        }   
                            break;
                        case 1:
                            gameMap[selected.y][selected.x] = tower2;
                            break; // place tower 2
                        case 2:
                            gameMap[selected.y][selected.x] = tower3;
                            break; // place tower 3
                        case 3:
                            gameMap[selected.y][selected.x] = tower4;
                            break; // place tower 4
                        case 4:
                            gameMap[selected.y][selected.x] = tower5;
                            break; // place tower 5
                    }

                    wclear(towerBox);
                    box(towerBox, ACS_VLINE, ACS_HLINE);
                    keypad(towerBox, false);
                    keypad(actionBox, true);
                    towerChoice = 0;
                    highlight = 0;
                    break;
                }

                case 1:
                    selected = selectSquare(mainBox); // Upgrade Tower Sequence
                    if (gameMap[selected.y][selected.x].type == "Tower" && gameMap[selected.y][selected.x].level < 3) {
                        gameMap[selected.y][selected.x].level++;
                    break;
                    }
                case 2:
                    selected = selectSquare(mainBox); // Move Tower Sequence
                    if (gameMap[selected.y][selected.x].type == "Tower") {
                        selected2 = selectSquare(mainBox);
                        if (gameMap[selected2.y][selected2.x].name == "ground") {
                            gameMap[selected2.y][selected2.x] = gameMap[selected.y][selected.x];
                            gameMap[selected.y][selected.x] = ground;
                        }
                    }
                    break;
                case 3: {
                    selected = selectSquare(mainBox);  // Sell Tower Sequence
                    if (gameMap[selected.y][selected.x].type == "Tower"){
                        gameMap[selected.y][selected.x] = ground;
                    }                        
                    break;
                }
                    
                case 4:
                    return 0; // Quit Sequence

            }
        }
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
