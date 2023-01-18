// Autore: Andrea Mutti

#ifndef GAME_H
#define GAME_H

#include <fstream>	// libreria fstream per gestire output su file di log
#include "DefenceGrid.h"
#include "AttackGrid.h"

class Game{
	public:	
		// Distruttore
		virtual ~Game(){log_.close();}		// distruttore virtual con chiusura file di log
		
		// Metodi getter
		int starter(void){return starter_;} 						// player iniziale
		bool ship_went_down(void) const { return ship_went_down_;}	// utile per il controllo di una nave abbattuta
		int turn(void) const { return turn_;}						// turno del gioco
	
	protected:
		// Costruttore
		Game(std::string log_file);
		Game(const Game&) = delete;				// costruttore di copia disabilitato
		Game& operator=(const Game&) = delete;	// assegnamento di copia disabilitato

		// Funzioni virtual
		virtual void make_move(int s);		
		virtual void select_starter(void);
		virtual void positioning(void) = 0;		// positioning virtuale pura (ogni classe derivata gestisce il poszionamento navi)

		// Funzioni membro
		void add_ship(int player, Coord& p, Coord& c, int type);	// aggiunta della nave nella rispettiva griglia di difesa
		
		int select_ship(int player);			// selezione randomica di una nave
		void fire(int pl, int pos, Coord& c);	// azioni delle navi
		void move_ship(int pl, int pos, Coord& c);
		void heal(int pl, int pos, Coord& c);	// passaggio di oggetti Coord avvengono per riferimento
		void search(int pl, int pos, Coord& c);
		
		// Scrittura del file di log
		void write_log(int player);						// player che inizia
		void write_log(std::pair<Coord, Coord>& x);		// coordinate delle navi o delle mosse

		// Turno successivo e controllo di fine partita
		bool end(bool over);
		void increment_turn(void);

		// Stampa delle griglie di attacco e difesa
		void print_defence(int pl);
		void print_attack(int pl);

		// Variabili d'esemplare protected - accessibili alle classi derivate
		AttackGrid att_grid1_;
		AttackGrid att_grid2_;		// griglie di attacco e difesa
		DefenceGrid def_grid1_;
		DefenceGrid def_grid2_;
		bool ship_went_down_;		// variabile di utilità
		int starter_;				// giocatore iniziale

	private:
		// Funzione membro private
		void titanic(int pl, int pos);		// chiamata solamente dalla classe Game
		
		// Variabili d'esemplare private
		int turn_;						// turno corrente
		std::ofstream log_;				// oggetto ofstream per output su file di log
		const int MAX_TURNS = 2000;		// massimo numero di turni per evitare stalli
};

namespace util{							// namespace di utilità
	void to_upper(std::string& x);		// conversione di una stringa in maiuscolo, sfruttando il metodo std::toupper(char)
}
#endif
