// Autore: Matteo

#include "../include/Ship.h"
#include "../include/HelpShip.h"
#include "../include/DefenceGrid.h"
#include "../include/Grid.h"

HelpShip::HelpShip() {
    type_='S';
    dim_=3;
    armor_=3;
	healed_=false;
    set_coord();
}

void HelpShip::move(int toX, int toY) {
	set_coord();	//TO DO
}
    
//A partire dalla cella centrale della nave, scorre una matrice 3x3
//Se 1 <= armor < dim, allora armor++
void HelpShip::heal(DefenceGrid yourGrid, int x, int y) {
	//segno come curata questa helShip, perchè non può curarsi da sola
	set_healed(true);					
	//scorre la matrice 3x3
	for (int i = (y-1); i < (y+2); i++) {
		for (int j = (x-1); j < (x+2); j++) {
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
						if (true) {	//if una coppia delle coord è uguale a [i][j]			//TO DO
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
