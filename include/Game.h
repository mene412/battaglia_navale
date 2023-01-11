// Autore: Andrea Mutti

#ifndef Game_h
#define Game_h

#include <vector>
#include "Coord.h"
#include "Ship.h"

class Game{
	public:
		virtual ~Game(){};
		void make_move(int s);
    	int starter(void){return starter_;}

	protected:
		Game(void);
		virtual std::pair<Coord,Coord> select_move(int player);
		void add_ship(int player, Coord p, Coord c, char type);
		virtual void positioning(void) = 0;
		virtual void select_starter(void);
		int starter_;

	private:
		std::pair<AttackGrid, AttackGrid> att_grid_;
		std::pair<DefenceGrid, DefenceGrid> def_grid_;
		int turn_;
};

#endif
