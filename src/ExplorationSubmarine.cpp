// Autore: Matteo Meneghin

#include "../include/ExplorationSubmarine.h"

ExplorationSubmarine::ExplorationSubmarine(Coord& front)
    :   Ship{front, front}
{   
    dim_= 1;
    armor_= 1;
    distance_ = 0;
    center_ = front;
    coord_.push_back(center_);
}


void ExplorationSubmarine::move(Coord& c) {
    set_coord_from_center(c);
}

void ExplorationSubmarine::set_coord_from_center(Coord& c){             
    center_ = c;
    front_ = c;
    back_ = c;
    coord_.at(0) = center_;
}

void ExplorationSubmarine::set_coord(std::vector<Coord>& coordinates){
    if(coordinates.size()!=1){
        throw std::invalid_argument("Dimensione coordinate errata");
    }
    coord_ = coordinates;
    center_ = coord_.at(0);
}
