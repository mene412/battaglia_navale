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
        //setter
        void set_grid(void);
        char** grid(void) { return grid_; }
        //getter
        std::vector<Ship> ships(void);
        int number_ship(void){ return ships_.size(); }
        std::vector<Battleship> battle_ship(void);
        std::vector<HelpShip> help_ship(void);
        std::vector<ExplorationSubmarine> sub_ship(void);
        //altri metodi
        int ship(Coord c);
        int type_ship(int pos);

        // date le coordinate centrali della nave, ritorna la posizione nell'array ships_,
        // -1 se non la trova
        int findShip(Coord x);
        //stampa la griglia
        std::string print_grid(void);
        virtual ~Grid(){};

    protected:
        std::vector<Ship*> ships_;
        char** grid_;
};

std::ostream& operator<<(std::ostream& os, Grid a);

#endif /* Grid_h */
