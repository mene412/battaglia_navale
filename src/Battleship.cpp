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
bool Battleship::fire(AttackGrid& AttGrid, DefenceGrid& DefGrid, Coord cord){
    if(AttGrid.grid()[cord.X()][cord.Y()]==' '){
        if(DefGrid.grid()[cord.X()][cord.Y()]==' '){
            AttGrid.grid()[cord.X()][cord.Y()]='O';
            return false;                                                           //colpo non andato a segno
        }
        else {
            for(int i=0; i<DefGrid.ships().size(); i++){
                for(int j=0; i<DefGrid.ships()[i].dim();j++){
                    if(DefGrid.ships()[i].coord(j).X()==cord.X() && DefGrid.ships()[i].coord(j).Y()==cord.Y()){
                        if(DefGrid.ships()[i].armor()>1){
                            DefGrid.ships()[i].decArmor();
                            DefGrid.grid()[cord.X()][cord.Y()]=std::tolower(DefGrid.ships()[i].type());
                        }
                        else{
                            for(int k=0; k<DefGrid.ships()[i].dim(); k++)
                                DefGrid.grid()[DefGrid.ships()[i].coord(k).X()][DefGrid.ships()[i].coord(k).Y()]=' ';
                                DefGrid.ships().erase(DefGrid.ships().begin()+i);
                        }
                    }
                }
            }
            AttGrid.grid()[x][y]='X';
            return true;
      }
    }
    else
      return false;
  }
