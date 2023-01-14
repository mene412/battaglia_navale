#include <iostream>
#include <exception>
#include "../include/Ship.h"

Ship::Ship(Coord front, Coord back)         // Costruttore di Ship, inizializza le variabili e richiama le funzioni per settare centro e orientamento della nave
    : front_{front}, back_{back}, distance_{0}, healed_{true}, coord_{0}, coord_hit_{}
{
    set_direction();
    set_center();
    set_coord_center();
}

void Ship::set_center(void){                // Setta il centro della nave a partire da front e back
    if(front_.X() == back_.X()){
        int y = (front_.Y() + back_.Y())/2;
        center_ = Coord{front_.X(), y};
    }else if(front_.Y() == back_.Y()){
        int x = (front_.X() + back_.X())/2;
        center_ = Coord{x, front_.Y()};
    }else{
        throw std::invalid_argument("Errore");
    }
}

void Ship::set_direction(void){     // Setta l'orientamento della nave [orizzontal_ = true -> orizzontale]
    if(front_.Y() < back_.Y()){
        orizzontal_ = true;
    }else if(front_.Y() > back_.Y()){
        orizzontal_ = true;
    }else if(front_.X() < back_.X()){
        orizzontal_ = false;
    }else if(front_.X() > back_.X()){
        orizzontal_ = false;
    }
}

void Ship::set_coord_center(void){             // Setta le coordinate iniziali
    if(orizzontal_){
        for(int i = 0; i<dim_; i++){
            coord_.push_back(Coord{center_.X(), center_.Y()-distance_+i});
        }
    }
    if(!orizzontal_){
        for(int i = 0; i<dim_; i++){
            coord_.push_back(Coord{center_.X()-distance_+i, center_.Y()});
        }
    }
}


void Ship::set_coord(std::vector<Coord>& coordinates){
    coord_=coordinates;
    set_coord_center(coordinates[(int)dim_/2]);
}

void Ship::set_coord_center(Coord cord){        // Setta le coordinate a partire dal centro 
    center_ = cord;
    if(orizzontal_){
        for(int i = 0; i<coord_.size(); i++){
            coord_.at(i) = Coord{cord.X(), cord.Y()-distance_+i};
        }
    }
    if(!orizzontal_){
        for(int i = 0; i<coord_.size(); i++){
            coord_.at(i) = Coord{cord.X()-distance_+i, cord.Y()};
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