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

  void DefenceGrid::addShip(Ship &newShip) {
        // controlla che la griglia sia vuota in quelle celle
        if (!checkPosition(newShip.coord()))        
            return;                                 //TO DO: lanciare eccezione

        // scrive nella griglia il char del type della ship
        for (int i = 0; i < newShip.coord().size(); i++) {
            int rowSelected = newShip.coord(i).first;
            int columnSelected = newShip.coord(i).second;
            grid_[rowSelected][columnSelected] = newShip.type();
        }

        // Se va a buon fine la scrittura su griglia, inserisce la nave nel vector
        ships_.push_back(newShip);
  }