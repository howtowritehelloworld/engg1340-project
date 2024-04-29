#ifndef ENEMY_H
#define ENEMY_H
#include <string>
#include <vector>
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

std::vector<std::string> tutor_wave(int wave_num);
std::vector<std::string> wave(int wave_num);

#endif // ENEMY_H
