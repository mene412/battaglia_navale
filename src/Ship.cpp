
#include "../include/Ship.h"

Ship::Ship(Coord& front, Coord& back)         // Costruttore di Ship, inizializza le variabili e richiama le funzioni per settare centro e orientamento della nave
    : front_{front}, back_{back}, healed_{true}, coord_hit_{}, dim_{0}, coord_{}, armor_{0}, distance_{0}, orizzontal_{false}, x_{0}, y_{0}
{}

void Ship::set_center(void){                // Setta il centro della nave a partire da front e back
    if(orizzontal_){
        Coord c{front_.X(), (back_.Y() + front_.Y())/2};
        center_ = c;
        x_ = front_.X();
        y_ = (back_.Y() + front_.Y()/2);
    }else{
        Coord c{(back_.X() + front_.X())/2, front_.Y()};
        center_ = c;
        x_ = (back_.X() + front_.X()/2);
        y_ = front_.Y();
    }
}



void Ship::set_direction(void){     // Setta l'orientamento della nave [orizzontal_ = true -> orizzontale]
    if(front_.Y()==back_.Y()){
        if(front_.X()!=back_.X()){
            orizzontal_ = false;
        }else{
            throw std::invalid_argument("Errore");
        }
    }else if(front_.X()==back_.X()){
        if(front_.Y()!=back_.Y()){
            orizzontal_ = true;
        }else{
            throw std::invalid_argument("Errore");
        }
    }else{
        throw std::invalid_argument("Errore");
    }
}

void Ship::set_coord_center(void){             // Setta le coordinate iniziali
    if(orizzontal_){
        if(front_.Y()<back_.Y()){
            for(int i = 0; i<dim_; i++){
                Coord c{front_.X(), front_.Y()+i};
                coord_.push_back(c);
            }
        }else{
            for(int i = 0; i<dim_; i++){
                Coord c{back_.X(), back_.Y()+i};
                coord_.push_back(c);
            }
        }
    }
    if(!orizzontal_){
        if(front_.X()<back_.X()){
            for(int i = 0; i<dim_; i++){
                Coord c{front_.X()+i, front_.Y()};
                coord_.push_back(c);
            }
        }else{
            for(int i = 0; i<dim_; i++){
                Coord c{back_.X()+i, back_.Y()};
                coord_.push_back(c);
            }
        }
    }
}


void Ship::set_coord(std::vector<Coord>& coordinates){
    if(coordinates.size()!=dim_){
        throw std::invalid_argument("Dimensione coordinate non valida");
    }
    coord_=coordinates;
    set_coord_from_center(coordinates[distance_+1]);
}


void Ship::set_coord_from_center(Coord& cord){        // Setta le coordinate a partire dal centro 
    center_ = cord;
    x_ = cord.X();
    y_ = cord.Y();
    if(orizzontal_){
        front_ = Coord{cord.X(), cord.Y()-distance_};
        back_ = Coord{cord.X(), cord.Y()+distance_};
        for(int i = 0; i<dim_; i++){
            Coord c{front_.X(), front_.Y()+i};
            coord_.at(i) = c;
        }
    }
    if(!orizzontal_){
        front_ = Coord{cord.X()-distance_, cord.Y()};
        back_ = Coord{cord.X()+distance_, cord.Y()};
        for(int i = 0; i<dim_; i++){
            Coord c{front_.X()+i, front_.Y()};
            coord_.at(i) = c;
        }
    }
}

void Ship::set_armor(int a){
    if(a<0 || a>dim_){
        throw std::invalid_argument("Errore");
    }
    armor_ = a;
}

void Ship::set_healed(bool heal) {
    healed_ = heal;
}


void Ship::dec_armor(void){
    armor_--;
    healed_ = false;
}

void Ship::heal(void){
    armor_ = dim_;
    healed_ = true;
    coord_hit_.clear();
}

void Ship::hit(Coord& c){
    for(int i = 0; i<dim(); i++){
        if(coord_.at(i)==c){
            coord_hit_.push_back(i);
            dec_armor();
            return;
        }
    }
}