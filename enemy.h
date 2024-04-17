#ifndef ENEMY_H
#define ENEMY_H
#include <string>
struct enemy
{
    std::string name;
    char icon;
    int health;
    int weight;
    int money;
    std::string type[5];
    void knight(int level);
    void dragon(int level);
    void ghost(int level);
    void vampire(int level);
};

#endif // ENEMY_H
