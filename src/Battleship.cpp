// Autore:
#include "Ship.h"
#include "Battleship.h"
#include "DefenceGrid.h"
#include "AttackGrid.h"
#include "Grid.h"
#include <vector>

Battleship::Battleship(Coord front, Coord back)
  : Ship{front, back}
{
    type_='C';
    dim_=5;
    armor_=5;
    distance_ = 2;
}
void Battleship::fire(AttackGrid& att_grid, DefenceGrid& def_grid, Coord cord){
    for(int i = 0; i<def_grid.ships().size(); i++){
        for(int j = 0; j<def_grid.ships().at(i)->coord().size(); j++){
            if(def_grid.ships().at(i)->coord().at(j) == cord){
                att_grid.add('x', cord);
                def_grid.ships().at(i) -> dec_armor();
                if(full_ship(def_grid, i)){
                    titanic(att_grid, def_grid, i);
                }
                return;
            }
        }
    }
    att_grid.add('o', cord);
    return;    
}

bool Battleship::full_ship(DefenceGrid& def_grid, int pos) const{
    if(def_grid.ships().at(pos)->armor() == 0){
        return true;
    }   
    return false;
}

void Battleship::titanic(AttackGrid& att_grid, DefenceGrid& def_grid, int pos){
    for(int i = 0; i<def_grid.ships().at(pos)->coord().size(); i++){
        att_grid.add('X', def_grid.ships().at(pos)->coord().at(i));
    }
    def_grid.ships().erase(def_grid.ships().begin()+pos);
    return;
}