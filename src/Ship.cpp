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

void Ship::set_coord_center(int x, int y){
    center_ = Coord{x, y};
    if(left_ && orizzontal_){
        front_.setX(x-distance_);
        back_.setX(x+distance_); 
    }
}


void Ship::set_healed(bool a){
    healed_=a;
}

void Ship::decArmor(void){
  armor_=armor_-1;
}

void Ship::incArmor(void){
  armor_=armor_+1;
}

bool Ship::ifSameCoord(int x, int y){
  for(int i=0; i<dim_; i++){
    if(coord_[i].first==x && coord_[i].second==y)
      return true;
  }
  return false; 
}

