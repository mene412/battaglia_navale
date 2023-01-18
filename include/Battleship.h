// Autore: Gaia Soso
#ifndef Battleship_h
#define Battleship_h
#include "Ship.h"

class Battleship: public Ship{
    public:
        // definizione del costruttore Corazzata
        Battleship(Coord& front, Coord& back);
};
#endif /* Battleship_h */
