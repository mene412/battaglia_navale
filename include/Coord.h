#ifndef "Coord_h"
#define "Coord_h"

class Coord{
	
	public:
		Coord();
		char X{ return X_}
		int Y{ return Y_}
		
		static Coord random_coord();
		static Coord random_coord(Coord c, int dim);
		static char from_int_to_char(int a);
		static Coord from_string_to_coord(std::string c);
	private:
		char X_;
		int Y_;
};

std::ostream& operator<<(std::ostream& os, Coord a);

#endif
