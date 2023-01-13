#include <iostream>
#include <exception>
#include "Ship.h"

Ship::Ship(Coord front, Coord back)
    : front_{front}, back_{back}, distance_{0} 
{
    set_center();
    set_direction();
}

void Ship::set_center(void){
    if(front_.X() == back_.X()){
        int y = (front_.Y() + back_.Y())/2;
        center_ = Coord{front_.X(), y};
    }else if(front_.Y() == back_.Y()){
        int x = (front_.X() + back_.X())/2;
        center_ = Coord{x, front_.Y()};
    }
}

void Ship::set_direction(void){
    if(front_.X() < back_.X()){
        left_ = true;
        orizzontal_ = true;
    }else if(front_.X() > back_.X()){
        left_ = false;
        orizzontal_ = true;
    }else if(front_.Y() < back_.Y()){
        left_ = true;
        orizzontal_ = false;
    }else if(front_.Y() >= back_.Y()){
        left_ = false;
        orizzontal_ = false;
    }
}

void Ship::set_coord_center(Coord cord){
    center_ = cord;
    if(left_ && orizzontal_){
        front_.setX(cord.X()-distance_);
        back_.setX(cord.X()+distance_); 
        front_.setY(cord.Y());
        back_.setY(cord.Y());
    }else if(!left_ && orizzontal_){
        front_.setX(cord.X()+distance_);
        back_.setX(cord.X()-distance_); 
        front_.setY(cord.Y());
        back_.setY(cord.Y());
    }else if(left_ && !orizzontal_){
        front_.setY(cord.Y()-distance_);
        back_.setY(cord.Y()+distance_); 
        front_.setX(cord.X());
        back_.setX(cord.X());
    }else if(!left_ && !orizzontal_){
        front_.setY(cord.Y()+distance_);
        back_.setY(cord.Y()-distance_);
        front_.setX(cord.X());
        back_.setX(cord.X());
    }
}

void Ship::set_armor(int a){
    armor_=a;
}

void Ship::set_healed(bool a){
    healed_=a;
}

void Ship::set_coord(std::vector<Coord>& coordinates){
    coord_=coordinates;
    set_coord_center(coordinates[(int)dim_/2]);
}
