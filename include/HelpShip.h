// Autore: Matteo Meneghin
#ifndef Help_Ship_h
#define Help_Ship_h

#include "Ship.h"
#include "DefenceGrid.h"

class HelpShip : public Ship {
    public:
        HelpShip(Coord front, Coord back);
        // controlla se le celle sono vuote, se true allora
        // cancella quelle vecchie, scrive quelle nuove e modifica i membri della ship
        // int pos = posizione della ship nel vector
        void move(DefenceGrid& myGrid, Coord c, int pos);
        // se trova nella griglia 3x3 una corazzata o una helpship, e manca vita
        // allora la cura del tutto
        void heal(DefenceGrid& yourGrid, Coord c);
};
#endif
