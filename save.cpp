#include "save.h"
using namespace std;

void saveGame(int health, int wave_num, int money, int map_num, vector<tower*> towers) {
    ofstream savefile("save.txt");
    if (savefile.is_open()) { 
        savefile << health << endl;
        savefile << wave_num << endl;
        savefile << money << endl;
        savefile << map_num;
        if (towers.size() == 0) {
            savefile.close();
            return;
        }
        savefile << endl;
        for (int i = 0; i<towers.size()-1; i++) {
            savefile << towers[i]->name << " "<< towers[i]->level <<" "<< towers[i]->coordinates.first << " " <<towers[i]->coordinates.second;
            savefile << endl;
            }
        savefile << towers[towers.size()-1]->name << " "<< towers[towers.size()-1]->level <<" "<< towers[towers.size()-1]->coordinates.first << " " <<towers[towers.size()-1]->coordinates.second;

        
        
    }
    savefile.close();
}

void loadGame(int &health, int &wave_num , int &money, int& map_num, vector<tower*> &towers) {
    ifstream loadfile("save.txt");
    loadfile >> health >> wave_num >> money>> map_num;
    int i = 0;
    while (!loadfile.eof()){
        tower* t = new tower;
        loadfile >> t->name >> t->level;
        loadfile >> t->coordinates.first >> t->coordinates.second;
        towers.push_back(t);
    }
    loadfile.close();
}
