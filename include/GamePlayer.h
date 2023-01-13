// Autore: Andrea Mutti

#ifndef Game_Player_h
#define Game_Player_h

#include "Game.h"
#include "Coord.h"

class GamePlayer: public Game{
 	public:
 	    GamePlayer(void);
 		void make_move(int s) override;
 	private:
 		void select_starter(void) override;
 		void positioning(void) override;
		std::pair<Coord,Coord> select_move(int player) override;
 		void positioning_player(void);
 		void positioning_pc(void);
};
#endif
