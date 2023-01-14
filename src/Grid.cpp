//Autore: Matteo

#include "../include/Grid.h"

Grid::Grid(void)
    : grid_{}
{
    // costriusco la griglia vuota e inizializzo tutte le celle a ' '
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            grid_[i][j] = ' ';
        }
    }
}

char Grid::get_char(Coord c) {
    return grid_[c.X()][c.Y()];
}

bool Grid::is_in_grid(char ch, Coord c) {
    return (ch == grid_[c.X()][c.Y()]);
}

void Grid::insert_char(char ch, Coord c){
    grid_[c.X()][c.Y()] = ch;
}

std::string Grid::print_grid(void) {
    std::string grid_str = "---------------------------------------------------\n";
    // stampo la griglia inserendo prima la lettera della riga
    for (int row = 0; row < 12; row++) {
        grid_str = grid_str + UCoord::from_int_to_char(row) + " | ";
        for (int column = 0; column < 12; column++) {
            // se il numero di riga è superiore all'8 (char I), aggiungo 2 per saltare i char J e K
            grid_str = grid_str + grid_[row][column] + " | ";
        }
        grid_str = grid_str + "\n---------------------------------------------------\n";
    }
    // ultima riga: numeri
    grid_str += "  | ";
    for (int j = 1; j < 13; j++) {
        if(j/10>=1){
            grid_str = grid_str + std::to_string(j) + "| ";
        }else{
            grid_str = grid_str + std::to_string(j) + " | ";
        }
    }
    return grid_str;
}


std::ostream& operator<<(std::ostream& os, Grid a){
    os << a.print_grid();
}