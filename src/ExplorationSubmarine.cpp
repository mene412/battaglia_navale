// Autore:
#include "../include/ExplorationSubmarine.h"

ExplorationSubmarine::ExplorationSubmarine(Coord front, Coord back)
    :   Ship{front, back}
{
    dim_=1;
    armor_=1;
    distance_ = 0;
}

void ExplorationSubmarine::move(Coord c) {
    set_coord_center(c);
}
    
