// Autore:

#include "../include/AttackGrid.h"
#include "../include/Ship.h"
#include "../include/ExplorationSubmarine.h"
#include "../include/DefenceGrid.h"

ExplorationSubmarine::ExplorationSubmarine(void){
    type_='E';
    dim_=1;
    armor_=1;
    healed_=false;
    SetCoord();
}

void ExplorationSubmarine::move(void) {

}
    
void ExplorationSubmarine::search(DefenceGrid enemyGrid, AttackGrid myGrid, int x, int y) {
    for (int i = (y-2); i < (y+3); i++) {
        for (int j = (x-2); j < (x+3); j++) {
            if (y < 0 || x < 0)
                break;
            if (enemyGrid.matrix()[i][j] != ' ') {
                char valueFind = enemyGrid.matrix()[i][j];
                if (valueFind == 'C' || valueFind == 'E' || valueFind == 'S') {
                    myGrid.matrix()[i][j] = 'Y';
                }
                else if (valueFind == 'c' || valueFind == 'e' || valueFind == 'd') {
                    myGrid.matrix()[i][j] = 'X';
                }
            }
        }
    }
}