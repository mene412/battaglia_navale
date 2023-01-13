// Autore: Andrea Mutti
#ifndef Coord_h
#define Coord_h

#include <string>

class Coord{
	
	public:
		Coord();					
		Coord(int X, int Y);		// costruttore: parametro X -> seleziona riga, parametro Y -> selezione colonna
		void setX(int X);
		void setY(int Y);
		int X(void){return X_;};
		int Y(void){return Y_;};
		std::string coord(void);
	private:
		int X_;
		int Y_;
};

namespace UCoord {
	static Coord random_coord();
	static Coord random_coord(Coord c, int dim);
	static char from_int_to_char(int a);
	static Coord from_string_to_coord(std::string c);
}

std::ostream& operator<<(std::ostream& os, Coord a);
bool operator==(Coord a, Coord b);
bool operator!=(Coord a, Coord b);
#endif