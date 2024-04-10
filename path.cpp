
using namespace std;

struct pathtile {
    int row, col;
    pathtile* next;
    enemy* on_top = NULL;
};

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