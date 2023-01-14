//Autore: Matteo

#include "../include/DefenceGrid.h"
#include "../include/Battleship.h"
#include "../include/HelpShip.h"
#include "../include/ExplorationSubmarine.h"


DefenceGrid::DefenceGrid(void)
    : Grid{}, ships_{}
{}

bool DefenceGrid::check_position(Coord a, Coord b, int dim) {
    std::vector<Coord> coord;
    if(a.X()<b.X()){
        dim = b.X()-a.X();
        for(int i = 0; i<dim; i++){
            coord.push_back(Coord{a.X()+i, a.Y()});
        }
    }else if(a.X()>b.X()){
        dim = a.X()-b.X();
        for(int i = 0; i<dim; i++){
            coord.push_back(Coord{b.X()+i, a.Y()});
        }
    }else if(a.Y()<b.Y()){
        dim = b.Y()-a.Y();
        for(int i = 0; i<dim; i++){
            coord.push_back(Coord{a.X(), a.Y()+i});
        }
    }else if(a.Y()>b.Y()){
        dim = a.Y()-b.Y();
        for(int i = 0; i<dim; i++){
            coord.push_back(Coord{b.X(), a.Y()+i});
        }
    }
    for (int i = 0; i < coord.size(); i++) {
        int checkRow = coord[i].X();        // numero riga
        int checkColumn = coord[i].Y();    // numero colonna
        if (grid_[checkRow][checkColumn] != ' ') {
            // se la cella non è vuota, ritorna false
            return false;
        } 
    }
    return true;
}

bool DefenceGrid::check_position(Coord a){
    if(grid_[a.X()][a.Y()] == ' '){
        return true;
    }
    return false;
}

bool DefenceGrid::check_position(std::vector<Coord>& coordinates) {
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

int DefenceGrid::type_ship(Ship* ship){
    if(dynamic_cast<Battleship*>(ship) != nullptr){
        return 1; // battleship 
    }
    if(dynamic_cast<HelpShip*>(ship) != nullptr){
        return 2; // helpship
    }
    if(dynamic_cast<ExplorationSubmarine*>(ship) != nullptr){
        return 3; // Exploration
    }
}



void DefenceGrid::add_ship(Ship* new_ship) {
    std::cout << "Qua ci sono" << std::endl;
    ships_.push_back(new_ship);
    for (int i = 0; i < (new_ship->dim()); i++){
        int rowSelected = new_ship->coord().at(i).X();
        int columnSelected = new_ship->coord().at(i).Y();
        int type = type_ship(new_ship);
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


std::ostream& operator<<(std::ostream& os, DefenceGrid a){
    os << "\nGriglia di difesa\n\n" << a.print_grid() << "OK GRIGLIA" << std::endl;
    return os;
}