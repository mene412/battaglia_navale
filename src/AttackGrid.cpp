// Autore: Matteo Meneghin

#include "../include/AttackGrid.h"

AttackGrid::AttackGrid(void)
    :   Grid{}
{}

void AttackGrid::remove_detections(void) {
    remove_char('Y');
}   

void AttackGrid::remove_hit(void) {
    remove_char('X');
    remove_char('x');
}       

void AttackGrid::remove_water(void) {
    return remove_char('O');
}       

void AttackGrid::remove_char(char c) {
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            if (grid_[i][j] == c){
                grid_[i][j] = ' ';
            }
        }
    }
}

void AttackGrid::add_char(char ch, Coord& coord) {
    if (ch != 'X' && ch != 'O' && ch!='Y' && ch!='x'){
        throw std::invalid_argument("Errore");
    }
    if(ch == 'Y'){
        if(grid_[coord.X()][coord.Y()] != 'x'){
            grid_[coord.X()][coord.Y()] = ch;
        }
    }else{
        grid_[coord.X()][coord.Y()] = ch;
    }
    
}

std::ostream& operator<<(std::ostream& os, AttackGrid& a){
    os << "Griglia di attacco\n\n" << a.print_grid() << "\n" << std::endl;
    return os;
}