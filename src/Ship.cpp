#include <iostream>
#include <exception>
#include "Ship.h"
Ship::Ship(void){
    coord_={{0,0},{0,0},{0,0},{0,0},{0,0}}; //nave inizializzata "fuori dal gioco"
}

void Ship::set_coord(void){
    std::cout<<"Inserisci le coordinate di prua e di poppa"<<std::endl;
    int y1,y2;
    char p1,p2;
    std::cin>>p1;
    std::cin>>y1;
    std::cin>>p2;
    std::cin>>y2;
    int x1=conversion::CharToInt(p1);
    int x2=conversion::CharToInt(p2);
    //SetX(x1, x2);
    //SetY(y1, y2);
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


// int const Ship::coord(int n1, int n2){ return coord_[n1][n2];}

void Ship::set_x(int x1, int x2){
    x_=(x1+x2)/2;
    return;
}

void Ship::set_y(int y1, int y2){
    y_=(y1+y2)/2;
    return;
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
