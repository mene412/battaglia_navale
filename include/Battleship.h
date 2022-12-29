// Autore:
#ifndef Battleship_h
#define Battleship_h
#include "Ship.h"
class Corazzata: public Ship
{
public:
    Corazzata()
    {
        type='C';
        dim=5;
        armor=5;
        set_coord();
    }
};
#endif /* Battleship.h */
