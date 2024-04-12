#include "tower.h"

using namespace std;
void tower::mage()
{
    name = "Mage";
    icon = 'M';
    cost = 4;
    damage = 2;
    attackspeed = 2;
    range = 1;
    type[0] = "AOE"; type[1] = "Ground"; type[2] = "Air";
}

void tower::archer()
{
    name = "Archer";
    icon = 'A';
    cost = 3;
    damage = 3;
    attackspeed = 1;
    range = 1;
    type[0] = "Single"; type[1] = "Ground"; type[2] = "Air";     
}

void tower::sniper()
{
    name = "Sniper";
    icon = 'S';
    cost = 5;
    damage = 6;
    attackspeed = 3;
    range = 2;
    type[0] = "Single"; type[1] = "Ground"; type[2] = "Air"; type[3] = "Camo";
}

void tower::cannon()
{
    name = "Cannon";
    icon = 'C';
    cost = 4;
    damage = 4;
    attackspeed = 3;
    range = 1;
    type[0] = "AOE"; type[1] = "Ground";
}

void tower::check_coverage(pathtile*& pathhead){
    pathtile* current = pathhead;
    while (current != NULL){
        int row = current->row;
        int col = current->col;
        if (abs(row - coordinates[0].first) <= range && abs(col - coordinates[0].second) <= range){
            tiles_covered.push_back(current);
        }
        current = current->next;
    }
}

void configure_tower(std::string tname, int row, int col, std::vector<tower*>& towers, pathtile*& pathhead){
    tower* new_tower = new tower;
    
    if (tname == "Mage"){
        new_tower->mage();
    }
    else if (tname == "Archer"){
        new_tower->archer();
    }
    else if (tname == "Sniper"){
        new_tower->sniper();
    }
    else if (tname == "Cannon"){
        new_tower->cannon();
    }

    new_tower->coordinates.push_back({row, col});

    new_tower->check_coverage(pathhead);

    towers.push_back(new_tower);
}

void print_towers(std::vector<tower*> towers){
    for (int i = 0; i < towers.size(); i++){
        cout << "***************************" << endl;
        cout << "Tower " << towers[i]->name << " at " << towers[i]->coordinates[0].first << " " << towers[i]->coordinates[0].second << " covers:" << endl;
        for (int j = 0; j < towers[i]->tiles_covered.size(); j++){
            cout << "Tile " << towers[i]->tiles_covered[j]->row << " " << towers[i]->tiles_covered[j]->col << endl;
        }
        cout << "***************************" << endl;
    }
}
// test code
int main(){
    pathtile* pathhead = new pathtile;

    char map[9][16];
    readmap(map, 1);
    int path_length = configpath(map, pathhead);

    vector<tower*> towers;
    configure_tower("Mage", 2, 3, towers, pathhead);
    configure_tower("Sniper", 0, 0, towers, pathhead);
    cout << "Testing" << endl;
    print_towers(towers);
    updatemap(map, pathhead, towers);
    printmap(map);

    return 0;
}
