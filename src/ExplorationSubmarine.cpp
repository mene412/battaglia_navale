// Autore:

#include "../include/AttackGrid.h"
#include "../include/Ship.h"
#include "../include/ExplorationSubmarine.h"
#include "../include/DefenceGrid.h"

ExplorationSubmarine::ExplorationSubmarine(Coord front, Coord back)
    :   Ship{front, back}
{
    type_='E';
    dim_=1;
    armor_=1;
    healed_=false;
}

void ExplorationSubmarine::move(DefenceGrid& myGrid, Coord c) {
    std::vector<Coord> coordinate {c};
    // controlla che la cella sia libera
    if (!myGrid.check_position(coordinate))
        throw std::invalid_argument("Errore");
    int row = c.X();
    int column = c.Y();
    // scrivi nella nuova cella
    myGrid.grid()[row][column] = 'E';
    // cancella la vecchia cella
    myGrid.grid()[center().X()][center().Y()] = ' ';
    // modifica i membri del sottomarino
    set_coord(coordinate);
}
    
void ExplorationSubmarine::search(DefenceGrid& enemyGrid, AttackGrid& myGrid, Coord c) {
    for (int i = (c.Y()-2); i < (c.Y()+3); i++) {
        for (int j = (c.X()-2); j < (c.X()+3); j++) {
            if (j < 0 || i < 0)
                continue;
            else if (enemyGrid.grid()[i][j] != ' ') {
                char valueFind = enemyGrid.grid()[i][j];
                if (valueFind == 'C' || valueFind == 'E' || valueFind == 'S') {
                    myGrid.grid()[i][j] = 'Y';
                }
                else if (valueFind == 'c' || valueFind == 'e' || valueFind == 'd') {
                    myGrid.grid()[i][j] = 'X';
                }
            }
        }
    }
}
