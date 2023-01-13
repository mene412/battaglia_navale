// Autore: Andrea Mutti

#ifndef Game_h
#define Game_h

#include <fstream>
#include "DefenceGrid.h"
#include "AttackGrid.h"

class Game{
	public:
		virtual ~Game(){log.close();};
		virtual void make_move(int s);
    	int starter(void){return starter_;}

	protected:
		Game(void);
		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;
		virtual std::pair<Coord,Coord> select_move(int player);
		void add_ship(int player, Coord p, Coord c, int type);
		virtual void positioning(void) = 0;
		virtual void select_starter(void);
		int starter_;
		void write_log(std::string x);
		void write_log(std::pair<Coord, Coord>& x);
		std::pair<AttackGrid, AttackGrid> att_grid_;
		std::pair<DefenceGrid, DefenceGrid> def_grid_;
		bool end_max_turn(void) const;
		void fire(int pl, int pos, Coord c);
		void move_ship(int pl, int pos, Coord c);
		void heal(int pl, int pos, Coord c);
		void search(int pl, int pos, Coord c);
		void increment_turn(void);
		void titanic(int pl, int pos);

	private:
		int turn_;
		std::ofstream log;
		const int MAX_TURNS = 250;
};

namespace util{
	void to_upper(std::string& x);
}
#endif
