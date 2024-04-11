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

// test code
int main(){
    pathtile* pathhead = new pathtile;
    tower* test = new tower;
    test->mage();
    test->coordinates = {{1,5}};
    char map[9][16] = {
      {'.','.','.','.','.','.','.','.','.','.', '.', '.', '.', '.', '.', '.'},
      {'.','.','.','.','.','.','.','.','.','.', '.', '.', '.', '.', '.', '.'},
      {'S','X','X','.','X','X','X','X','X','X', 'X', '.', '.', '.', '.', '.'},
      {'.','.','X','.','X','.','.','.','.','.', 'X', '.', '.', '.', '.', '.'},
      {'.','.','X','.','X','X','X','X','X','.', 'X', '.', '.', '.', '.', '.'},
      {'.','.','X','.','.','.','.','.','X','.', 'X', '.', '.', '.', '.', '.'},
      {'.','.','X','X','.','.','.','.','X','.', 'X', '.', '.', '.', '.', '.'},
      {'.','.','.','X','X','.','.','.','X','.', 'X', 'X', 'X', 'X', 'X', 'E'},
      {'.','.','.','.','X','X','X','X','X','.', '.', '.', '.', '.', '.', '.'},
    };
    int path_length = configpath(map, pathhead);
    test->check_coverage(pathhead);
    for (int i = 0; i < test->tiles_covered.size(); i++){
      cout << test->tiles_covered[i]->row << " " << test->tiles_covered[i]->col << endl;
    }
    return 0;
}
