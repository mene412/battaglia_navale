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
        bool fire(AttackGrid& AttGrid, DefenceGrid& DefGrid, int x,int y);
};
#endif /* Battleship_h */
