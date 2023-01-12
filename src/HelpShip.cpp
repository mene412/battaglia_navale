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

void HelpShip::move(DefenceGrid myGrid, std::vector<Coord> c) {
	// controlla che la cella sia libera
	if (!myGrid.check_position(c))
        throw std::invalid_argument("Errore");
	// cancella la vecchia cella
	for (int i = 0; i < coord().size(); i++) {
		myGrid.grid()[coord().at(i).X()][coord().at(i).Y()] = ' ';
	}
	// scrive nelle nuove celle
	for (int i = 0; i < c.size(); i++) {
		int row = c.at(i).X();
    	int column = c.at(i).Y();
		myGrid.grid()[row][column] = 'S';
	}
	// modifica i membri
	set_coord(c);
}

//A partire dalla cella centrale della nave, scorre una matrice 3x3
//Se 1 <= armor < dim, allora armor++
void HelpShip::heal(DefenceGrid yourGrid, Coord c) {
	//segno come curata questa helShip, perchè non può curarsi da sola
	set_healed(true);
	//scorre la matrice 3x3
	for (int i = (c.Y()-1); i < (c.Y()+2); i++) {
		for (int j = (c.X()-1); j < (c.X()+2); j++) {
			if (j < 0 || i < 0)
				break;
			if (yourGrid.grid()[i][j] != ' ') {
				//determino il tipo della nave
				char charFind = yourGrid.grid()[i][i];
				if (charFind == 'c')
					charFind = 'C';
				else if (charFind == 's')
					charFind = 'S';
				else if (charFind == 'e')
					charFind = 'E';
				//cerco la nave per tipo
				for (int k = 0; k < yourGrid.ships().size(); k++) {
					if (yourGrid.ships()[k].type() == charFind) {
					//trovato il tipo, cerco la nave giusta guardando le posizioni
						if (yourGrid.ships()[k].ifSameCoord(i,j)) {	//if una coppia delle coord è uguale a [i][j]	//Metodo IfSamecoord di ship
							if (!yourGrid.ships()[k].healed()) {
								if (1 <= yourGrid.ships()[k].armor() && yourGrid.ships()[k].armor() < yourGrid.ships()[k].dim())
									yourGrid.ships()[k].incArmor();
							}
						}
					}
				}
			}
		}
	}
}
