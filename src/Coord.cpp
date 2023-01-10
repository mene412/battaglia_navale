#include "Coord.h"
#include <time.h>
#include <stdlib.h>

Coord::Coord(int X, int Y)
	: X_{X}, Y_{Y}
{
	if(X_<1 || X_>12 || Y_<1 || Y_>12){
		throw new std::illegal_argument();
	}
}


std::string Coord::coord(){
	std::string c = "";
	c.push_back(from_int_to_char(X());
	c.push_back(Y_);
	return c;
}


static Coord Coord::random_coord(){
	srand(time(NULL));
	int x = rand()%11+1;
	int y = rand()%11+1;
	Coord coordinate{x,y};
	return coordinate;
}

static Coord Coord::random_coord(Coord c, int dim){
	srand(time(NULL));
	int s = rand()%2;
	int x;
	int y;
	if(s == 0){
		int t = (int)(c.X);
		if((c.X+dim)>=1 && (c.Y+dim)<=12){
			x = c.X+dim;
		}else{
			x = c.X-dim;
		}
	}else if(s == 1){
		if((c.Y+dim)>=1 && (c.Y+dim)<=12){
			y = c.Y+dim;
		}else{
			y = c.Y-dim;
		}
	}
	
	Coord coordinate{x,y};
	return coordinate;
}

static char Coord::from_int_to_char(int a){
	char c;	
	a--;
	std::string letters = "ABCDEFGHILMN";
	if(a<0 || a>11){
		throw new std::illegal_arguments();
	}
	c = letters.at(a);
	return c;
}	

static Coord from_string_to_coord(std::string c){
	if(c.length()<2 || c.length()>3){
		throw new std::illegal_argument();
	}
	char x = c.at(0);
	int y = stoi(c.substr(1));
	char in = 'A';
	char fin = 'N';
	if(x<in || x>fin){
		throw new std::illegal_argument();
	}
	if(x=='J' || x=='K'){
		throw new std::illegal_argument();
	}
	int xf;
	if(x<='I'){
		xf = x-'A'+1;
	}
	if(x=='L'){
		xf = 10;
	}
	if(x=='M'){
		xf = 11;
	}
	if(x=='N'){
		xf = 12;
	}
	Coord coordinate{xf, y};
	return coordinate; 
}

std::ostream& operator<<(std::ostream& os, Coord a){
	return os << from_int_to_char(a.X) << a.Y;
}
