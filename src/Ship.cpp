#include <iostream>
#include <exception>
#include "Ship.h"
Ship::Ship(void){
    coord_={{0,0},{0,0},{0,0},{0,0},{0,0}}; //nave inizializzata "fuori dal gioco"
}

char Ship::GetType(void){
    return type_;
}

void Ship::SetCoord(void){
    std::cout<<"Inserisci le coordinate di prua e di poppa"<<std::endl;
    int y1,y2;
    char p1,p2;
    std::cin>>p1;
    std::cin>>y1;
    std::cin>>p2;
    std::cin>>y2;
    int x1=conversion::CharToInt(p1);
    int x2=conversion::CharToInt(p2);
    SetX(x1, x2);
    SetY(y1, y2);
    if(x1==x2 && std::max(y1,y2)-std::min(y1,y2)+1==dim_){
        for(int i=0; i<dim_; i++){
            coord_[i][0]=x1;
            coord_[i][1]=std::min(y1,y2)+i;
        }
    }
    else if(y1==y2 && std::max(x1,x2)-std::min(x1,x2)+1==dim_){
        for(int i=0; i<dim_; i++){
            coord_[i][0]=std::min(x1,x2)+i;;
            coord_[i][1]=y1;
        }
    }
    else{ throw std::out_of_range("NO");}   //eventuali eccezioni ancora da gestire
    return;
}

int const Ship::GetCoord(int n1, int n2){ return coord_[n1][n2];}

int const Ship::GetDim(void){ return dim_;}

int Ship::GetArmor(void){ return armor_;}

int Ship::GetX(void){ return x_;}

int Ship::GetY(void){return y_;}

void Ship::SetX(int x1, int x2){
    x_=(x1+x2)/2;
    return;
}

void Ship::SetY(int y1, int y2){
    y_=(y1+y2)/2;
    return;
}

void Ship::SetHealed(bool a){
  healed_=a;
}

void Ship::DecArmor(void){
  armor_=armor_-1;
}

void Ship::IncArmor(void){
  armor_=armor_+1;
}

bool Ship:: Healed(void){
  return healed_
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
