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
    void knight();
    void dragon();
    void ghost();

};

#endif // ENEMY_H
