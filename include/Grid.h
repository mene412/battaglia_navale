// Autore: Matteo Meneghin

#ifndef Grid_h
#define Grid_h

#include "Ship.h"
#include "vector"
#include <iostream>

class Grid {
    public:
        Grid(void);
        //setter
        void set_grid(void);
        char** grid(void) { return grid_; }
        //getter
        std::vector<Ship> ships(void) { return ships_; }
        //altri metodi
        // date le coordinate centrali della nave, ritorna la posizione nell'array ships_,
        // -1 se non la trova
        int findShip(int x, int y);
        //stampa la griglia
        void showGrid(void);
    protected:
        std::vector<Ship> ships_;
        char** grid_;
};
#endif /* Grid_h */
