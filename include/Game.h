// Autore: Andrea Mutti

#ifndef Game_h
#define Game_h

#include <fstream>
#include "DefenceGrid.h"
#include "AttackGrid.h"

class Game{
	public:
		virtual ~Game(){log.close();}
		int starter(void){return starter_;}
	
	protected:
		virtual void make_move(int s);
		Game(void);
		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;
		virtual int select_ship(int player);
		void add_ship(int player, Coord& p, Coord& c, int type);
		virtual void positioning(void) = 0;
		virtual void select_starter(void);
		int starter_;
		void write_log(std::string x);
		void write_log(std::pair<Coord, Coord>& x);
		int turn(void) const { return turn_;}

		AttackGrid att_grid1_;
		AttackGrid att_grid2_;
		DefenceGrid def_grid1_;
		DefenceGrid def_grid2_;

		std::pair<DefenceGrid, DefenceGrid> def_grid_;
		bool end(bool over);
		void fire(int pl, int pos, Coord& c);
		void move_ship(int pl, int pos, Coord& c);
		void heal(int pl, int pos, Coord& c);
		void search(int pl, int pos, Coord& c);
		void increment_turn(void);
		void titanic(int pl, int pos);
		void print_defence(int pl);
		void print_attack(int pl);

	private:
		int turn_;
		std::ofstream log;
		const int MAX_TURNS = 25;
};

namespace util{
	void to_upper(std::string& x);
}
#endif
