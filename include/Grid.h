// Autore: Matteo Meneghin

#ifndef Grid_h
#define Grid_h

#include "Battleship.h"
#include "ExplorationSubmarine.h"
#include "HelpShip.h"
#include <iostream>

class Grid {
    public:
        // costruttore: crea una amtrice 12x12 di char vuoti
        Grid(void);
        //getter
        char[] grid(void) { return grid_; }
        //stampa la griglia
        std::string print_grid(void);
        virtual ~Grid(void){};

    protected:    
        char grid_[12][12];
};

std::ostream& operator<<(std::ostream& os, Grid a);

#endif /* Grid_h */
