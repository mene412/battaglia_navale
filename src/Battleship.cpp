// Autore:
#include "../include/Battleship.h"

Battleship::Battleship(Coord& front, Coord& back)
    : Ship{front, back}
{
    dim_= 5;
    armor_= 5;
    distance_ = 2;
    set_direction();
    set_center();
    set_coord_center();
}
