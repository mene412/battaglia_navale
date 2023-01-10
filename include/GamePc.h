#ifndef "GamePc_h"
#define GamePc_h"

#include "Game.h"

class GamePc : public Game{
	public:
		GamePc(void);
		void positioning(void);
		bool end_max_turn(void) const;
	private:
		static const int MAX_TURNS = 100;
#endif
