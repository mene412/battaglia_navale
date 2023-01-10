// Autore:
#include "Ship.h"
#include "Battleship.h"
#include "DefenceGrid.h"
#include "AttackGrid.h"
#include "Grid.h"
#include <vector>
Battleship::Battleship(void){
    type_='C';
    dim_=5;
    armor_=5;
    set_coord();
}
bool Battleship::fire(AttackGrid& AttGrid, DefenceGrid& DefGrid, int x,int y){
    if(AttGrid.grid()[x][y]==' '){
        if(DefGrid.grid()[x][y]==' '){
            AttGrid.grid()[x][y]='O';
      return false;         //colpo non andato a segno
  }
  else {
      for(int i=0; i<DefGrid.ships().size(); i++){
        for(int j=0; i<DefGrid.ships()[i].dim();j++){
            if(DefGrid.ships()[i].coord(j).first==x && DefGrid.ships()[i].coord(j).second==y){
                if(DefGrid.ships()[i].armor()>1){
                    DefGrid.ships()[i].decArmor();
                    DefGrid.grid()[x][y]=std::tolower(DefGrid.ships()[i].type());     //scrive il carattere minuscolo al posto del maiuscolo
            }
            else{
                for(int k=0; k<DefGrid.ships()[i].dim(); k++)
                    DefGrid.grid()[DefGrid.ships()[i].coord(k).first][DefGrid.ships()[i].coord(k).second]=' ';   //"reinizializza la grid dove è affondata la nave"
                DefGrid.ships().erase(ships().begin()+i);                                                //rimuove la nave abbattuta dal vettore
            }
            }
          }
        }
      AttGrid.grid()[x][y]='X';
        return true;                      //colpo andato a segno
      }
    }
    else{
      return false; //DA rivedere
    }                        //Come gestiamo il "colpo ripetuto"? Per esempio se le coordinate x,y generate dal computer sono quelle di un "pezzo" di nave già colpito?
  }
