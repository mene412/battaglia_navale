//Autore: Matteo

#include "../include/Grid.h"
#include "../include/DefenceGrid.h"
#include "../include/Ship.h"
#include "../include/Battleship.h"
#include "../include/HelpShip.h"
#include "../include/ExplorationSubmarine.h"
#include "../include/Coord.h"


DefenceGrid::DefenceGrid(void)
    : Grid{}
{}

bool DefenceGrid::checkPosition(std::vector<Coord> coordinates) {
    for (int i = 0; i < coordinates.size(); i++) {
        int checkRow = coordinates[i].X();        // numero riga
        int checkColumn = coordinates[i].Y();    // numero colonna
        if (grid_[checkRow][checkColumn] != ' ') {
            // se la cella non è vuota, ritorna false
            return false;
        }
    }
    return true;
}



void DefenceGrid::addShip(Ship newShip) {
    if (!checkPosition(newShip.coord())) {      //da errore in compilazione perhè coord è, per ora, un vector di vector di int
                                                // deve essere invece un vector di Coord
        return;                                 //TO DO: lanciare eccezione
    }
    for (int i = 0; i < newShip.coord().size(); i++) {
        int rowSelected = newShip.coord().at(i).X();
        int columnSelected = newShip.coord().at(i).Y();
        grid_[rowSelected][columnSelected] = newShip.type();
    }
    ships_.push_back(&newShip);
}

std::ostream& operator<<(std::ostream& os, DefenceGrid a){
    os << "Griglia di difesa\n\n" << a.print_grid() << std::endl;
}