// Autore: Gaia Soso
#ifndef Battleship_h
#define Battleship_h

#include "Ship.h"
#include "DefenceGrid.h"
#include "AttackGrid.h"
#include "Coord.h"

class Battleship: public Ship
{
    public:
        Battleship(Coord front, Coord back);
        void fire(AttackGrid& AttGrid, DefenceGrid& DefGrid, Coord cord);
        bool full_ship(DefenceGrid& def_grid, int pos) const;
        void titanic(AttackGrid& att_grid, DefenceGrid& def_grid, int pos);
};
#endif /* Battleship_h */
