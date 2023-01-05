// Autore:
#ifndef Help_Ship_h
#define Help_Ship_h

#include "Ship.h"

class HelpShip : public Ship
{
public:
    HelpShip(void);
    void Move(int toX, int toY);
    void heal(DefenceGrid yourGrid, int x, int y);
};
#endif
