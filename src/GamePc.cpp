// Autore: Andrea Mutti
#include "../include/GamePc.h"

#include <ctime>
#include <cstdlib>

// Costruttore public
GamePc::GamePc(void)
:   Game{"log_pc.txt"}		// richiama il costruttore di Game passando come parametro il file di log
{
    select_starter();		// scelta giocatore inziale
	positioning();			// posizionamento iniziale
}

// Funzione start
void GamePc::start(void){
	std::cout << "\n   Posizionamento navi iniziale." << std::endl;
	print_defence(1);
	print_defence(2);	// dopo il posizionamento navi stampa le griglie
	while(!end(false)){
		increment_turn();
		std::cout << "\n	Turno " << turn() << std::endl;
		make_move(starter());
		make_move((starter()%2)+1);
	}
	if(end(true)){
		std::cout << "\nFine gioco.\n" << std::endl; 
	}
}
// Posizionamento inziziale
void GamePc::positioning(void){
    int pl1 = (starter_);
	int pl2;					// pl1 -> starter, pl2 -> other player
	if(pl1 == 1){
		pl2 = 2;
	}else{
		pl2 = 1;
	}

	int number_c = 1;			// inserimento navi identico a positioning_pc di GamePlayer
	int t = 1;
	int dim = 4;				// crea coordinate random, se funzionano, incrementa il contatore
	while(number_c < 4){
		try{
			Coord punta = UCoord::random_coord();
			Coord coda = UCoord::random_coord(punta, dim);
			Game::add_ship(pl1, punta, coda, t);
			number_c++;
		}catch(std::invalid_argument& e){}
	}
	
	int number_s = 1;
	t = 2;
	dim = 2;
	while(number_s < 4){
		try{
			Coord punta = UCoord::random_coord();
			Coord coda = UCoord::random_coord(punta, dim);
			Game::add_ship(pl1, punta, coda, t);
			number_s++;
		}catch(std::invalid_argument& e){}
	}		
	int number_e = 1;
	t = 3;
	while(number_e < 3){
		try{
			Coord punta = UCoord::random_coord();
			Coord coda = punta;						// una sola per il sottomarino
			Game::add_ship(pl1, punta, coda, t);
			number_e++;
		}catch(std::invalid_argument& e){}
	}
	number_c = 1;
	t = 1;
    dim = 4;
	while(number_c < 4){
		try{
			Coord punta = UCoord::random_coord();
			Coord coda = UCoord::random_coord(punta, dim);
			Game::add_ship(pl2, punta, coda, t);
			number_c++;
		}catch(std::invalid_argument& e){}
	}
	number_s = 1;
	t = 2;
	dim = 2;
	while(number_s < 4){
		try{
			Coord punta = UCoord::random_coord();
			Coord coda = UCoord::random_coord(punta, dim);
			Game::add_ship(pl2, punta, coda, t);
			number_s++;
		}catch(std::invalid_argument& e){}
	}		
	number_e = 1;
	t = 3;	
	while(number_e < 3){
		try{
			Coord punta = UCoord::random_coord();
			Coord coda = punta;
			Game::add_ship(pl2, punta, coda, t);
			number_e++;
		}catch(std::invalid_argument& e){}
	}
	std::cout << "Navi create e inserite correttamente\n" << std::endl;
}
