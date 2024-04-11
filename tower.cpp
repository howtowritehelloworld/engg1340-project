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
    // for (int i = -range; i <= range; i++){
    //     for (int j = -range; j <= range; j++){
    //         if (map[coordinates[0].first + i][coordinates[0].second + j] == 'X'){
    //             tiles_covered.push_back(make_pair(coordinates[0].first + i, coordinates[0].second + j));
    //         }
    //     }
    // }
    pathtile* current = pathhead;
    while (current != NULL){
        int row = current->row;
        int col = current->col;
        if (abs(row - coordinates[0].first) <= range && abs(col - coordinates[0].second) <= range){
            tiles_covered.push_back(make_pair(row, col));
        }
        current = current->next;
    }
}

// test code
int main(){
    pathtile* pathhead = new pathtile;
    tower* test = new tower;
    test->mage();
    test->coordinates = {{1,2}};
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
      cout << test->tiles_covered[i].first << " " << test->tiles_covered[i].second << endl;
    }
    return 0;
}
