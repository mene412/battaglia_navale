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

