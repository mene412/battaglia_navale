// Autore: Andrea Mutti
#ifndef Coord_h
#define Coord_h

class Coord{
	
	public:
		Coord(int X, int Y);
		int X(void){ return X_;};
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

#endif