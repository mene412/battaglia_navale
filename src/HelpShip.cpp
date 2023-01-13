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
	// controlla che la cella sia libera
	if (!myGrid.check_position(coordinate))
        throw std::invalid_argument("Errore");
	// cancella la vecchia cella
	for (int i = 0; i < coord().size(); i++) {
		myGrid.grid()[coord().at(i).X()][coord().at(i).Y()] = ' ';
	}
	// scrive nelle nuove celle
	for (int i = 0; i < coordinate.size(); i++) {
		int row = coordinate.at(i).X();
    	int column = coordinate.at(i).Y();
		myGrid.grid()[row][column] = 'S';
	}
	// modifica i membri
	set_coord(coordinate);
}

//A partire dalla cella centrale della nave, scorre una matrice 3x3
//Se 1 <= armor < dim, allora armor++

