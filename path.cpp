#include "path.h"
using namespace std;

bool is_bounded(int row, int col) {
    return row >= 0 && row < 9 && col >= 0 && col < 16;
}

bool is_path(char map[9][16], int row, int col) {
    return (is_bounded(row, col)) &&
    (map[row][col] == 'X' || map[row][col] == 'S' || map[row][col] == 'E');
}

bool is_not_previous(pathtile*& previous, int row, int col) {
    return previous == NULL || previous->row != row || previous->col != col;
}

void set_start(char map[9][16], char target, pathtile*& pathhead) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 16; col++) {
            if (map[row][col] == 'S') {
                pathhead->row = row;
                pathhead->col = col;
                pathhead->next = NULL;
                return;
            }
        }
    }
}

void get_next(char map[9][16], pathtile*& current, pathtile*& previous) {
    int neighbors[4][2] = {
        {current->row+1, current->col},
        {current->row-1, current->col},
        {current->row, current->col+1},
        {current->row, current->col-1}
    };
    for (int i = 0; i < 4; i++) {
        int row = neighbors[i][0];
        int col = neighbors[i][1];
        if (is_path(map, row, col) && 
            is_not_previous(previous, row, col)) {
            pathtile* p = new pathtile;
            p->row = row;
            p->col = col;
            p->next = NULL;

            current->next = p;
            previous = current;
            current = p;
            break;
        }
    }
}

int configpath(char map[9][16], pathtile*& pathhead) {
    set_start(map, 'S', pathhead);
    pathtile* current = pathhead;
    pathtile* previous = NULL;
    int i = 1;
    while (map[current->row][current->col] != 'E') {
        get_next(map, current, previous);
        i++;
    }
    return i;
}