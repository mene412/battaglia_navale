// Autore: Matteo Meneghin

#include "HelpShip.h"

HelpShip::HelpShip(Coord& front, Coord& back)
	:	Ship{front, back}
{
    dim_ = 3;
    armor_ = 3;
	distance_ = 1;
    set_direction();
    set_center();
    set_coord_center();
}

void HelpShip::move(Coord& c) {
	set_coord_from_center(c);
}
