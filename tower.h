#ifndef TOWER_H
#define TOWER_H

#include <string>
#include <vector>
#include "map.h"
#include "enemy.h"
#include "path.h"


struct tower{
    std::string name;
    int color_id;
    char icon;
    int cost;
    int damage;
    int attackspeed;
    int range;
    std::string type[5];
    std::vector<struct tile*> tiles_covered;
    int last = tiles_covered.size() - 1;
    void mage(int level);
    void archer(int level);
    void sniper(int level);
    void cannon(int level);

    void CalculateDamage(){
      if (type[0] == "AOE"){
        for (int i = 0; i < tiles_covered.size(); i++){
          if (tiles_covered[i]->is_enemy() == true){
            if (tiles_covered[i]->enemy_on_top->type[0] == "Air" && type[2] == ""){
              continue;
            }
            else if (tiles_covered[i]->enemy_on_top->type[1] == "Camo" && type[3] == ""){
              continue;
            }
            tiles_covered[i]->enemy_on_top->health -= damage;
          }
        }
      }
      else if (type[0] == "Single"){
        if (tiles_covered[last]->is_enemy() == true){
          if (tiles_covered[last]->enemy_on_top->type[0] == "Air" && type[2] == ""){
        }
          else if (tiles_covered[last]->enemy_on_top->type[1] == "Camo" && type[3] == ""){
          }
          else{
            tiles_covered[last]->enemy_on_top->health -= damage;
          }
      }
    }
    };

#endif
