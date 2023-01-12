// Autore: Matteo Meneghin

#ifndef Grid_h
#define Grid_h

#include "Ship.h"
#include "Coord.h"
#include <vector>
#include <iostream>

class Grid {
    public:
        // costruttore: crea una amtrice 12x12 di char vuoti
        Grid(void);
        //getter
        char** grid(void) { return grid_; }
        std::vector<Ship> ships(void) { return ships_; }
        int number_ship(void){ return ships_.size(); }
        //altri metodi
        // date le coordinate centrali della nave, ritorna la posizione nell'array ships_,
        // -1 se non la trova
        int findShip(Coord x);
        //stampa la griglia, aggiungendo la prima colonna di lettere e l'ultima riga di numeri
        std::string print_grid(void);
    protected:
        std::vector<Ship> ships_;
        char** grid_;
};

std::ostream& operator<<(std::ostream& os, Grid a);

#endif /* Grid_h */
