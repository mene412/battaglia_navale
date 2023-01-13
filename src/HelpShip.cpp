// Autore: Matteo

#include "../include/HelpShip.h"

HelpShip::HelpShip(Coord front, Coord back)
	:	Ship{front, back}
{
    dim_ = 3;
    armor_ = 3;
	distance_ = 1;
}

void HelpShip::move(Coord c) {
	std::vector<Coord> coordinate;
	int x = c.X();
	int y = c.Y();
	bool is_orizzontal = orizzontal();
	int dim_ship = 3;
	if (is_orizzontal) {
        // orizzontal -> stessa x
        for (int i = 0; i < dim_ship; i++) {
            Coord new_c {x, (y-(dim_ship/2)+i)};
            coordinate.push_back(new_c);
        }
    } else {
        // vertical -> stessa y
        for (int i = 0; i < dim_ship; i++) {
            Coord new_c {(x-(dim_ship/2)+i), y};
            coordinate.push_back(new_c);
        }
    }
	// modifica i membri
	set_coord(coordinate);
}

//A partire dalla cella centrale della nave, scorre una matrice 3x3
//Se 1 <= armor < dim, allora armor++

