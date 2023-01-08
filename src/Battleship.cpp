// Autore:
#include "Ship.h"
#include "Battleship.h"
Battleship::Battleship(void){
    type_='C';
    dim_=5;
    armor_=5;
    SetCoord();
}
bool Battleship::fire(AttackGrid& AttGrid, DefenceGrid& DefGrid, int x, int y){
  if(DefGrid[x][y]==' '){
      AttGrid[x][y]='O';
      return false;         //colpo non andato a segno
  }
  else{
      for(int i=0; i<DefGrid.ships_.size(); i++){
        for(int j=0; i<DefGrid.ships_[i].dim();j++){
          if(ships_[i].coord(j).first==x && ships_[i].coord(j).second==y){
            if(ships_[i].armor()>1){
              ships_[i].decArmor();
              DefGrid[x][y]=std::tolower(ships_[i].type());     //scrive il carattere minuscolo al posto del maiuscolo
            }
            else{
              for(int k=0; k<ships_[i].dim(); k++)
                DefGrid[ships_[i].coord_(k).first][ships_[i].coord_(k).second]=' ';   //"reinizializza la grid dove è affondata la nave"
              DefGrid.ships_.erase(i);                                                //rimuove la nave abbattuta dal vettore
            }
            }
          }
        }
        AttGrid[x][y]='X';
        return true;                      //colpo andato a segno
      }

  }
