// Autore: Andrea Mutti
#ifndef COORD_H
#define COORD_H

#include <string>

// Classe di gestione delle coordinate di una griglia 12X12
class Coord{
	public:
		// Costruttore che non riceve parametri in ingresso
		Coord();	
		// Costruttore che riceve in ingresso due interi, controlla la validità
		Coord(int X, int Y);
		// Copy constructor
		Coord(const Coord& c);
		// Move constructor
		Coord(Coord&& c);

		// Metodi setter
		// Setta la riga della coordinata
		void setX(int X);	
		// Setta la riga della colonna		
		void setY(int Y);			

		// Metodi getter
		// Ritorna la riga della coordinata come int
		int X(void) const {return X_;};	
		// Ritorna la colonna della coordinata come int
		int Y(void) const {return Y_;};	
		// restituisce la coordinata in formato char -int
		std::string coord(void);			

		// Overload operator di assegnamento
		Coord& operator=(const Coord& c);
		// Overload assegnamento
		Coord& operator=(Coord&& c);
	
	private:
		// Variabili membro private
		// numero riga
		int X_;	
		// numero colonna	
		int Y_;		
};

// Overload operratori - helper functions
// Overload operatore di output
std::ostream& operator<<(std::ostream& os, Coord& a);
// Overload operatore di uguaglianza
// Ritorna true se le due variabili x e le due variabili y sono uguali
bool operator==(Coord a, Coord b);	
// Overload operatore di disuguaglianza		
// Ritorna true se almeno una variabile del primo oggetto non è uguale alla variabile del secondo			
bool operator!=(Coord a, Coord b);						


// Namepsace per alcune funzioni di utilità con le coordinate (Utility Coord)
namespace UCoord {
	// Crea una coordinata randomica
	Coord random_coord();			
	// Crea una coordinata pseudo-randomica a partire da una già definita e una dimensione			
	Coord random_coord(Coord c, int dim);	
	// Resistuisce un valore di tipo char a partire dall'int corrispondente
	// Utile per stampare il valore della variabile x
	char from_int_to_char(int a);		
	// Conversione da stringa a Coord
	// Utile in ingresso per la lettura di una coordinata
	// Lancia eccezione se non valida
	Coord from_string_to_coord(std::string c);	
}

#endif // COORD_H
