#include "enemy.h"
using namespace std;

void enemy::knight(int level)
{
    /*

    Input:
    level : Level of the enemy to be created

    Process:
    Sets the attributes for a knight enemy according to level

    Output:
    Modified struct enemy

    */
    name = "Knight";
    icon = 'K';
    health = 9*level;
    weight = 2*level;
    money = 2*level;
    type[0] = "Ground"; type[1] = "";
}

void enemy::dragon(int level)
{
    /*

    Input:
    level : Level of the enemy to be created

    Process:
    Sets the attributes for a dragon enemy according to level

    Output:
    Modified struct enemy

    */
    name = "Dragon";
    icon = 'D';
    health = 12*level;
    weight = 4*level;
    money = 4*level;
    type[0] = "Air"; type[1] = "";
}

void enemy::vampire(int level)
{

    /*

    Input:
    level : Level of the enemy to be created

    Process:
    Sets the attributes for a vampire enemy according to level

    Output:
    Modified struct enemy

    */
    name = "Vampire";
    icon = 'V';
    health = 9*level;
    weight = 4*level;
    money = 4*level;
    type[0] = "Air"; type[1] = "Camo";
}

void enemy::ghost(int level)
{
    /*

    Input:
    level : Level of the enemy to be created

    Process:
    Sets the attributes for a ghost enemy according to level

    Output:
    Modified struct enemy

    */
    name = "Ghost";
    icon = 'G';
    health = 9*level;
    weight = 3*level;
    money = 3*level;
    type[0] = "Ground"; type[1] = "Camo";
}

std::vector<std::string> tutor_wave(int wave_num)
{
    /*
    
    Input:
    wave_num : wave number of the tutorial

    Process:
    Find the corresponding tutorial wave based on wave_num

    Output:
    A vector of strings containing the enemies (Name and Level) in the wave

    */
    std::vector<std::vector<std::string>> tutor_wave = 
    {
        {"K1"},
        {"D1"},
        {"G1"},
        {"V1"},
    };
    return tutor_wave[wave_num-1];
}

std::vector<std::string> wave(int wave_num)
{
    /*
    
    Input:
    wave_num : wave number of the game

    Process:
    Find the corresponding wave based on wave_num
        wave_num <= 14: Predefined waves
        wave_num > 14: Random waves
    
    Output:
    A vector of strings containing the enemies (Name and Level) in the wave
    
    */
    if (wave_num <= 14)
    {
        std::vector<std::vector<std::string>> wave = 
        {
            {"K1"}, 
            {"K1", "K1"}, 
            {"K1", "K1", "K1"},
            {"D1"},
            {"D1", "K2"},
            {"D1", "D1", "K2"},
            {"G1", "G1"},
            {"G2", "D2", "K3"},
            {"G1", "G2", "D2", "K3"},
            {"V1", "V1"},
            {"V1", "V2", "G2", "D3", "K3"},
            {"V3", "V3", "G3", "G3"},
            {"K3", "K3", "K3", "D3", "D3", "D3"},
            {"K3", "K3", "D3", "D3", "G3", "G3", "V3", "V3"},
        };
        return wave[wave_num-1];
    }
    else
    {
        srand(time(0)); 
        int stage = wave_num/5;
        int max_weight = wave_num*(stage+4);
        int total_weight = 0;
        std::vector<std::string> enemy_lst= {};
        while (total_weight <= max_weight)
        { 
            int enemytype = rand()%4;
            int lev = rand()%(2)+stage;
            switch(enemytype)
            {
                case(0):
                    enemy_lst.push_back("K"+std::to_string(lev));
                    total_weight +=  2*lev;
                    break;
                case(1):
                    enemy_lst.push_back("D"+std::to_string(lev));
                    total_weight +=  3*lev;
                    break;
                case(2):
                    enemy_lst.push_back("G"+std::to_string(lev));
                    total_weight +=  3*lev;
                    break;
                case(3):
                    enemy_lst.push_back("V"+std::to_string(lev));
                    total_weight +=  4*lev;
                    break;
            }
        }
        return enemy_lst;
    }        
}