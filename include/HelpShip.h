// Autore: Matteo Meneghin
#ifndef Help_Ship_h
#define Help_Ship_h

#include "Ship.h"
#include "DefenceGrid.h"

class HelpShip : public Ship {
public:
    HelpShip(void);
    void move(int toX, int toY);
    void heal(DefenceGrid yourGrid, int x, int y);
};
#endif
