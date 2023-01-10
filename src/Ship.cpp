#include <iostream>
#include <exception>
#include "Ship.h"
Ship::Ship(void){
    coord_={{0,0},{0,0},{0,0},{0,0},{0,0}}; //nave inizializzata "fuori dal gioco"
}

void Ship::setInitialCoord(int x1, int x2, int y1, int y2){
   if(x1==x2 && std::max(y1,y2)-std::min(y1,y2)+1==dim_){
        for(int i=0; i<dim_; i++){
            coord_[i].first=x1;
            coord_[i].second=std::min(y1,y2)+i;
        }
    }
    else if(y1==y2 && std::max(x1,x2)-std::min(x1,x2)+1==dim_){
        for(int i=0; i<dim_; i++){
            coord_[i].first=std::min(x1,x2)+i;;
            coord_[i].second=y1;
        }
    }
    else{ throw std::out_of_range("NO");}  //coordinate non valide
    return;
}

void Ship::setHealed(bool a){
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

char conversion::NumToLett(int t){
    std::vector<char> letters={'a','b','c','d','e','f','g','h','i','l','m','n'};
    return letters[t-1];
}

int conversion::CharToInt(char t){
    std::vector<char> letters={'a','b','c','d','e','f','g','h','i','l','m','n'};
    int s=0;
    while(letters[s]!=t)
        s++;
    return s+1;
}
