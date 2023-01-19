// Autore: Andrea Mutti

#ifndef GAME_PC_H
#define GAME_PC_H

#include "Game.h"

// Classe per la gestione di una partita di battaglia navale tra due computer
// La classe deriva i metodi e i campi d'esemplare public e protected della classe Game
class GamePc : public Game{			
	public:
		// Costruttore public, non riceve parametri di ingresso, sfrutta il costruttore della classe da cui deriva
		GamePc(void);

		// Funzione di inizio gioco, gestisce l'intera partita dall'inizio alla fine
		void start(void);			
		
		// Distruttore virtual, automaticamente richiama il costruttore di Game
		~GamePc(){}

	private:
		// Override obbligato della funzione virtuale pura definita nella classe Game, private per evitare posizionamenti non voluti
		void positioning(void) override;
};

#endif // GAME_PC_H
