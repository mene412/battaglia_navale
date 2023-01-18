// Autore: Matteo Meneghin

#ifndef Help_Ship_h
#define Help_Ship_h

#include "Ship.h"

class HelpShip : public Ship {
    public:
        // Costruttore
        HelpShip(Coord& front, Coord& back);

        // Muove la nave in posizione c
        void move(Coord& c);
};

#endif