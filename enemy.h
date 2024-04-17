#ifndef ENEMY_H
#define ENEMY_H
#include <string>
struct enemy
{
    std::string name;
    char icon;
    int health;
    int weight;
    std::string type[5];
    void knight(int level);
    void dragon(int level);
    void ghost(int level);

};

#endif // ENEMY_H
