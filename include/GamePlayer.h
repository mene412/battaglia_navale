#ifndef "Game_Player_h"
#define "Game_Player_h

#include "Game.h"
#include "Coord.h"

class Game_Player: public Game{
 	public:
 		Game_Player(void);
 		
 	private:
 		void select_starter(void) override;
 		void positioning(void);
 		void positioning_player(void);
 		void positioning_pc(void);
#endif
