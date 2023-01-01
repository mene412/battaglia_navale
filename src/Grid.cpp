
#include <iostream>
#include "Ship.h"
#include "Grid.h"
Grid::Grid(void){
    ships_[0];                              //Grid inizializzata con 0 navi e tutte caselle "mare"
    for(int i=1; i<=12; i++){
        for(int j=1; j<=12; j++){
            coord_[0][j]=j+'0';
            coord_[i][j]='*';
        }
        coord_[i][0]=conversion::NumToLett(i);
    }
    coord_[0][0]=' ';
}

void Grid::ShowGrid(void){
    for(int i=0; i<=12; i++){
        for(int j=0; j<=12; j++){
                std::cout<<coord_[i][j]<<"   ";
        }

    std::cout<<std::endl;
    }
    return;
}
bool operator== (Ship& Ship1, Ship& Ship2)
{
  for(int i=0; i<std::min(Ship1.GetDim(),Ship2.GetDim()); i++){
      for(int k=0; k<std::max(Ship1.GetDim(),Ship2.GetDim()); k++){
          if(Ship1.GetCoord(i, 0)==Ship2.GetCoord(k, 0) && Ship1.GetCoord(i, 1)==Ship2.GetCoord(k, 1))
              return true;
          }
    return false;
}
