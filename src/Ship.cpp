//AUTORE: Gaia Soso
#include "Ship.h"

Ship::Ship(Coord& front, Coord& back)       //definizione costruttore Ship
    : front_{front}, back_{back}, healed_{true}, coord_hit_{}, dim_{0}, coord_{}, armor_{0}, distance_{0}, orizzontal_{false}
{}

void Ship::set_center(void){
    if(orizzontal_){
        Coord c{front_.X(), (back_.Y() + front_.Y())/2};        //coordinata del centro di una nave orizzontale
        center_ = c;
    }else{
        Coord c{(back_.X() + front_.X())/2, front_.Y()};        //coordinata del centro di una nave verticale
        center_ = c;
    }
}



void Ship::set_direction(void){
    if(front_.Y()==back_.Y()){                  //se le ordinate di prua e di poppa sono uguali la nave è verticale
        if(front_.X()!=back_.X()){
            orizzontal_ = false;               
        }else{
            throw std::invalid_argument("Errore");
        }
    }else if(front_.X()==back_.X()){             //se le ascisse di prua e di poppa sono uguali la nave è orizzontale
        if(front_.Y()!=back_.Y()){
            orizzontal_ = true;
        }else{
            throw std::invalid_argument("Errore");
        }
    }else{
        throw std::invalid_argument("Errore");      //altrimenti coordinate non valide ed eccezione lanciata
    }
}

void Ship::set_coord_center(void){
    if(orizzontal_){
        if(front_.Y()<back_.Y()){
            for(int i = 0; i<dim_; i++){
                Coord c{front_.X(), front_.Y()+i};
                coord_.push_back(c);                    //"caricamento" della coordinata nel vettore coord
            }
        }else{
            for(int i = 0; i<dim_; i++){
                Coord c{back_.X(), back_.Y()+i};
                coord_.push_back(c);                    //"caricamento" della coordinata nel vettore coord
            }
        }
    }
    if(!orizzontal_){
        if(front_.X()<back_.X()){
            for(int i = 0; i<dim_; i++){
                Coord c{front_.X()+i, front_.Y()};
                coord_.push_back(c);                  //"caricamento" della coordinata nel vettore coord
            }
        }else{
            for(int i = 0; i<dim_; i++){
                Coord c{back_.X()+i, back_.Y()};
                coord_.push_back(c);                 //"caricamento" della coordinata nel vettore coord
            }
        }
    }
}


void Ship::set_coord(std::vector<Coord>& coordinates){
    if(coordinates.size()!=dim_){
        throw std::invalid_argument("Dimensione coordinate non valida"); //se il vettore di coordinate ha dimensione maggiore della nave viene                                                                  lanciata un'eccezione
    }
    coord_=coordinates;
    set_coord_from_center(coordinates[distance_+1]); //distance+1 è la coordinata centrale che identifica il centro della nave
}


void Ship::set_coord_from_center(Coord& cord){
    center_ = cord;
    if(orizzontal_){                            //caso nave orizzontale
        front_ = Coord{cord.X(), cord.Y()-distance_};
        back_ = Coord{cord.X(), cord.Y()+distance_};
        for(int i = 0; i<dim_; i++){                 //inserimento delle coordinate da quella di prua a quella di poppa nel vettore coord_
            Coord c{front_.X(), front_.Y()+i};
            coord_.at(i) = c;
        }
    }
    if(!orizzontal_){                           //caso nave verticale 
        front_ = Coord{cord.X()-distance_, cord.Y()};
        back_ = Coord{cord.X()+distance_, cord.Y()};
        for(int i = 0; i<dim_; i++){                 //inserimento delle coordinate da quella di prua a quella di poppa nel vettore coord_
            Coord c{front_.X()+i, front_.Y()};
            coord_.at(i) = c;
        }
    }
}

void Ship::set_armor(int a){
    if(a<0 || a>dim_){
        throw std::invalid_argument("Errore"); //se il parametro a inserito è minore di 0 o maggiore della dimensione dell'armatura viene                                             lanciata un'eccezione
    }
    armor_ = a;
}

void Ship::set_healed(bool heal) {
    healed_ = heal;
}


void Ship::dec_armor(void){
    armor_--;                   //decremento dell'armatura di 1
    healed_ = false;            //variabile healed impostata a false così che la nave possa essere riparata
}

void Ship::heal(void){
    armor_ = dim_;      //riporta la dimensione dell'armatura alla dimensione della nave
    healed_ = true;     //variabile healed impostata ad indicare che è stata riparata
    coord_hit_.clear(); //cancella il contenuto del vettore coord_hit_ dato che la nave è stata curata
}

void Ship::hit(Coord& c){
    for(int i = 0; i<dim(); i++){
        if(coord_.at(i)==c){
            for(int j = 0; j<coord_hit_.size(); j++){ //si scorre il vettore coord_hit per vedere se c'è un elemento uguale alla posizione della                                          coordinata colpita della nave
                if(coord_hit_.at(j) == i){
                    return;
                }
            }
            coord_hit_.push_back(i); //posizione della coordinata colpita inserita nel vettore delle coordinate colpite.
            dec_armor();
            return;
        }
    }
}
