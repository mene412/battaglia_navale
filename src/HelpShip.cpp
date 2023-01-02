// Autore: Matteo

// TO DO
// - aggiungere a Ship variabile healed, e il metodo setHealed(bool a) e healed(void)
// - aggiungere a Grid metodo che ritorna la matrice di char
// - aggiungere a Ship 2 metodi per l'armor: incrArmor() e decrArmor()

#include "Ship.h"
#include "Help_Ship.h"

HelpShip::HelpShip() {
    type_='S';
    dim_=3;
    armor_=3;
    SetCoord();
}

void HelpShip::move(int xTo, int yTo) {
	setCoord();	//TO DO
}
    
//A partire dalla cella centrale della nave, scorre una matrice 3x3
//Se 1 <= armor < dim, allora armor++
void HelpShip::heal(defenceGrid yourGrid, int x, int y) {
	//segno come curata questa helShip, perchè non può curarsi da sola
	setHealed(true);					
	//scorre la matrice 3x3
	for (int i = (y-1); i < (y+2); i++) {
		for (int j = (x-1); j < (x+2); j++) {
			if (j < 0 || i < 0)
				break;
			if (yourGrid.matrix()[i][j] != ' ') {
				//determino il tipo della nave
				char charFind = yourGrid.matrix()[i][i];
				if (charFind == 'c')
					charFind = 'C';
				else if (charFind == 's')
					charFind = 'S';
				else if (charFind == 'e')
					charFind = 'E';
				//cerco la nave per tipo
				for (int s = 0; s < ships().length(); s++) {
					if (ships()[k].type() == charFind) {
					//trovato il tipo, cerco la nave giusta guardando le posizioni
						if () {	//if una coppia delle coord è uguale a [i][j]
							if (!ships()[k].healed()) {
								if (1 <= ships()[k].armor() < ships()[k].dim())
									ships()[k].incrArmor();
							}
						}
					}
				}
			}
		}
	}
}
