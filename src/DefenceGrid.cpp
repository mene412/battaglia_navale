//Autore: Matteo

#include "../include/Grid.h"
#include "../include/DefenceGrid.h"
#include "../include/Ship.h"
#include "../include/Battleship.h"
#include "../include/HelpShip.h"
#include "../include/ExplorationSubmarine.h"
#include "../include/Coord.h"


DefenceGrid::DefenceGrid(void)
    : Grid{}
{}

bool DefenceGrid::check_position(std::vector<Coord> coordinates) {
    for (int i = 0; i < coordinates.size(); i++) {
        int checkRow = coordinates[i].X();        // numero riga
        int checkColumn = coordinates[i].Y();    // numero colonna
        if (grid_[checkRow][checkColumn] != ' ') {
            // se la cella non è vuota, ritorna false
            return false;
        }
    }
    return true;
}

int DefenceGrid::find_ship(Coord x) {
    for (int i = 0; i < number_ship(); i++) {
        if (ships().at(i)->armor() != 0) {
            if (ships().at(i)->center() == x) {
                return i;
            }
        }
    }
    throw std::invalid_argument("Errore");
}




std::vector<Battleship*>& DefenceGrid::battle_ship(void){
    std::vector<Battleship*> battle{};
    Battleship* battleship;
    for(int i = 0; i<number_ship(); i++){
        battleship = dynamic_cast<Battleship*>(ships_.at(i));
        if(battleship!=nullptr){
            battle.push_back(battleship);
        }
    }
    delete battleship;
    return battle;
}

std::vector<HelpShip*>& DefenceGrid::help_ship(void){
    std::vector<HelpShip*> help{};
    HelpShip* helpship;
    for(int i = 0; i<number_ship(); i++){
        helpship = dynamic_cast<HelpShip*>(ships_.at(i));
        if(helpship!=nullptr){
            help.push_back(helpship);
        }
    }
    delete helpship;
    return help;
}

std::vector<ExplorationSubmarine*>& DefenceGrid::sub_ship(void){
    std::vector<ExplorationSubmarine*> sub{};
    ExplorationSubmarine* subship;
    for(int i = 0; i<number_ship(); i++){
        subship = dynamic_cast<ExplorationSubmarine*>(ships_.at(i));
        if(subship!=nullptr){
            sub.push_back(subship);
        }
    }
    delete subship;
    return sub;
}


int DefenceGrid::type_ship(int pos){
    if(dynamic_cast<Battleship*>(ships_.at(pos)) != nullptr){
        return 1; // battleship 
    }
    if(dynamic_cast<HelpShip*>(ships_.at(pos)) != nullptr){
        return 2; // helpship
    }
    if(dynamic_cast<ExplorationSubmarine*>(ships_.at(pos)) != nullptr){
        return 3; // Exploration
    }
}

void DefenceGrid::add_ship(Ship newShip) {
    if (!check_position(newShip.coord())) {      //da errore in compilazione perhè coord è, per ora, un vector di vector di int
                                                // deve essere invece un vector di Coord
        return;                                 //TO DO: lanciare eccezione
    }
    for (int i = 0; i < newShip.coord().size(); i++) {
        int rowSelected = newShip.coord().at(i).X();
        int columnSelected = newShip.coord().at(i).Y();
        grid_[rowSelected][columnSelected] = newShip.type();
    }
    ships_.push_back(&newShip);
}

std::ostream& operator<<(std::ostream& os, DefenceGrid a){
    os << "\nGriglia di difesa\n\n" << a.print_grid() << std::endl;
}