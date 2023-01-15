// Autore: Matteo

#include "../include/HelpShip.h"

HelpShip::HelpShip(Coord& front, Coord& back)
	:	Ship{front, back}
{
    dim_ = 3;
    armor_ = 3;
	distance_ = 1;
    set_center();
    set_direction();
    set_coord_center();
}

void HelpShip::move(Coord& c) {
	set_coord_center(c);
}
