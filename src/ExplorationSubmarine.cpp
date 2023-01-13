// Autore:

#include "../include/AttackGrid.h"
#include "../include/Ship.h"
#include "../include/ExplorationSubmarine.h"
#include "../include/DefenceGrid.h"

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
    
