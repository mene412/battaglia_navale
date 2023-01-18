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
		

		void write_log(int player);
		void write_log(std::pair<Coord, Coord>& x);
		void check_dim(Coord& a, Coord& b, int dim);

		AttackGrid att_grid1_;
		AttackGrid att_grid2_;
		DefenceGrid def_grid1_;
		DefenceGrid def_grid2_;
		bool ship_went_down_;
		int starter_;

		bool end(bool over);
		
		void increment_turn(void);
		void titanic(int pl, int pos);
		void print_defence(int pl);
		void print_attack(int pl);

	private:
		int turn_;
		std::ofstream log_;
		const int MAX_TURNS = 2000;
};

namespace util{
	void to_upper(std::string& x);
}
#endif
