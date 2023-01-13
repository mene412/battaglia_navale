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
        bool fire(AttackGrid& AttGrid, DefenceGrid& DefGrid, Coord cord);
};
#endif /* Battleship_h */
