// Autore: Matteo Meneghin

#ifndef Grid_h
#define Grid_h

#include "Ship.h"
#include "Battleship.h"
#include "ExplorationSubmarine.h"
#include "HelpShip.h"
#include "Coord.h"
#include <vector>
#include <iostream>

class Grid {
    public:
        // costruttore: crea una amtrice 12x12 di char vuoti
        Grid(void);
        //getter
        char** grid(void) { return grid_; }
        // date le coordinate centrali della nave, ritorna la posizione nell'array ships_,
        // se non la trova lancia un errore
        int find_ship(Coord x);
        //stampa la griglia
        std::string print_grid(void);
        virtual ~Grid(){};

    protected:    
        char** grid_;
};

std::ostream& operator<<(std::ostream& os, Grid a);

#endif /* Grid_h */
