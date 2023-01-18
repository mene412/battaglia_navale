#include "Game.h"


// Costruttore che istanzia le variabili iniziali e il file di log corretto
Game::Game(std::string log_file)
	: def_grid1_{}, def_grid2_{}, att_grid1_{}, att_grid2_{}, turn_{0}, starter_{0}, log_{log_file}, ship_went_down_{false}
{
	print_info();	// stampa le info iniziali
}

void Game::select_starter(void){	// Seleziona il giocatore che inizia in maniera randomica
	int s = rand()%2+1;
	if(s==1){
		std::cout << "   Inizia il player " << s << std::endl;
	}else if(s==2){
		std::cout << "   Inizia il player " << s << std::endl;
	}
	starter_ = s;
	write_log(s);		// scrive su log il giocatore che inizia
}




// Crea la mossa del giocatore in maniera randomica
void Game::make_move(int s){	// s è il giocatore
	if(end(false)){
		return;					// se è terminato, ritorna
	}
	bool valid = false;			// bool per controllo, se è true sempre, allora la mossa è valida
	Coord def, att;				// coordinate (def, la nave scelta, att la coordinata di attacco)
	while(!valid){
		try{								// tenta una mossa, se non lancia eccezioni allora è valida
			valid = true;
			int pos = select_ship(s);		// seleziono nave in maniera randomica
				
			att = UCoord::random_coord();	// coordinate random per att
			if(s == 1){
				int type = def_grid1_.type_ship(pos);	// tipo di nave (per capire quale azione può fare)
				def = def_grid1_.ship(pos) -> center();	// coordinata della nave scelta (necessaria per il log)
				if(type == 1){				// BATTLESHIP
					fire(s, pos, att); 
				} else if(type == 2) {		// HELPSHIP
					move_ship(s, pos, att);
					heal(s, pos, att);
				} else if(type == 3) {		// EXPL SUBMARINE
					move_ship(s, pos, att);
					search(s, pos, att);
				}
			}
			if(s == 2){
				int type = def_grid2_.type_ship(pos);
				def = def_grid2_.ship(pos) -> center();	
				if(type == 1){				// BATTLESHIP
					fire(s, pos, att); 
				} else if(type == 2) {		// HELPSHIP
					move_ship(s, pos, att);
					heal(s, pos, att);
				} else if(type == 3) {		// EXPL SUBMARINE
					move_ship(s, pos, att);
					search(s, pos, att);
				}
			}
		}catch(std::invalid_argument& e){
			valid  = false;					// se trova eccezioni vuol dire che la mossa non è valida e ne riprova una diversa
		}
	}
	std::cout << "   Player " << s << " --> " << def << " " << att << std::endl;	// scrive a schermo la mossa effettuata
	std::pair<Coord, Coord> coord{def, att}; 
	write_log(coord);								// scrive su log la coppia di coordinate
	
	if(ship_went_down_){							// se una nave è stata abbattuta -> true
		ship_went_down_ = false;					// stampa a schermo che è stata distrutta e quante ne sono rimaste e rimette a false
		if(s == 1){
			std::cout << "   Nave abbattuta del player 2 - rimaste: " << def_grid2_.number_ship() << " navi." << std::endl;
		}else{
			std::cout << "   Nave abbattuta del player 1 - rimaste: " << def_grid1_.number_ship() << " navi." << std::endl;
		}
	}
}

// Funzione per l'aggiunta di una nave 
void Game::add_ship(int player, Coord& p, Coord& c, int type){	// giocatore, coordinate poppa e prua, tipo di nave
	if(player == 1){
		if(type == 1 && def_grid1_.check_position(p, c, 5, -1)){	// a seconda del tipo di nave, controlla che lo spazio sia libero
			def_grid1_.add_ship(p, c, type);						// se libero, aggiunge la nave e scrive su log
			std::pair<Coord, Coord> coord{p, c}; 					// se occupato, lancia un'eccezione, gestita dalle classi derivate
			write_log(coord);
		}else if(type == 2 && def_grid1_.check_position(p, c, 3, -1)){
			def_grid1_.add_ship(p, c, type);
			std::pair<Coord, Coord> coord{p, c}; 
			write_log(coord);
		}else if(type == 3 && def_grid1_.check_position(c)){
			def_grid1_.add_ship(p, c, type);
			std::pair<Coord, Coord> coord{p, c}; 
			write_log(coord);
		}else{
			throw std::invalid_argument("Posizione non valida");
		}
	}else{
		if(type == 1 && def_grid2_.check_position(p, c, 5, -1)){
			def_grid2_.add_ship(p, c, type);							// player 2
			std::pair<Coord, Coord> coord{p, c}; 
			write_log(coord);
		}else if(type == 2 && def_grid2_.check_position(p, c, 3, -1)){
			def_grid2_.add_ship(p, c, type);
			std::pair<Coord, Coord> coord{p, c}; 
			write_log(coord);
		}else if(type == 3 && def_grid2_.check_position(c)){
			def_grid2_.add_ship(p, c, type);
			std::pair<Coord, Coord> coord{p, c}; 
			write_log(coord);
		}else{
			throw std::invalid_argument("Posizione non valida");
		}
	}
}

// Seleziona una nave randomicamente tra quelle a disposizione di un player
int Game::select_ship(int player){
	if(player == 1){
		int ran = rand()%(def_grid1_.number_ship());
		return ran;
	}else{
		int ran = rand()%(def_grid2_.number_ship());
		return ran;
	}
}

// Fa fuoco su una coordinata specificata
void Game::fire(int pl, int pos, Coord& c){
    if(pl == 1){
		for(int i = 0; i<def_grid2_.number_ship(); i++){ 		// scorre le navi nella  defGrid nemica
			for(int j = 0; j<def_grid2_.ship(i)->dim(); j++){	// scorre le coord di ogni nave
				if(def_grid2_.ship(i)->coord().at(j) == c){		// Se trova la nave nella posizione da colpire
					att_grid1_.add_char('x', c);				// stampa nella griglia di attacco una x
					def_grid2_.ship(i) -> hit(c);				// segna nella nave che è stata colpita
					def_grid2_.hit(c);							// segna nella defGrid nemica che è stata colpita
					if(def_grid2_.destroyed(i)){				// controlla se la nave è stat distrutta
						titanic(pl, i);							// se distrutta, la rimuove dalla griglia e modifica ship_went_down->true
						ship_went_down_ = true;
					}
					def_grid2_.reload();						// aggiorna la griglia e ritorna
					return;
				}
			}
		}														// se non trova la nave, segna acqua ("O")
    	att_grid1_.add_char('O', c);
    	return;
	}else{
		for(int i = 0; i<def_grid1_.number_ship(); i++){
			for(int j = 0; j<def_grid1_.ship(i)->dim(); j++){
				if(def_grid1_.ship(i)->coord().at(j) == c){
					att_grid2_.add_char('x', c);				// player 2
					def_grid1_.ship(i) -> hit(c);
					def_grid1_.hit(c);
					if(def_grid1_.destroyed(i)){
						titanic(pl, i);
						ship_went_down_ = true;
					}
					def_grid1_.reload();
					return;
				}
			}
		}
    	att_grid2_.add_char('O', c);
    	return;
	} 
}




void Game::move_ship(int pl, int pos, Coord& c){
	if(pl == 1){									
		int type = def_grid1_.type_ship(pos);							// determino il tipo di nave che devo muovere
		if(type == 2){													// caso nave di supporto
			std::vector<Coord> new_coord;								// vettore di coordinate dove si sposta la nave
		if(def_grid1_.ship(pos)->orizzontal()){							// a seconda della direzione della nave riempie il vettore
				Coord new_c{c.X(), c.Y()-1};
				new_coord.push_back(new_c);
				new_c = Coord{c};
				new_coord.push_back(new_c);		
				new_c = Coord{c.X(), c.Y()+1};
				new_coord.push_back(new_c);
			} else {
				Coord new_c{c.X()-1, c.Y()};
				new_coord.push_back(new_c);
				new_c = Coord{c};
				new_coord.push_back(new_c);
				new_c = Coord{c.X()+1, c.Y()};
				new_coord.push_back(new_c);
			}
			if(def_grid1_.check_position(new_coord, pos)){						// controlla se la posizione è libera
				HelpShip* s = dynamic_cast<HelpShip*>(def_grid1_.ship(pos));	// se si, esgue un cast dinamico per
				s -> move(c);													// sfruttare la funzione move di HelpShip
				def_grid1_.reload();											// aggiorna la griglia
				return;
			}else{
				throw std::invalid_argument("Coordinata non valida");
			}
		}
		// caso: SUBMARINE
		else if(type == 3){													// caso submarine
			if(def_grid1_.check_position(c)){								// controlla se la cella è libera
				ExplorationSubmarine* s = dynamic_cast<ExplorationSubmarine*>(def_grid1_.ship(pos));
				s -> move(c);												// cast dinamico e move di ExplorationSubmarine
				def_grid1_.reload();										// aggiorna la griglia
				return;
			}else{
				throw std::invalid_argument("Coordinata non valida");		// lancio di eccezioni gestite da make_move
			}
		}else{
			throw std::invalid_argument("Coordinata non valida");
		}
	}else{
		int type = def_grid2_.type_ship(pos);
		if(type == 2){
			// Creo il vettore di coord dove andrà la nave
			std::vector<Coord> new_coord;
			if(def_grid2_.ship(pos)->orizzontal()){
				Coord new_c{c.X(), c.Y()-1};
				new_coord.push_back(new_c);							// player 2
				new_c = Coord{c};
				new_coord.push_back(new_c);		
				new_c = Coord{c.X(), c.Y()+1};
				new_coord.push_back(new_c);
			} else {
				Coord new_c{c.X()-1, c.Y()};
				new_coord.push_back(new_c);
				new_c = Coord{c};
				new_coord.push_back(new_c);
				new_c = Coord{c.X()+1, c.Y()};
				new_coord.push_back(new_c);
			}
			if(def_grid2_.check_position(new_coord, pos)){
				HelpShip* s = dynamic_cast<HelpShip*>(def_grid2_.ship(pos));
				s -> move(c);
				def_grid2_.reload();
				// Ridisegniamo la nave sulla griglia
				return;
			}else{
				throw std::invalid_argument("Mossa non valida");
			}
		}else if(type == 3){
			if(def_grid2_.check_position(c)){
				ExplorationSubmarine* s = dynamic_cast<ExplorationSubmarine*>(def_grid2_.ship(pos));
				s -> move(c);
				def_grid2_.reload();
				// Ridisegniamo la nave sulla griglia
				return;
			}else{
				throw std::invalid_argument("Mossa non valida");
			}
		}else{
			throw std::invalid_argument("Mossa non valida");
		}
	}
}


// Cura delle navi
void Game::heal(int pl, int pos, Coord& c){					
	std::vector<Coord> coord_heal;					// vettore di coordinate da curare
	for(int i = 0; i<3; i++){						// riempito di una casella 3x3
		try{
			Coord cord{c.X()-1, c.Y()-1+i};
			coord_heal.push_back(cord);
		}catch(std::invalid_argument& e){}			// se una coordinata non può esister (fuori dal bordo), la ignora
	}
	for(int i = 0; i<3; i++){
		try{
			Coord cord{c.X(), c.Y()-1+i};
			coord_heal.push_back(cord);
		}catch(std::invalid_argument& e){}
	}
	for(int i = 0; i<3; i++){
		try{
			Coord cord{c.X()+1, c.Y()-1+i};
			coord_heal.push_back(cord);
		}catch(std::invalid_argument& e){}
	}
	if(pl == 1){
		for(int i = 0; i<coord_heal.size(); i++){										// scorre le coordinate 3x3
			for(int k = 0; k<def_grid1_.number_ship(); k++){							// scorre il numero di navi
				if(k!=pos){																// se la nave non è se stessa
					for(int j = 0; j<def_grid1_.ship(k)->coord().size(); j++){			// scorre le coordinate della nave
						if(!def_grid1_.ship(k)->healed()){								// se non è curata
							if(def_grid1_.ship(k)->coord().at(j) == coord_heal.at(i)){	// e se una coordinata 3x3 è una coordinata della nave
								def_grid1_.ship(k) -> heal();							// la cura
							}
						}
					}
				}
			}
		}
		def_grid1_.reload();									// ricarica la griglia
	}else{
		for(int i = 0; i<coord_heal.size(); i++){
			for(int k = 0; k<def_grid2_.number_ship(); k++){
				if(k!=pos){
					for(int j = 0; j<def_grid2_.ship(k)->coord().size(); j++){				// player 2
						if(!def_grid2_.ship(k)->healed()){
							if(def_grid2_.ship(k)->coord().at(j) == coord_heal.at(i)){
								def_grid2_.ship(k) -> heal();
							}
						}
					}
				}
			}
		}
		def_grid2_.reload();
	}
}

// Search del sottomarino - radar
void Game::search(int pl, int pos, Coord& c) {
    if(pl == 1){													// crea il vettore di coordinate 5x5
		std::vector<Coord> coord;
		for(int i = 0; i<5; i++){									// se una coordinata non può esistere (bordo), la ignora
			try{
				Coord temp{c.X()-2, c.Y()-2+i};
				coord.push_back(temp);
			}catch(std::invalid_argument& e){}
		}
		for(int i = 0; i<5; i++){
			try{
				Coord temp{c.X()-1, c.Y()-2+i};
				coord.push_back(temp);
			}catch(std::invalid_argument& e){}
		}
		for(int i = 0; i<5; i++){
			try{
				Coord temp{c.X(), c.Y()-2+i};
				coord.push_back(temp);
			}catch(std::invalid_argument& e){}
		}
		for(int i = 0; i<5; i++){
			try{
				Coord temp{c.X()+1, c.Y()-2+i};
				coord.push_back(temp);
			}catch(std::invalid_argument& e){}
		}
		for(int i = 0; i<5; i++){
			try{
				Coord temp{c.X()+2, c.Y()-2+i};
				coord.push_back(temp);
			}catch(std::invalid_argument& e){}
		}

		for(int i = 0; i<coord.size(); i++){										// scorre le coordinate 5x5
			try{
				for(int j = 0; j < def_grid2_.number_ship(); j++){					// scorre le navi dell'avversario
					for(int k = 0; k < def_grid2_.ship(j)->coord().size(); k++){	// scorre le coordinate di ogni nave
						if(coord.at(i) == def_grid2_.ship(j) -> coord().at(k)){		// se una nave ha una coordinata nel 5x5
							att_grid1_.add_char('Y', coord.at(i));					// segna una Y nel punto corrispondente
						}
					}
				}
			}catch(std::invalid_argument& e){}
		}
	}else{
		std::vector<Coord> coord;
		for(int i = 0; i<5; i++){
			try{																		// player 2
				Coord temp{c.X()-2, c.Y()-2+i};
				coord.push_back(temp);
			}catch(std::invalid_argument& e){}
		}
		for(int i = 0; i<5; i++){
			try{
				Coord temp{c.X()-1, c.Y()-2+i};
				coord.push_back(temp);
			}catch(std::invalid_argument& e){}
		}
		for(int i = 0; i<5; i++){
			try{
				Coord temp{c.X(), c.Y()-2+i};
				coord.push_back(temp);
			}catch(std::invalid_argument& e){}
		}
		for(int i = 0; i<5; i++){
			try{
				Coord temp{c.X()+1, c.Y()-2+i};
				coord.push_back(temp);
			}catch(std::invalid_argument& e){}
		}
		for(int i = 0; i<5; i++){
			try{
				Coord temp{c.X()+2, c.Y()-2+i};
				coord.push_back(temp);
			}catch(std::invalid_argument& e){}
		}

		for(int i = 0; i<coord.size(); i++){
			try{
				for(int j = 0; j < def_grid1_.number_ship(); j++){
					for(int k = 0; k < def_grid1_.ship(j)->coord().size(); k++){
						if(coord.at(i) == def_grid1_.ship(j) -> coord().at(k)){
							att_grid2_.add_char('Y', coord.at(i));
						}
					}
				}
			}catch(std::invalid_argument& e){}
		}
	}
}


// Scrittura su file di log del player iniziale
void Game::write_log(int player){
	log_ << std::to_string(player);
}

// Scrittura su file di log delle coppie di coordinate
void Game::write_log(std::pair<Coord, Coord>& x){
	log_ << "\n" << x.first << " " << x.second;
}

// Controlla la fine della partita, se over = true stampa a schermo chi ha vinto
bool Game::end(bool over){
	if(turn_>=MAX_TURNS){
		if(over){
			std::cout << "\n|-----------|\n";
			std::cout << "| Pareggio! |";
			std::cout << "\n|-----------|\n" << std::endl;
		}
		return true;
	}
	if(def_grid1_.number_ship()==0){
		if(over){
			std::cout << "\n|--------------------|\n";
			std::cout << "| Player 2 ha vinto! |";
			std::cout << "\n|--------------------|\n" << std::endl;
		}
		return true;	
	}
	if(def_grid2_.number_ship()==0){		
		if(over){
			std::cout << "\n|--------------------|\n";
			std::cout << "| Player 1 ha vinto! |";
			std::cout << "\n|--------------------|\n" << std::endl;
		}
		return true;
	}
	return false;
}

// Incrementa il turno a meno che non si abbia raggiunto il numero massimo di turni
void Game::increment_turn(void){	
	if(turn_ == MAX_TURNS){
		return;
	}
	turn_++;
}

// Stampa la griglia di difsa
void Game::print_defence(int pl){
	if(pl == 1){
		def_grid1_.reload();
		std::cout << "Player " << pl << " - " << def_grid1_;
	}else{
		def_grid2_.reload();
		std::cout << "Player " << pl << " - " << def_grid2_;
	}
}

// Stampa la griglia di attacco
void Game::print_attack(int pl){
	if(pl == 1){
		std::cout << "Player " << pl << " - " << att_grid1_;
	}else{
		std::cout << "Player " << pl << " - " << att_grid2_;
	}
}

// Nave affondata
void Game::titanic(int pl, int pos){
    if(pl == 1){
		for(int i = 0; i<def_grid2_.ship(pos)->dim(); i++){					// scorre le navi
			att_grid1_.add_char('X', def_grid2_.ship(pos)->coord().at(i));	// quando trova la nave, mette le X sulle posizioni
		}																	
		def_grid2_.remove_ship(pos);										// rimuove la nave
		return;
	}else{
		for(int i = 0; i<def_grid1_.ship(pos)->dim(); i++){
			att_grid2_.add_char('X', def_grid1_.ship(pos)->coord().at(i));
		}
		def_grid1_.remove_ship(pos);
		return;
	}
}

// Stampa informazioni iniziali
void Game::print_info(void){												// tanti cout ma solo per praticità visiva
	std::cout << "- - - - - - - - - - - - - - - - - - - - -" << std::endl; 
	std::cout << "* * * I N I Z I A   I L   G I O C O * * *" << std::endl;
	std::cout << "- - - - - - - - - - - - - - - - - - - - -\n" << std::endl; 
	std::cout << "\nNella partita di battaglia navale pc v pc vengono mostrate solamente le mosse di ogni giocatore e i posizionamenti iniziali." << std::endl;
	std::cout << "\nNel caso di partita player v pc, per prima cosa dovrai posizionare le navi.";
	std::cout << "\nDovrai inserire 3 corazzate lunghe 5, 3 navi supporto lunghe 3 e due sottomarini di lunghezza 1.";
	std::cout << "\nPer inserirle devi scrivere le coordinate in formato AX (A -> lettera riga, X -> numero colonna).";
	std::cout << "\nInserisci le due coordinate di poppa e prua della nave. Successivamente dovrai eseguire una mossa.";
	std::cout << "\nViene definita dalla coordinata centrale della nave che vuoi utilizzare e la coordinata del punto (AX BY)";
	std::cout << "\n\nPuoi utilizzare dei caratteri speciali che sono:";
	std::cout << "\n XX XX -> stampa le griglie di attacco e difesa";
	std::cout << "\n AA AA -> rimuove dalla griglia di attacco i rilevamenti radar del sottomarino";
	std::cout << "\n BB BB -> rimuove dalla griglia di attacco i colpi andati a segno dato che le navi possono spostarsi";
	std::cout << "\n CC CC -> rimuove dalla griglia di attacco i colpi non andati a segno (acqua)";
	std::cout << "\n\nBuona partita!\n\n";
}


//NAMESPACE UTIL

// Trasforma una stringa in maiuscolo
void util::to_upper(std::string& x){	 // stringa come riferimento, viene modificata direttamente
	for(int i = 0; i<x.size(); i++){
		x.at(i) = std::toupper(x.at(i));		// sfrutta std::toupper() e modidica ogni singolo carattere
	}
}
