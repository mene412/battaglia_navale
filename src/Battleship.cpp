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
  if(AttGrid[x][y]==' '){
  if(DefGrid[x][y]==' '){
      AttGrid[x][y]='O';
      return false;         //colpo non andato a segno
  }
  else {
      for(int i=0; i<DefGrid.ships_.size(); i++){
        for(int j=0; i<DefGrid.ships_[i].dim();j++){
          if(ships()[i].coord(j).first==x && ships()[i].coord(j).second==y){
            if(ships()[i].armor()>1){
              ships()[i].decArmor();
              DefGrid[x][y]=std::tolower(ships()[i].type());     //scrive il carattere minuscolo al posto del maiuscolo
            }
            else{
              for(int k=0; k<ships_[i].dim(); k++)
                DefGrid[ships()[i].coord(k).first][ships()[i].coord(k).second]=' ';   //"reinizializza la grid dove è affondata la nave"
              DefGrid.ships().erase(i);                                                //rimuove la nave abbattuta dal vettore
            }
            }
          }
        }
        AttGrid[x][y]='X';
        return true;                      //colpo andato a segno
      }
    }
    else{
      return false; //DA rivedere
    }                        //Come gestiamo il "colpo ripetuto"? Per esempio se le coordinate x,y generate dal computer sono quelle di un "pezzo" di nave già colpito?
  }
