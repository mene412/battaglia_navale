// Autore: Andrea Mutti

#ifndef GamePc_h
#define GamePc_h

#include "Game.h"

class GamePc : public Game{
	public:
		GamePc(void);
		void start(void);
	protected:
		void positioning(void) override;
		
};
#endif
