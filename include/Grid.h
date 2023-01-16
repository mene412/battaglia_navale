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
        int dimension(void){ return sizeof(grid_);}
        char get_char(Coord& c);
        bool is_in_grid(char ch, Coord& c);
        void insert_char(char ch, Coord& c);
        //stampa la griglia
        std::string print_grid(void);
        virtual ~Grid(void){};
        void flush(void);

    protected:    
        char grid_[12][12];
};

std::ostream& operator<<(std::ostream& os, Grid& a);

#endif /* Grid_h */
