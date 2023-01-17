// Autore: Andrea Mutti

#ifndef GAME_PC_H
#define GAME_PC_H

#include "Game.h"

class GamePc : public Game{
	public:
		GamePc(void);
		void start(void);
		~GamePc(){}

	private:
		void positioning(void) override;
		
};
#endif
