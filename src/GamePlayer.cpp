#include "GamePlayer.h"

#include <cmath>

// Costruttore
GamePlayer::GamePlayer(void)
	: Game{"log_player.txt"}		// richiama il costruttore di Game passando come parametro il file di log player v pc
{
	select_starter();				// seleziona chi inizia
	positioning();					// posiziona le navi
}

// Funzione start - gestisce tutto il gioco fino alla chiusura
void GamePlayer::start(){
	std::cout << "\n   Il tuo posizionamento iniziale" << std::endl;	// stampa la griglia con le navi posizionate 
	print_defence(1);
	while(!end(false)){
		increment_turn();									// incrementa e stampa il turno corrente
		std::cout << "\n	Turno " << turn() << std::endl;
		make_move(starter());								// esegue le mosse, prima starter, poi l'altro player
		make_move((starter()%2)+1);
	}
	if(end(true)){
		std::cout << "\nFine gioco.yy\n" << std::endl; 
	}
}


// Seleziona chi inizia randomicamente
void GamePlayer::select_starter(void) {				// leggermente modificato rispetto a Game solo per l'output
	int s = rand()%2+1;
	if(s==1){
		std::cout << "   Inizia il player " << s << " (You)\n" << std::endl;
	}else if(s==2){
		std::cout << "   Inizia il player " << s << " (Pc)\n" << std::endl;
	}
	starter_ = s;
	write_log(s);
}

// Posiziona le navi
void GamePlayer::positioning(void){
 	if(starter_ == 0){
 		throw std::invalid_argument("Errore");					// chiama positionig_player o pc a seconda di chi deve effettuare prima il posizionamento
 	}
 	if(starter_==1){
		std::cout << "\n   E' il tuo turno di inserimento navi." << std::endl;
 		positioning_player();					
 		positioning_pc();
 	}else{
 		positioning_pc();
		std::cout << "\n   E' il tuo turno di inserimento navi." << std::endl;
 		positioning_player();
 	}
 	std::cout << "\n   Posizionamento navi terminato.\n" << std::endl;
}

// Esegue la mossa in base al player
void GamePlayer::make_move(int s){
	if(end(false)){
		return;					// return se partita finita
	}
	
	bool valid = false;			// variabile booleana d'appoggio
	Coord def, att;				// coordinate della mossa
	while(!valid){
		try{
			valid = true;
			if(s == 1){									// caso player umano
				std::string first, second;
				std::cout << "\n   Inserisci le coordinate della tua prossima mossa --> ";
				std::cin >> first >> second;
				util::to_upper(first);					// inserisce le coordinate string e le rende maiuscole
				util::to_upper(second);						
				if(!special_insert(first, second)){		// nel caso di inserimento speciale, non verifica il resto
					try{
						def = UCoord::from_string_to_coord(first);			// da string a Coord, se non valido, UCoord lancia eccezione
						att = UCoord::from_string_to_coord(second);
						int pos = def_grid1_.find_ship(def);				// posizione della nave nel vettore di navi (eccezione se non presente)
						int type = def_grid1_.type_ship(pos);				// typo di nave scelta
						if(type == 1){					// BATTLESHIP
							fire(s, pos, att); 
						} else if(type == 2) {			// HELPSHIP
							move_ship(s, pos, att);
							heal(s, pos, att);
						} else if(type == 3) {			// EXPL SUBMARINE
							move_ship(s, pos, att);
							search(s, pos, att);
						}
					}catch(std::invalid_argument& e){						// se la mossa non è valida avvisa e rilancia eccezione gestita a monte
						std::cout << "   Mossa non valida" << std::endl;
						throw std::invalid_argument("Mossa non valida");
					}
				}else{
					valid = false;			// valid = false cosi da ripetere con un altro comando
				}				
			}
			if(s == 2){
				att = UCoord::random_coord();					// caso player pc - mossa randomica
				int pos = rand()%def_grid2_.number_ship();		// posizione della nave randomica
				int type = def_grid2_.type_ship(pos);			// tipo della nave
				def = def_grid2_.ship(pos) -> center();			// coordinata centrale della nave scelta, utile per il log
				if(type == 1){					// BATTLESHIP
					fire(s, pos, att); 
				} else if(type == 2) {			// HELPSHIP
					move_ship(s, pos, att);
					heal(s, pos, att);
				} else if(type == 3) {			// EXPL SUBMARINE
					move_ship(s, pos, att);
					search(s, pos, att);
				}
				std::cout << "\n   Player 2 -> mossa eseguita." << std::endl;	// mossa eseguita (non specifica le coordinate per non agevolare il player)
			}
		}catch(std::invalid_argument& e){
			valid  = false;								// se qualcosa è andato storto (mossa non valida), ripete
		}
	}
	if(ship_went_down_){
		ship_went_down_ = false;						// se la nave è stat abbattuta lo scrive in output
		if(s == 1){
			std::cout << "   Nave abbattuta del player 2 - rimaste: " << def_grid2_.number_ship() << " navi." << std::endl;
		}else{
			std::cout << "   Nave abbattuta del player 1 - rimaste: " << def_grid1_.number_ship() << " navi." << std::endl;
		}
	}
	std::pair<Coord, Coord> coord{def, att}; 			// scritura su log
	write_log(coord);
}

// Posiziona le navi del giocatore
void GamePlayer::positioning_player(void){
	int const pl = 1;							// numero giocatore
	int number_c = 1;							// numero di battleships
	std::string punta;							// stringhe di coordinate da ricevere in ingresso
	std::string coda;
	int t = 1;									// tipo di nave
	while(number_c < 4){
		try{
			std::cout << "   Inserire le coordinate della nave corazzata " << number_c << " -> ";
			std::cin >> punta;
			util::to_upper(punta);
			std::cin >> coda;
			util::to_upper(coda);
			Coord p{UCoord::from_string_to_coord(punta)};		// da string a Coord, se non va, eccezione lanciata
			Coord c{UCoord::from_string_to_coord(coda)};
			int dim = 4;										// differenza tra poppa e prua
			check_dim(p, c, dim);								// controlla la dimensione
			Game::add_ship(pl, p, c, t);						// aggiunge la nave		
			number_c++;											// se tutto andato a buon fine, incrementa il numero
		}catch(std::invalid_argument& e){
			std::cout << "   Coordinate non valide, reinserire." << std::endl;
		}
	}
	
	int number_s = 1;
	t = 2;					// tipo helpship
	while(number_s < 4){
		try{
			std::cout << "   Inserire le coordinate della nave di supporto " << number_s << " -> ";
			std::cin >> punta;
			util::to_upper(punta);
			std::cin >> coda;
			util::to_upper(coda);			
			Coord p{UCoord::from_string_to_coord(punta)};
			Coord c{UCoord::from_string_to_coord(coda)};
			int dim = 2;
			check_dim(p, c, dim);			// controlla la dimensione
			Game::add_ship(pl, p, c, t);
			number_s++;
		}catch(std::invalid_argument& e){
			std::cout << "   Coordinate non valide, reinserire." << std::endl;
		}
	}		
	
	int number_e = 1;
	t = 3;			// tipo submarine
	while(number_e < 3){
		try{
			std::cout << "   Inserire la coordinata del sottomarino di esplorazione " << number_e << " -> ";
			std::cin >> punta;
			util::to_upper(punta);							// per il sottomarino fa inserire una sola coordinata
			Coord p{UCoord::from_string_to_coord(punta)};
			Coord c{UCoord::from_string_to_coord(punta)};
			Game::add_ship(pl, p, c, t);
			number_e++;
		}catch(std::invalid_argument& e){
			std::cout << "   Coordinate non valide, reinserire." << std::endl;
		}
	}

}

// Posizionamento navi pc
void GamePlayer::positioning_pc(void){
	int const pl = 2;
	int number_c = 1;	
	int t = 1;
	int dim = 4;
	while(number_c < 4){
		try{
			Coord punta = UCoord::random_coord();				// funzionamento pressoché uguale a sopra, ma con coordinate randomcihe
			Coord coda = UCoord::random_coord(punta, dim);
			Game::add_ship(pl, punta, coda, t);
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
			Game::add_ship(pl, punta, coda, t);
			number_s++;
		}catch(std::invalid_argument& e){}
	}		
	
	int number_e = 1;
	t = 3;
	while(number_e < 3){
		try{
			Coord punta = UCoord::random_coord();
			Coord coda = punta;
			Game::add_ship(pl, punta, coda, t);
			number_e++;
		}catch(std::invalid_argument& e){}
	}
}

// Funzione per la verifica dei caratteri speciali utilizzabili
bool GamePlayer::special_insert(std::string first, std::string second){
	if(first == "XX"){
		if(second == "XX"){				// se un carattere viene riconosciuto, esegue e ritorna true
			print_attack(1);			// stampa le navi
			print_defence(1);
			return true;
		}else{
			throw std::invalid_argument("Comando non valido");	 // se il carattere non è valido a metà lancia eccezione
		}
	}else if(first == "AA"){
		if(second == "AA"){
			att_grid1_.remove_detections();			// rimuove gli avvistamenti radar
			return true;
		}else{
			throw std::invalid_argument("Comando non valido");
		}
	}else if(first == "BB"){
		if(second == "BB"){
			att_grid1_.remove_hit();				// rimuove i colpi
			return true;
		}else{
			throw std::invalid_argument("Comando non valido");
		}
	}else if(first == "CC"){
		if(second == "CC"){
			att_grid1_.remove_water();
			return true;							// rimuove i colpi non andati a segno
		}else{
			throw std::invalid_argument("Comando non valido");
		}
	}
	return false;								// se non è un carattere speciale ritorna false
}	

// Controlla la dimensione di una nave
void GamePlayer::check_dim(Coord& a, Coord&b, int dim){
	if(a.X()!=b.X()){
		if(a.Y()!=b.Y()){								// Se una nave non è della dimensione corretta, lancia un'eccezione
			throw std::invalid_argument("Dimensione errata");
		}else{
			if(abs(a.X()-b.X())!=dim){					// sfrutto il valore assoluto per la differenza
				throw std::invalid_argument("Dimensione errata");
			}
		}
	}else{
		if(a.Y()==b.Y()){
			throw std::invalid_argument("Dimensione errata");
		}else{
			if(abs(a.Y()-b.Y())!=dim){
				throw std::invalid_argument("Dimensione errata");
			}
		}
	}
}
