// Autore: Matteo

#include "../include/AttackGrid.h"


AttackGrid::AttackGrid(void)
    :   Grid{}
{}
//rimuove le Y
// invocato dall'utente con il comando AA AA
void AttackGrid::remove_detections(void) {
    remove_char('Y');
}   
//rimuove le X
// invocato dall'utente con il comando BB BB (vedi FAQ - Q1)
void AttackGrid::remove_hit(void) {
    remove_char('X');
    remove_char('x');
}       
//rimuove le O
// invocato dall'utente con il comando CC CC (vedi FAQ - Q1)
void AttackGrid::remove_water(void) {
    return remove_char('O');
}       
//rimuove uno specifico char
void AttackGrid::remove_char(char c) {
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            if (grid_[i][j] == c){
                grid_[i][j] = ' ';
            }
        }
    }
}
// aggiunge uno specifico char in una specifica Coord
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