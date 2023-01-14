// Autore: Andrea Mutti

#ifndef Game_Player_h
#define Game_Player_h

#include "Game.h"

class GamePlayer: public Game{
 	public:
 	    GamePlayer(void);
		void start(void);
 	private:
		void make_move(int s) override;
 		void select_starter(void) override;
 		void positioning(void) override;
		int select_ship(int player);
		Coord select_target(int player);
 	private:
		void positioning_player(void);
 		void positioning_pc(void);
};
#endif
