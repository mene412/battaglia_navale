// Autore: Matteo Meneghin
#ifndef Help_Ship_h
#define Help_Ship_h

#include "Ship.h"
#include "DefenceGrid.h"

class HelpShip : public Ship {
    public:
        HelpShip(Coord front, Coord back);
        void move(DefenceGrid& myGrid, std::vector<Coord> c);
        void heal(DefenceGrid& yourGrid, Coord c);
};
#endif
