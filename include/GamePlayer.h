// Autore: Andrea Mutti

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "Game.h"

// Classe derivata dalla classe Game, gestisce la partita player umano v pc
// Eredita i metodi public e protected di Game
class GamePlayer: public Game{		
 	public:
		// Costruttore public, eredita il costruttore di Game
 	    GamePlayer(void);

		// Funzione di inizio gioco che gestisce l'intera partita
		// Quando la funzione termina, vuol dire che è terminato il gioco
		void start(void);			
		
		// Distruttore (automaticamente virtual)
		~GamePlayer(){}
		
 	private:
		// Funzione membro di override, seleziona il giocatore iniziale randomicamente
		void select_starter(void) override;
		// Override di funzione virtuale pura, posiziona le navi iniziali
 		void positioning(void) override;
		// Funzione membro di override, permette di eseguire le mosse
		void make_move(int s) override;

		// Funzioni membro private
		// Posizionamento navi da parte del player umano
		void positioning_player(void);		
		// Posizionamento navi da parte del player pc
 		void positioning_pc(void);

		// Funzione per l'inserimento di caratteri speciali
		// XX XX
		// AA AA
		// BB BB
		// CC CC
		bool special_insert(std::string first, std::string second);	
		// Controlla se un player rispetta la lunghezza della nave	
		void check_dim(Coord& a, Coord& b, int dim);					
};

#endif	// GAME_PLAYER_H
