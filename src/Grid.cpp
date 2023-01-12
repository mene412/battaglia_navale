//Autore: Matteo

#include "../include/Ship.h"
#include "../include/Grid.h"
#include <vector>
#include <iostream>

Grid::Grid(void){
    ships_;
    // costriusco la matrice e inizializzo tutte le celle a ' '
    grid_[13][13];
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 13; j++) {
            grid_[i][j] = ' ';
        }
    }
    // prima colonna: lettere
    // non scrivo nulla nell'ultima riga (quindi i < 12)
    for (int i = 0; i < 12; i++) {
        if (i == 9)
            i += 2;
        grid_[i][0] = 'A' + i;
    }
    // ultima riga: numeri
    // non scrivo nulla nella priam colonna (quindi j = 1)
    for (int j = 1; j < 13; j++) {
        grid_[12][j] = j;
    }
}

int Grid::findShip(Coord x) {
    for (int i = 0; i < ships_.size(); i++) {
        if (ships().at(i).armor() != 0) {
            if (ships().at(i).center().X() == x.X() && ships().at(i).center().Y() == x.Y()) {
                return i;
            }
        }
    }
    return -1;
}



std::vector<Ship> Grid::ships(void){
    std::vector<Ship> x{};
    for(int i = 0; i<ships_.size(); i++){
        x.push_back(*ships_.at(i));
    }
    return x;
}


std::vector<Battleship> Grid::battle_ship(void){
    std::vector<Battleship> battle{};
    Battleship* battleship;
    for(int i = 0; i<ships_.size(); i++){
        battleship = dynamic_cast<Battleship*>(ships_.at(i));
        if(battleship!=nullptr){
            battle.push_back(*battleship);
        }
    }
    return battle;
}

std::vector<HelpShip> Grid::help_ship(void){
    std::vector<HelpShip> help{};
    HelpShip* helpship;
    for(int i = 0; i<ships_.size(); i++){
        helpship = dynamic_cast<HelpShip*>(ships_.at(i));
        if(helpship!=nullptr){
            help.push_back(*helpship);
        }
    }
    return help;
}

std::vector<ExplorationSubmarine> Grid::sub_ship(void){
    std::vector<ExplorationSubmarine> sub{};
    ExplorationSubmarine* subship;
    for(int i = 0; i<ships_.size(); i++){
        subship = dynamic_cast<ExplorationSubmarine*>(ships_.at(i));
        if(subship!=nullptr){
            sub.push_back(*subship);
        }
    }
    return sub;
}

int Grid::ship(Coord c){
    for(int i = 0; i<ships().size(); i++){
        if(ships().at(i).center() == c){
            return i;
        }
    }
    throw std::invalid_argument("Errore");
}

int Grid::type_ship(int pos){
    
}


std::string Grid::print_grid(void) {
    std::string grid = "";
    for (int row = 0; row < 13; row++) {
        for (int column = 0; column < 13; column++) {
            grid = grid + grid_[row][column] + "|\n";
        }
    }
    return grid;
}

std::ostream& operator<<(std::ostream& os, Grid a){
    os << a.print_grid();
}