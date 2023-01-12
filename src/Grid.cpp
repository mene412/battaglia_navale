//Autore: Matteo

#include "../include/Ship.h"
#include "../include/Grid.h"
#include "../include/Coord.h"
#include <vector>
#include <iostream>

Grid::Grid(void){
    ships_;
    // costriusco la griglia vuota e inizializzo tutte le celle a ' '
    grid_[12][12];
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            grid_[i][j] = ' ';
        }
    }
}

int Grid::find_ship(Coord x) {
    for (int i = 0; i < ships_.size(); i++) {
        if (ships().at(i).armor() != 0) {
            if (ships().at(i).center() == x) {
                return i;
            }
        }
    }
    throw std::invalid_argument("Errore");
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


int Grid::type_ship(int pos){
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


std::string Grid::print_grid(void) {
    std::string grid_str = "";
    // stampo la griglia inserendo prima la lettera della riga
    for (int row = 0; row < 12; row++) {
        int number_row = row;
        for (int column = 0; column < 12; column++) {
            // se il numero di riga è superiore all'8 (char I), aggiungo 2 per saltare i char J e K
            if (number_row > 8)
                number_row += 2;
            char char_row = 'A' + number_row;
            grid_str = grid_str + char_row + "|";
            grid_str = grid_str + grid_[row][column] + "|\n";
        }
    }
    // ultima riga: numeri
    grid_str += " |";
    for (int j = 1; j < 13; j++) {
        grid_str = grid_str + std::to_string(j) + "|";
    }
    return grid_str;
}

std::ostream& operator<<(std::ostream& os, Grid a){
    os << a.print_grid();
}