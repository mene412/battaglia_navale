<<<<<<< Updated upstream
// Autore: Andrea Mutti

#ifndef Game_Player_h
#define Game_Player_h

#include "Game.h"
#include "Coord.h"

class GamePlayer: public Game{
 	public:
 	    GamePlayer(void);
 		
 	private:
 		void select_starter(void) override;
 		void positioning(void) override;
 		void positioning_player(void);
 		void positioning_pc(void);
};
#endif
=======
// Autore: Andrea Mutti

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "Game.h"

class GamePlayer: public Game{
 	public:
 	    GamePlayer();
		void start(void);
		~GamePlayer(){}
		
 	private:
		void make_move(int s) override;
 		void select_starter(void) override;
 		void positioning(void) override;
		void positioning_player(void);
 		void positioning_pc(void);
		bool special_insert(std::string first, std::string second);

		
};
#endif
>>>>>>> Stashed changes
