  //Autore: Matteo
  
  #include "../include/Grid.h"
  #include "../include/DefenceGrid.h"
  #include "../include/Ship.h"
  #include "../include/Battleship.h"
  #include "../include/HelpShip.h"
  #include "../include/ExplorationSubmarine.h"
  
  bool DefenceGrid::checkPosition(std::vector<std::pair<int,int>> coordinates) {
        for (int i = 0; i < coordinates.size(); i++) {
            int checkRow = coordinates[i].first;        // numero riga
            int checkColumn = coordinates[i].second;    // numero colonna
            if (grid_[checkRow][checkColumn] != ' ') {
                // se la cella non è vuota, ritorna false
                return false;
            }
        }
        return true;
  }

  void DefenceGrid::addShip(Ship newShip) {
        if (!checkPosition(newShip.coord()))        //da errore in compilazione perhè coord è, per ora, un vector di vector di int
            return;                                 //TO DO: lanciare eccezione
        for (int i = 0; i < newShip.coord().size; i++) {
            int rowSelected = newShip.coord().first;
            int columnSelected = newShip.coord().second;
            grid_[rowSelected][columnSelected] = newShip.type();
        }
  }

//   void DefenceGrid::SetGrid(void){
//       for(int i=0; i<3; i++){
//           std::cout<<"Corazzata"<<std::endl;
//           Battleship c;
//           if(CheckShip(c)){
//               PositionShip(c);
//               std::cout<<"OK"<<std::endl;           //"Ok" messo solo per controllo codice
//           }
//           else i--;
//       }
//       for(int i=0; i<3; i++){
//           std::cout<<"Nave Supporto"<<std::endl;
//           HelpShip s;
//           if(CheckShip(s)){
//               PositionShip(s);
//               std::cout<<"OK"<<std::endl;           //"Ok" messo solo per controllo codice
//           }
//           else i--;
//       }
//       for(int i=0; i<2; i++){
//           std::cout<<"Sottomarino"<<std::endl;
//           ExplorationSubmarine d;
//           if(CheckShip(d)){
//               PositionShip(d);
//               std::cout<<"OK"<<std::endl;           //"Ok" messo solo per controllo codice
//           }
//           else i--;
//       }
//       return;
//     }