// Autore: Gaia Soso
#ifndef Battleship_H
#define Battleship_H
#include "Ship.h"

class Battleship: public Ship{
    public:
        // definizione del costruttore Corazzata
        Battleship(Coord& front, Coord& back);
};
#endif /* Battleship_H */
