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

int Grid::findShip(int x, int y) {
    for (int i = 0; i < ships_.size(); i++) {
        if (ships_[i].armor() != 0) {
            if (ships_[i].x() == x && ships_[i].y() == y) {
                return i;
            }
        }
    }
    return -1;
}

void Grid::showGrid(void) {
    for (int row = 0; row < 13; row++) {
        for (int column = 0; column < 13; column++) {
            std::cout << grid_[row][column] << "|" << std::endl;
        }
    }
}