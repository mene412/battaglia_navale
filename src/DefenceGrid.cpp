//Autore: Matteo

#include "../include/Grid.h"
#include "../include/DefenceGrid.h"
#include "../include/Ship.h"
#include "../include/Battleship.h"
#include "../include/HelpShip.h"
#include "../include/ExplorationSubmarine.h"
#include "../include/Coord.h"


DefenceGrid::DefenceGrid(void)
    : Grid{}, ships_{}
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

void DefenceGrid::add_ship(Ship* newShip) {
    if (!check_position(newShip->coord())) {      //da errore in compilazione perhè coord è, per ora, un vector di vector di int
                                                // deve essere invece un vector di Coord
        return;                                 //TO DO: lanciare eccezione
    }
    ships_.push_back(newShip);
    for (int i = 0; i < newShip->coord().size(); i++) {
        int rowSelected = newShip->coord().at(i).X();
        int columnSelected = newShip->coord().at(i).Y();
        int type = type_ship(ships_.size()-1);
        if(type == 1){
            grid_[rowSelected][columnSelected] = 'C';
        }else if(type == 2){
            grid_[rowSelected][columnSelected] = 'S';
        }else if(type == 3){
            grid_[rowSelected][columnSelected] = 'E';
        }
    }
}

DefenceGrid::~DefenceGrid(void){
    for(int i = 0; i<number_ship(); i++){
        delete ships_.at(i);
    }
}


std::vector<Coord> DefenceGrid::get_ship_coord(Coord c, int pos) {
    std::vector<Coord> coord_ship;
    int x = c.X();
    int y = c.Y();
    bool is_orizzontal = ships_.at(pos)->orizzontal();
    int dim_ship = ships_.at(pos)->orizzontal();
    if (is_orizzontal) {
        // orizzontal -> stessa x
        for (int i = 0; i < dim_ship; i++) {
            Coord new_c {x, (y-(dim_ship/2)+i)};
            coord_ship.push_back(new_c);
        }
    } else {
        // vertical -> stessa y
        for (int i = 0; i < dim_ship; i++) {
            Coord new_c {(x-(dim_ship/2)+i), y};
            coord_ship.push_back(new_c);
        }
    }
    return coord_ship;
}

std::ostream& operator<<(std::ostream& os, DefenceGrid a){
    os << "\nGriglia di difesa\n\n" << a.print_grid() << std::endl;
}

bool DefenceGrid::destroyed(int pos){
    if(ships_.at(pos)->armor() == 0){
        return true;
    }   
    return false;

    if(ships_.at(pos)->armor() == 0){
        return true;
    }   
    return false;
}

void DefenceGrid::remove_ship(int pos){
    ships_.erase(ships_.begin()+pos);
}

void DefenceGrid::reload(void){
    for(int i=0; i<number_ship(); i++){
        int type = type_ship(i);
        for(int j = 0; j<ships_.at(i) -> coord().size(); j++){
            if(type == 1){
                bool hit = false;
                for(int k = 0; k<ships_.at(i) -> coord_hit().size(); k++){
                    if(ships_.at(i) -> coord_hit().at(k) == j){
                        hit = true;
                    }
                    if(hit){
                        grid_[ships_.at(i) -> coord().at(j).X()][ships_.at(i) -> coord().at(j).Y()] = 'c';
                    }else{
                        grid_[ships_.at(i) -> coord().at(j).X()][ships_.at(i) -> coord().at(j).Y()] = 'C';
                    }
                }
            }else if(type == 2){
                bool hit = false;
                for(int k = 0; k<ships_.at(i) -> coord_hit().size(); k++){
                    if(ships_.at(i) -> coord_hit().at(k) == j){
                        hit = true;
                    }
                    if(hit){
                        grid_[ships_.at(i) -> coord().at(j).X()][ships_.at(i) -> coord().at(j).Y()] = 's';
                    }else{
                        grid_[ships_.at(i) -> coord().at(j).X()][ships_.at(i) -> coord().at(j).Y()] = 'S';
                    }
                }
            }else if(type == 3){
                bool hit = false;
                for(int k = 0; k<ships_.at(i) -> coord_hit().size(); k++){
                    if(ships_.at(i) -> coord_hit().at(k) == j){
                        hit = true;
                    }
                    if(hit){
                        grid_[ships_.at(i) -> coord().at(j).X()][ships_.at(i) -> coord().at(j).Y()] = 'e';
                    }else{
                        grid_[ships_.at(i) -> coord().at(j).X()][ships_.at(i) -> coord().at(j).Y()] = 'E';
                    }
                }
            }
        }   
    }
}

void DefenceGrid::hit(Coord c){
    grid_[c.X()][c.Y()] = tolower(grid_[c.X()][c.Y()]);
}