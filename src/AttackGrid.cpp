// Autore: Matteo

#include "../include/Grid.h"
#include "../include/AttackGrid.h"


AttackGrid::AttackGrid(void)
    :   Grid{}
{}
//rimuove le Y
// invocato dall'utente con il comando AA AA
void AttackGrid::removeDetections(void) {
    return removeChar('Y');
}   
//rimuove le X
// invocato dall'utente con il comando BB BB (vedi FAQ - Q1)
void AttackGrid::removeHit(void) {
    return removeChar('X');
}       
//rimuove le O
// invocato dall'utente con il comando CC CC (vedi FAQ - Q1)
void AttackGrid::removeWater(void) {
    return removeChar('O');
}       
//rimuove uno specifico char
void AttackGrid::removeChar(char c) {
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            if (grid_[i][j] == c)
                grid_[i][j] = ' ';
        }
    }
}

std::ostream& operator<<(std::ostream& os, AttackGrid a){
    os << "Griglia di attacco\n\n" << a.print_grid() << std::endl;
}