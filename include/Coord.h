// Autore: Andrea Mutti
#ifndef COORD_H
#define COORD_H

#include <string>

class Coord{
	public:
		// Costruttori e costruttori di copia -> necessari
		Coord();	
		Coord(int X, int Y);
		Coord(const Coord& c);		// copy constructor
		Coord(Coord&& c);			// move constructor

		// Metodi setter
		void setX(int X);			// setta la riga
		void setY(int Y);			// setta la colonna

		// Metodi getter
		int X(void) const {return X_;};		// restituisce la riga
		int Y(void) const {return Y_;};		// restituisce la colonna
		std::string coord(void);			// restituisce la coordinata in formato
											// char-int
		// Overload operatori di assegnamento
		Coord& operator=(const Coord& c);
		Coord& operator=(Coord&& c);
	
	private:
		// Variabili membro private
		int X_;		// numero riga
		int Y_;		// numero colonna
};

// Overload operratori - helper functions
std::ostream& operator<<(std::ostream& os, Coord& a);	// overload output
bool operator==(Coord a, Coord b);						// overload operatore di confronto
bool operator!=(Coord a, Coord b);						// uguaglianza e disuguaglianza


// Namepsace per alcune funzioni di utilità (Utility Coord)
namespace UCoord {
	Coord random_coord();						// crea una coordinata randomica
	Coord random_coord(Coord c, int dim);		// coordinata pseudo-randomica a partire da una già definita e una dimensione
	char from_int_to_char(int a);				// resistuisce un char a partire da un int (utile per la stampa)
	Coord from_string_to_coord(std::string c);	// conversione da stringa in entrata a coordinata
}												// utile in ingresso

#endif
