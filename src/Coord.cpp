// Autore: Andrea Mutti

#include "../include/Coord.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

Coord::Coord()					// costruttore base
	: X_{0}, Y_{0}
{}

Coord::Coord(int X, int Y)		// costruttore che riceve in ingresso due parametri int, lancia eccezione se i valori sono errati
	: X_{X}, Y_{Y}
{
	if(X_<0 || X_>11 || Y_<0 || Y_>11){
		throw std::invalid_argument("Coordinate non valide");
	}
}

Coord::Coord(const Coord& c)	// copy contructor
	: X_{c.X()}, Y_{c.Y()}
{}


Coord::Coord(Coord&& c)			// move contructor
	: X_{c.X()}, Y_{c.Y()}	
{}

void Coord::setX(int x){		// setta le coordinata X dopo averne controllato la validità
	if(x<0 || x>11){
		throw std::invalid_argument("");
	}
	X_ = x;
}

void Coord::setY(int y){		// setta la coordinata Y dopo averne controllato la valità
	if(y<0 || y>11){
		throw std::invalid_argument("");
	}
	Y_ = y;
}

Coord& Coord::operator=(const Coord& c){		// overload operatori di assegnamento
	X_ = c.X(); 
	Y_ = c.Y();
	return *this;
}


Coord& Coord::operator=(Coord&& c){
	X_ = c.X();
	Y_ = c.Y();
	return *this;
}

std::string Coord::coord(){
	std::string c = "";
	c.push_back(UCoord::from_int_to_char(X()));
	c.push_back(Y_);
	return c;
}

Coord UCoord::random_coord(){	
	int x = rand()%12;
	int y = rand()%12;
	Coord coordinate{x,y};
	return coordinate;
}

Coord UCoord::random_coord(Coord c, int dim){
	int s = rand()%2;
    int x=c.X();
    int y=c.Y();
	if(s == 0){
		if((c.X()+dim)>=0 && (c.X()+dim)<=11){
			x = c.X()+dim;
			y = c.Y();
		}else{
			x = c.X()-dim;
			y = c.Y();
		}
	}else{
		if((c.Y()+dim)>=0 && (c.Y()+dim)<=11){
			y = c.Y()+dim;
			x = c.X();
		}else{
			y = c.Y()-dim;
			x = c.X();
		}
	}
	
	Coord coordinate{x,y};
	return coordinate;
}

char UCoord::from_int_to_char(int a){
	char c;
	std::string letters = "ABCDEFGHILMN";
	if(a<0 || a>11){
		throw std::invalid_argument("Coordinate non valide");
	}
	c = letters.at(a);
	return c;
}	

Coord UCoord::from_string_to_coord(std::string c){
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
	Coord coordinate{xf, (y-1)};
	return coordinate; 
}

std::ostream& operator<<(std::ostream& os, Coord& a){
	return os << UCoord::from_int_to_char(a.X()) << (a.Y()+1);
}

bool operator==(Coord a, Coord b){
	return a.X() == b.X() && a.Y() == b.Y();
}

bool operator!=(Coord a, Coord b){
	return !(a==b);
}
