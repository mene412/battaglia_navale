// Autore: Andrea Mutti
#ifndef Coord_h
#define Coord_h

#include <string>

class Coord{
	public:
		// Costruttori
		Coord();	
		Coord(const Coord& c);				
		Coord(int X, int Y);
		Coord(Coord&& c);		

		// Metodi setter
		void setX(int X);
		void setY(int Y);

		// Metodi getter
		int X(void) const {return X_;};
		int Y(void) const {return Y_;};
		std::string coord(void);

		Coord& operator=(const Coord& c);
		Coord& operator=(Coord&& c);
	
	private:
		int X_;		// numero riga
		int Y_;		// numero colonna
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