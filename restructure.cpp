#include <iostream>
#include "path.h"
#include "map.h"

using namespace std;

int main(){
    tile map[9][16];
    readmap(map, 1);
    tile* path_start;
    int path_length = configpath(map, path_start);
    cout << "Path length: " << path_length << endl;
    return 0;
}