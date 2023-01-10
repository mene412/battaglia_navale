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
		Ship ship(int pos){return *(ship_.at(pos));}
		int number_ship(){return ship_.size();}
		
	protected:
		Game(void);
		virtual std::pair<Coord,Coord> select_move(int player);
		void add_ship(int player, Coord p, Coord c, char type);
		virtual void positioning(void) = 0;
		virtual void select_starter(void);
		int starter_;

	private:
		AttackGrid att_grid1_;
		DefenceGrid def_grid1_;
		AttackGrid att_grid2_;
		DefenceGrid def_grid2_;
		int turn_;
		std::vector<Ship*> ship_;
};

#endif
