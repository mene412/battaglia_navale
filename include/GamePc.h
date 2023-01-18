// Autore: Andrea Mutti

#ifndef GAME_PC_H
#define GAME_PC_H

#include "Game.h"

class GamePc : public Game{			// classe derivata da Game
	public:
		// Costruttore public
		GamePc(void);

		// Funzione di inizio gioco
		void start(void);			// gestisce l'intera partita, toglie il più possibile codice al main, ma gestisce il game totalmente
		
		// Distruttore (automaticamente virtual)
		~GamePc(){}

	private:
		// Override obbligato della funzione virtuale pura definita nella classe Game, private per evitare posizionamenti non voluti
		void positioning(void) override;
		
};
#endif
