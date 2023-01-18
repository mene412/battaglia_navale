<<<<<<< Updated upstream
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
    set_coord();
}

void ExplorationSubmarine::move(void) {

}
    
void ExplorationSubmarine::search(DefenceGrid enemyGrid, AttackGrid myGrid, int x, int y) {
    for (int i = (y-2); i < (y+3); i++) {
        for (int j = (x-2); j < (x+3); j++) {
            if (y < 0 || x < 0)
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
=======
// Autore:
#include "../include/ExplorationSubmarine.h"


ExplorationSubmarine::ExplorationSubmarine(Coord& front)
    :   Ship{front, front}
{   
    dim_= 1;
    armor_= 1;
    distance_ = 0;
    center_ = front;
    coord_.push_back(center_);
    x_ = center_.X();
    y_ = center_.Y();
}


void ExplorationSubmarine::move(Coord& c) {
    set_coord_from_center(c);
}

void ExplorationSubmarine::set_coord_from_center(Coord& c){             
    center_ = c;
    front_ = c;
    back_ = c;
    x_ = c.X();
    y_ = c.Y();
    coord_.at(0) = center_;
}

void ExplorationSubmarine::set_coord(std::vector<Coord>& coordinates){
    if(coordinates.size()!=1){
        throw std::invalid_argument("Dimensione coordinate errata");
    }
    coord_ = coordinates;
    center_ = coord_.at(0);
}
>>>>>>> Stashed changes
