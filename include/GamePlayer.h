// Autore: Andrea Mutti

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "Game.h"

class GamePlayer: public Game{		// classe derivata dalla classe Game
 	public:
		// Costruttore public
 	    GamePlayer(void);

		// Funzione di inizio gioco
		void start(void);			// gestisce l'intera partita, toglie il più possibile codice al main, ma gestisce il game totalmente
		
		// Distruttore (automaticamente virtual)
		~GamePlayer(){}
		
 	private:
		// Funzioni membro di override
		void select_starter(void) override;
 		void positioning(void) override;	// override funzione virtuale pura
		void make_move(int s) override;

		// Funzioni membro private
		void positioning_player(void);		// posizionamento navi
 		void positioning_pc(void);

		bool special_insert(std::string first, std::string second);		// funzione per l'inserimento di caratteri speciali come XX XX
		void check_dim(Coord& a, Coord& b, int dim);					// controlla se un player rispetta la lunghezza della nave
};
#endif
