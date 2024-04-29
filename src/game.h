#ifndef GAME_H
#define GAME_H

// Include any necessary libraries or headers
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

// Declare any global constants or macros

// Declare any necessary classes or structs

// Declare any function prototypes

std::string getString(char x);
void printgametitle(WINDOW* titlewin, std::string name, int row);
void printMap(WINDOW *mainBox, path*& path_start, std::vector<tower*> towers);
std::pair<int, int> selectSquare(WINDOW *win, WINDOW* actionBox);
void print_tower(WINDOW* win, tower* tower_on_top);
void mapdisplay(WINDOW* mapwin, int count);
int mapscreen(WINDOW* titlewin);
int chooseOption(WINDOW *win, std::vector<std::string> choices, bool box_on);
int choose_tower_option(WINDOW* actionBox, WINDOW* towerBox, std::vector<std::string> tower_options);
void print_current_enemy(WINDOW *win, path*& path_start);
void print_wave(WINDOW* win, int wave_num, std::vector<std::string> next_wave);
int mainmenu(WINDOW *win);
int loseScreen();
int chestscreen();
int prizescreen(int dollars);
int winScreen();
int endscreen();
int playscreen(WINDOW *win, bool load);
void storydisplay(WINDOW* storywin, int count);
int storyscreen(WINDOW *win);
int helpscreen(WINDOW *win);


#endif // GAME_H