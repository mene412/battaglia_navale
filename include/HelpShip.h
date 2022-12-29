// Autore:
#ifndef HelpShip_h
#define HelpShip_h
#include "Ship.h"
class Support_Ship: public Ship
{
public:
    Support_Ship()
    {
        type='S';
        dim=3;
        armor=3;
        set_coord();
    }
};
#endif /* HelpShip_h */
