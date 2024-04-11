#include <iostream>
#include <vector>
using namespace std;

void check(vector <pair<int,int>> &tiles, vector<pair<int,int>> coor, int range, char map[][16]){
  for (int i = -range; i <= range; i++){
    for (int j = -range; j <= range; j++){
      if (map[coor[0].first + i][coor[0].second + j] == 'X'){
        tiles.push_back(make_pair(coor[0].first + i, coor[0].second + j));
      }
    }
  }


}
int main(){
  vector<pair<int,int>> tiles;
  vector<pair<int,int>> towercoordinates = {{3,3}};
  int range = 1;
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
  check(tiles, towercoordinates, range, map);
  for (int i = 0; i < tiles.size(); i++){
    cout << tiles[i].first << " " << tiles[i].second << endl;
  }
}
