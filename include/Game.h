// Autore: Andrea Mutti

#ifndef Game_h
#define Game_h

#include <vector>
#include <fstream>
#include "Coord.h"
#include "Ship.h"
#include "DefenceGrid.h"
#include "AttackGrid.h"

class Game{
	public:
		virtual ~Game(){log.close();};
		void make_move(int s);
    	int starter(void){return starter_;}

	protected:
		Game(void);
		virtual std::pair<Coord,Coord> select_move(int player);
		void add_ship(int player, Coord p, Coord c, char type);
		virtual void positioning(void) = 0;
		virtual void select_starter(void);
		int starter_;
		void write_log(std::string x);
		void write_log(std::vector<std::string>& x);
		void write_log(std::pair<Coord, Coord>& x);
		std::pair<AttackGrid, AttackGrid> att_grid_;
		std::pair<DefenceGrid, DefenceGrid> def_grid_;

	private:
		int turn_;
		std::ofstream log;
};

#endif
