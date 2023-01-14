// Autore: Matteo

#include "../include/AttackGrid.h"


AttackGrid::AttackGrid(void)
    :   Grid{}
{}
//rimuove le Y
// invocato dall'utente con il comando AA AA
void AttackGrid::remove_detections(void) {
    return remove_char('Y');
}   
//rimuove le X
// invocato dall'utente con il comando BB BB (vedi FAQ - Q1)
void AttackGrid::remove_hit(void) {
    return remove_char('X');
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
            if (grid_[i][j] == c)
                grid_[i][j] = ' ';
        }
    }
}
// aggiunge uno specifico char in una specifica Coord
void AttackGrid::add_char(char ch, Coord coord) {
    if (ch != 'X' || ch != 'O' || ch!='Y')
        throw std::invalid_argument("Errore");
    grid_[coord.X()][coord.Y()] = ch;
}

std::ostream& operator<<(std::ostream& os, AttackGrid a){
    os << "\nGriglia di attacco\n\n" << a.print_grid() << std::endl;
}