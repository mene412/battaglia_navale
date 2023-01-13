// Autore: Matteo

#include "../include/Ship.h"
#include "../include/HelpShip.h"
#include "../include/DefenceGrid.h"
#include "../include/Grid.h"
#include "../include/Coord.h"

HelpShip::HelpShip(Coord front, Coord back)
	:	Ship{front, back}
{
    type_='S';
    dim_=3;
    armor_=3;
	healed_=false;
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
void HelpShip::heal(DefenceGrid& yourGrid, Coord c) {
	//segno come curata questa helShip, perchè non può curarsi da sola
	set_healed(true);
	//scorre la matrice 3x3
	for (int i = (c.Y()-1); i < (c.Y()+2); i++) {
		for (int j = (c.X()-1); j < (c.X()+2); j++) {
			if (j < 0 || i < 0)
				break;
			if (yourGrid.grid()[i][j] != ' ') {
								Coord c {i, j};
				//determino il tipo della nave e curo di conseguenza
				char charFind = yourGrid.grid()[i][j];
				if (charFind == 'c' || charFind == 'C')
					heal_battleship(c, yourGrid);
				else if (charFind == 's' || charFind == 'S') {
					set_healed(true);
					heal_helpShip(c, yourGrid);
				}
			}
		}
	}
}

void heal_battleship(Coord c, DefenceGrid yourGrid) {
	std::vector<Battleship*> ships = yourGrid.battle_ship();
	for (int i = 0; i < ships.size(); i++) {
		for (int k = 0; k < ships.at(i)->coord().size(); k++) {
			if (ships.at(i)->coord().at(i) == c) {
				if (ships.at(i)->armor() > 0 || ships.at(i)->armor() < ships.at(i)->dim()) {
					ships.at(i)->set_armor(5);
				}
			}
		}
	}
}

void heal_helpShip(Coord c, DefenceGrid yourGrid) {
	std::vector<HelpShip*> ships = yourGrid.help_ship();
	for (int i = 0; i < ships.size(); i++) {
		for (int k = 0; k < ships.at(i)->coord().size(); k++) {
			if (ships.at(i)->coord().at(i) == c) {
				if ((ships.at(i)->armor() > 0 || ships.at(i)->armor() < ships.at(i)->dim()) && !ships.at(i)->healed()) {
					ships.at(i)->set_armor(3);
				}
			}
		}
	}
}