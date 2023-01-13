// Autore: Matteo Meneghin
#ifndef Help_Ship_h
#define Help_Ship_h

#include "Ship.h"

class HelpShip : public Ship {
    public:
        HelpShip(Coord front, Coord back);
        // modifica i membri della ship
        void move(Coord c);
        // se trova nella griglia 3x3 una corazzata o una helpship, e manca vita
        // allora la cura del tutto
};
#endif
