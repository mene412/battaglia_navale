//Autore: Matteo

#include "../include/Ship.h"
#include "../include/Grid.h"
#include "../include/Coord.h"
#include <vector>
#include <iostream>

Grid::Grid(void){
    // costriusco la griglia vuota e inizializzo tutte le celle a ' '
    grid_[12][12];
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            grid_[i][j] = ' ';
        }
    }
}

std::string Grid::print_grid(void) {
    std::string grid_str = "";
    // stampo la griglia inserendo prima la lettera della riga
    for (int row = 0; row < 12; row++) {
        int number_row = row;
        for (int column = 0; column < 12; column++) {
            // se il numero di riga è superiore all'8 (char I), aggiungo 2 per saltare i char J e K
            if (number_row > 8)
                number_row += 2;
            char char_row = 'A' + number_row;
            grid_str = grid_str + char_row + "|";
            grid_str = grid_str + grid_[row][column] + "|\n";
        }
    }
    // ultima riga: numeri
    grid_str += " |";
    for (int j = 1; j < 13; j++) {
        grid_str = grid_str + std::to_string(j) + "|";
    }
    return grid_str;
}

std::ostream& operator<<(std::ostream& os, Grid a){
    os << a.print_grid();
}