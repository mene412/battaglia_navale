//Autore: Matteo

#include "../include/Ship.h"
#include "../include/Grid.h"
#include <vector>
#include <iostream>

Grid::Grid(void){
    ships_;
    // costriusco la matrice e inizializzo tutte le celle a ' '
    grid_[13][13];
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 13; j++) {
            grid_[i][j] = ' ';
        }
    }
    // prima colonna: lettere
    // non scrivo nulla nell'ultima riga (quindi i < 12)
    for (int i = 0; i < 12; i++) {
        if (i == 9)
            i += 2;
        grid_[i][0] = 'A' + i;
    }
    // ultima riga: numeri
    // non scrivo nulla nella priam colonna (quindi j = 1)
    for (int j = 1; j < 13; j++) {
        grid_[12][j] = j;
    }
}

int Grid::findShip(Coord x) {
    for (int i = 0; i < ships_.size(); i++) {
        if (ships_.at(i).armor() != 0) {
            if (ships_.at(i).center().X() == x.X() && ships_.at(i).center().Y() == x.Y()) {
                return i;
            }
        }
    }
    return -1;
}


std::string Grid::print_grid(void) {
    std::string grid = "";
    for (int row = 0; row < 13; row++) {
        for (int column = 0; column < 13; column++) {
            grid = grid + grid_[row][column] + "|\n";
        }
    }
    return grid;
}

std::ostream& operator<<(std::ostream& os, Grid a){
    os << a.print_grid();
}