//Autore: Matteo Meneghin

#include "../include/DefenceGrid.h"

DefenceGrid::DefenceGrid(void)
    : Grid{}, ships_{}
{}

bool DefenceGrid::check_position(Coord& a, Coord& b, int dim, int pos) {
    std::vector<Coord> coord;
    if(a.X()<b.X()){
        for(int i = 0; i<dim; i++){
            Coord c{a.X()+i, a.Y()};
            coord.push_back(c);
        }
    }else if(a.X()>b.X()){
        for(int i = 0; i<dim; i++){
            Coord c{b.X()+i, a.Y()};
            coord.push_back(c);
        }
    }else if(a.Y()<b.Y()){
        for(int i = 0; i<dim; i++){
            Coord c{a.X(), a.Y()+i};
            coord.push_back(c);
        }
    }else if(a.Y()>b.Y()){
        for(int i = 0; i<dim; i++){
            Coord c{a.X(), b.Y()+i};
            coord.push_back(c);
        }
    } else if(a == b) {
        coord.push_back(a);
    }
    if(check_position(coord, pos)){
        return true;
    }else{
        return false;
    }
}

bool DefenceGrid::check_position(Coord& a){
    for(int i = 0; i<ships_.size(); i++){
        for(int j = 0; j<ships_.at(i)->coord().size(); j++){
            if(a == ships_.at(i)->coord().at(j)){
                return false;
            }
        }
    }
    return true;
}

bool DefenceGrid::check_position(std::vector<Coord>& coordinates, int pos) {
    for (int i = 0; i < coordinates.size(); i++) {
        for(int j = 0; j<ships_.size(); j++){
            if(j != pos){
                for(int k = 0; k<ships_.at(j)->coord().size(); k++){
                    if(coordinates.at(i) == ships_.at(j) -> coord().at(k)){
                        return false;
                    }
                }
            }else{
                if(ships_.at(j) -> center() == coordinates.at((int)(coordinates.size()/2))){
                    return false;
                }
            }
        }
    }
    return true;
}

int DefenceGrid::find_ship(Coord& x) {
    for (int i = 0; i < ships_.size(); i++) {
        if (ships_.at(i)->center() == x) {
            return i;
        }
    }
    throw std::invalid_argument("Nave non trovata");
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
    throw std::invalid_argument("Tipo non trovato");
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
    throw std::invalid_argument("Tipo non trovato");
}



void DefenceGrid::add_ship(Coord& front, Coord& back, int type) {
    if(type == 1){
        ships_.push_back(new Battleship{front, back});
    }else if(type == 2){
        ships_.push_back(new HelpShip{front, back});
    }else if(type == 3){
        ships_.push_back(new ExplorationSubmarine{front});
    }
    for (int i = 0; i < (ships_.at(ships_.size() - 1)->dim()); i++){
        int rowSelected = ships_.at(ships_.size() - 1)->coord().at(i).X();
        int columnSelected = ships_.at(ships_.size() - 1)->coord().at(i).Y();
        int type = type_ship(ships_.at(ships_.size() - 1));
        if(type == 1){
            grid_[rowSelected][columnSelected] = 'C';
        }else if(type == 2){
            grid_[rowSelected][columnSelected] = 'S';
        }else if(type == 3){
            grid_[rowSelected][columnSelected] = 'E';
        }
    }
}



std::vector<Coord> DefenceGrid::get_ship_coord(Coord& c, int pos) {
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
}

void DefenceGrid::remove_ship(int pos){
    delete ships_.at(pos);
    ships_.at(pos) = nullptr;
    ships_.erase(ships_.begin()+pos);
}

void DefenceGrid::reload(void){
    flush_grid();
    for(int i=0; i<number_ship(); i++){
        int type = type_ship(i);
        for(int j = 0; j<ships_.at(i) -> dim(); j++){
            if(type == 1){
                bool hit = false;
                if(ships_.at(i) -> coord_hit().size() == 0){
                    grid_[ships_.at(i) -> coord().at(j).X()][ships_.at(i) -> coord().at(j).Y()] = 'C';
                }else{
                    for(int k = 0; k<ships_.at(i) -> coord_hit().size(); k++){
                        if(ships_.at(i) -> coord_hit().at(k) == j){
                            hit = true;
                        }
                        if(hit){
                            grid_[ships_.at(i) -> coord().at(j).X()][ships_.at(i) -> coord().at(j).Y()] = 'c';
                        }else{
                            grid_[ships_.at(i) -> coord().at(j).X()][ships_.at(i) -> coord().at(j).Y()] = 'C';
                        }
                        hit = false;
                    }
                }
            }else if(type == 2){
                bool hit = false;
                if(ships_.at(i) -> coord_hit().size() == 0){
                    grid_[ships_.at(i) -> coord().at(j).X()][ships_.at(i) -> coord().at(j).Y()] = 'S';
                }else{
                    for(int k = 0; k<ships_.at(i) -> coord_hit().size(); k++){
                        if(ships_.at(i) -> coord_hit().at(k) == j){
                            hit = true;
                        }
                        if(hit){
                            grid_[ships_.at(i) -> coord().at(j).X()][ships_.at(i) -> coord().at(j).Y()] = 's';
                        }else{
                            grid_[ships_.at(i) -> coord().at(j).X()][ships_.at(i) -> coord().at(j).Y()] = 'S';
                        }
                        hit = false;
                    }
                }
            }else if(type == 3){
                grid_[ships_.at(i) -> coord().at(j).X()][ships_.at(i) -> coord().at(j).Y()] = 'E';
            }   
        }   
    }
}

void DefenceGrid::hit(Coord& c){
    grid_[c.X()][c.Y()] = tolower(grid_[c.X()][c.Y()]);
}

std::ostream& operator<<(std::ostream& os, DefenceGrid& a){
    os << "Griglia di difesa\n\n" << a.print_grid() << "\n" << std::endl;
    return os;
}

 DefenceGrid::~DefenceGrid(void){
    for(int i = 0; i<number_ship(); i++){
        delete ships_.at(i);
        ships_.at(i) = nullptr;
    }
 }
