// Autore:
#ifndef ExplorationSubmarine_h
#define ExplorationSubmarine_h
#include "Ship.h"
class Submarine: public Ship
{
public:
    Submarine()
    {
        type='E';
        dim=1;
        armor=1;
        set_coord();
    }
 #endif /* ExplorationSubmarine.h */
