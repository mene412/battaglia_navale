// Autore:
#include "../include/ExplorationSubmarine.h"


ExplorationSubmarine::ExplorationSubmarine(Coord front)
    :   Ship{front, front}
{   
    dim_= 1;
    armor_= 1;
    distance_ = 0;
    center_ = front;
    coord_.push_back(center_);
}

void ExplorationSubmarine::move(Coord c) {
    set_coord_center(c);
}
    
