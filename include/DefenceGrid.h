// Autore: Matteo Meneghin

#ifndef DefenceGrid_h
#define DefenceGrid_h

#include "Grid.h"
#include "Coord.h"

class DefenceGrid : public Grid {
    public: 
        DefenceGrid(void);
        //controlla che le celle non siano già occupate da altre navi
        // ritorna true se sono libere
        bool checkPosition(std::vector<Coord> coordinates);   
        // inserisce la nave nel vettore di ship, e scrive i char corrispondenti nella griglia
        void addShip(Ship newShip);
};

std::ostream& operator<<(std::ostream& os, DefenceGrid a);

#endif /* DefenceGrid_h */
