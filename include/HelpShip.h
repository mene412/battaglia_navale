// Autore: Matteo Meneghin
#ifndef Help_Ship_h
#define Help_Ship_h

#include "Ship.h"
#include "DefenceGrid.h"

class HelpShip : public Ship {
    public:
        HelpShip(Coord front, Coord back);
        // int pos = posizione della ship nel vector
        void move(DefenceGrid& myGrid, Coord c, int pos);
        void heal(DefenceGrid& yourGrid, Coord c);
};
#endif
