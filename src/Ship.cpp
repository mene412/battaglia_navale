#include <iostream>
#include <exception>
#include "../include/Ship.h"

Ship::Ship(Coord front, Coord back)         // Costruttore di Ship, inizializza le variabili e richiama le funzioni per settare centro e orientamento della nave
    : front_{front}, back_{back}, healed_{true}, coord_hit_{}, dim_{0}, coord_{0}, armor_{0}, distance_{0}, orizzontal_{false}
{}

void Ship::set_center(void){                // Setta il centro della nave a partire da front e back
    if(orizzontal_){
        center_ = Coord{front_.X(), (back_.Y() + front_.Y())/2};
    }else{
        center_ = Coord{(back_.X() + front_.X())/2, front_.Y()};
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
            for(int i = 0; i<dim(); i++){
                coord_.push_back(Coord{front_.X(), front_.Y()+i});
                std::cout << i << " OK1" << std::endl;
            }
        }else{
            for(int i = 0; i<dim(); i++){
                coord_.push_back(Coord{back_.X(), back_.Y()+i});
                std::cout << i << " OK2 " << std::endl;
            }
        }
    }
    if(!orizzontal_){
        if(front_.X()<back_.X()){
            for(int i = 0; i<dim(); i++){
                coord_.push_back(Coord{front_.X()+i, front_.Y()});
                std::cout << i << " OK3" << std::endl;
            }
        }else{
            for(int i = 0; i<dim(); i++){
                coord_.push_back(Coord{back_.X()+i, back_.Y()});
                std::cout << i << " OK4 " << std::endl;
            }
        }
    }
}


void Ship::set_coord(std::vector<Coord>& coordinates){
    coord_=coordinates;
    set_coord_center(coordinates[distance_+1]);
}


void Ship::set_coord_center(Coord cord){        // Setta le coordinate a partire dal centro 
    center_ = cord;
    if(orizzontal_){
        front_ = Coord{cord.X(), cord.Y()-distance_};
        back_ = Coord{cord.X(), cord.Y()+distance_};
        for(int i = 0; i<coord_.size(); i++){
            coord_.at(i) = Coord{front_.X(), front_.Y()+i};
        }
    }
    if(!orizzontal_){
        front_ = Coord{cord.X()-distance_, cord.Y()};
        back_ = Coord{cord.X()+distance_, cord.Y()};
        for(int i = 0; i<coord_.size(); i++){
            coord_.at(i) = Coord{front_.X()+i, front_.Y()};
        }
    }
}

void Ship::set_armor(int a){
    armor_ = a;
}


void Ship::dec_armor(void){
    armor_--;
    healed_ = false;
}

void Ship::heal(void){
    armor_ = dim_;
    healed_ = true;
}

void Ship::hit(Coord c){
    for(int i = 0; i<coord_.size(); i++){
        if(coord_.at(i)==c){
            coord_hit_.push_back(i);
            dec_armor();
            return;
        }
    }
}