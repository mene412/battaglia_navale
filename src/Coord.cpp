#include "Coord.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>

Coord::Coord()
	: X_{0}, Y_{0}
{}

void Coord::setX(int x){
	if(x<0 || x>11){
		throw std::invalid_argument("");
	}
	X_ = x;
}

void Coord::setY(int y){
	if(y<0 || y>11){
		throw std::invalid_argument("");
	}
	Y_ = y;
}

Coord::Coord(int X, int Y)
	: X_{X}, Y_{Y}
{
	if(X_<0 || X_>11 || Y_<0 || Y_>11){
		throw std::invalid_argument("Coordinate non valide");
	}
}


std::string Coord::coord(){
	std::string c = "";
	c.push_back(UCoord::from_int_to_char(X()));
	c.push_back(Y_);
	return c;
}

static Coord UCoord::random_coord()
{
    srand(time(NULL));
	int x = rand()%11;
	int y = rand()%11;
	Coord coordinate{x,y};
	return coordinate;
}

static Coord UCoord::random_coord(Coord c, int dim){
	srand(time(NULL));
	int s = rand()%2;
	int x;
	int y;
	if(s == 0){
		int t = (int)(c.X());
		if((c.X()+dim)>=0 && (c.Y()+dim)<=11){
			x = c.X()+dim;
		}else{
			x = c.X()-dim;
		}
	}else if(s == 1){
		if((c.Y()+dim)>=0 && (c.Y()+dim)<=11){
			y = c.Y()+dim;
		}else{
			y = c.Y()-dim;
		}
	}
	
	Coord coordinate{x,y};
	return coordinate;
}

static char UCoord::from_int_to_char(int a){
	char c;	
	a--;
	std::string letters = "ABCDEFGHILMN";
	if(a<0 || a>11){
		throw std::invalid_argument("Coordinate non valide");
	}
	c = letters.at(a);
	return c;
}	

static Coord UCoord::from_string_to_coord(std::string c){
	if(c.length()<2 || c.length()>3){
		throw std::invalid_argument("Coordinate non valide");
	}
	char x = c.at(0);
	int y = stoi(c.substr(1));
	char in = 'A';
	char fin = 'N';
	if(x<in || x>fin){
		throw std::invalid_argument("Coordinate non valide");
	}
	if(x=='J' || x=='K'){
		throw std::invalid_argument("Coordinate non valide");
	}
	int xf;
	if(x<='I'){
		xf = x-in;
	}
	if(x=='L'){
		xf = 9;
	}
	if(x=='M'){
		xf = 10;
	}
	if(x=='N'){
		xf = 11;
	}
	Coord coordinate{xf, y};
	return coordinate; 
}

std::ostream& operator<<(std::ostream& os, Coord a){
	return os << UCoord::from_int_to_char(a.X()) << (a.Y()+1);
}

bool operator==(Coord a, Coord b){
	return a.X() == b.X() && a.Y() == b.Y();
}

bool operator!=(Coord a, Coord b){
	return !(a==b);
}