// Autore: Matteo

#include "../include/Grid.h"
#include "../include/AttackGrid.h"

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
        for (int j = 1; j < 13; j++) {
            if (grid_[i][j] == c)
                grid_[i][j] = ' ';
        }
    }
}