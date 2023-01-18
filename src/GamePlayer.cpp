#include "../include/GamePlayer.h"


#include <ctime>
#include <cstdlib>

GamePlayer::GamePlayer(void)
	: Game{}
{
	select_starter();
	positioning();
}

void GamePlayer::select_starter(void) {
	int s = rand()%2+1;
	if(s==1){
		std::cout << "   Inizia il player " << s << " (You)\n" << std::endl;
	}else if(s==2){
		std::cout << "   Inizia il player " << s << " (Pc)\n" << std::endl;
	}
	starter_ = s;
	write_log(s);
}

void GamePlayer::positioning(void){
 	if(starter_ == 0){
 		throw std::invalid_argument("Errore");
 	}
 	if(starter_==1){
		std::cout << "   E' il tuo turno di inserimento navi." << std::endl;
 		positioning_player();
 		positioning_pc();
 	}else{
 		positioning_pc();
		std::cout << "   E' il tuo turno di inserimento navi." << std::endl;
 		positioning_player();
 	}
 	std::cout << "\n   Posizionamento navi terminato.\n" << std::endl;
}

void GamePlayer::positioning_player(void){
	int const pl = 1;
	int number_c = 1;
	std::string punta;
	std::string coda;
	int t = 1;
	while(number_c < 4){
		try{
			std::cout << "   Inserire le coordinate della nave corazzata " << number_c << " -> ";
			std::cin >> punta;
			util::to_upper(punta);
			std::cin >> coda;
			util::to_upper(coda);
			Coord p{UCoord::from_string_to_coord(punta)};
			Coord c{UCoord::from_string_to_coord(coda)};
			int dim = 4;
			check_dim(p, c, dim);
			Game::add_ship(pl, p, c, t);
			number_c++;
		}catch(std::invalid_argument& e){
			std::cout << "   Coordinate non valide, reinserire." << std::endl;
		}
	}
	
	int number_s = 1;
	t = 2;
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
			check_dim(p, c, dim);
			Game::add_ship(pl, p, c, t);
			number_s++;
		}catch(std::invalid_argument& e){
			std::cout << "   Coordinate non valide, reinserire." << std::endl;
		}
	}		
	
	int number_e = 1;
	t = 3;
	while(number_e < 3){
		try{
			std::cout << "   Inserire la coordinata del sottomarino di esplorazione " << number_e << " -> ";
			std::cin >> punta;
			util::to_upper(punta);
			Coord p{UCoord::from_string_to_coord(punta)};
			Coord c{UCoord::from_string_to_coord(punta)};
			Game::add_ship(pl, p, c, t);
			number_e++;
		}catch(std::invalid_argument& e){
			std::cout << "   Coordinate non valide, reinserire." << std::endl;
		}
	}

}


void GamePlayer::make_move(int s){
    // controlla che la partita non sia finita:
	// - player senza navi
	// - limite turni raggiunto
	if(end(false)){
		return;
	}
	
	bool valid = false;
	Coord def, att;
	while(!valid){
		try{
			valid = true;
			if(s == 1){
				std::string first, second;
				std::cout << "\n   Inserisci le coordinate della tua prossima mossa --> ";
				std::cin >> first >> second;
				util::to_upper(first);
				util::to_upper(second);
				if(!special_insert(first, second)){
					try{
						def = UCoord::from_string_to_coord(first);
						att = UCoord::from_string_to_coord(second);
						int pos = def_grid1_.find_ship(def);
						// Definisco il tipo di nave per l'azione da fare
						int type = def_grid1_.type_ship(pos);
						if(type == 1){					// BATTLESHIP
							fire(s, pos, att); 
						} else if(type == 2) {			// HELPSHIP
							move_ship(s, pos, att);
							heal(s, pos, att);
						} else if(type == 3) {			// EXPL SUBMARINE
							move_ship(s, pos, att);
							search(s, pos, att);
						}
					}catch(std::invalid_argument& e){
						std::cout << "   Mossa non valida" << std::endl;
						throw std::invalid_argument("Errore");
					}
				}else{
					valid = false;
					
				}				
			}
			if(s == 2){
				att = UCoord::random_coord();
				int pos = rand()%def_grid2_.number_ship();				
				int type = def_grid2_.type_ship(pos);
				def = def_grid2_.ship(pos) -> center();
				if(type == 1){					// BATTLESHIP
					fire(s, pos, att); 
				} else if(type == 2) {			// HELPSHIP
					move_ship(s, pos, att);
					heal(s, pos, att);
				} else if(type == 3) {			// EXPL SUBMARINE
					move_ship(s, pos, att);
					search(s, pos, att);
				}
				std::cout << "   Player " << s << " --> " << def << " " << att << std::endl;
			}
		}catch(std::invalid_argument& e){
			valid  = false;
		}
	}
	if(ship_went_down_){
		ship_went_down_ = false;
		if(s == 1){
			std::cout << "   Nave abbattuta del player 2 - rimaste: " << def_grid2_.number_ship() << " navi." << std::endl;
		}else{
			std::cout << "   Nave abbattuta del player 1 - rimaste: " << def_grid1_.number_ship() << " navi." << std::endl;
		}
	}
	std::pair<Coord, Coord> coord{def, att}; 
	write_log(coord);
	if(end(false)){
		return;
	}
}


void GamePlayer::positioning_pc(void){
	int const pl = 2;
	int number_c = 1;
	int t = 1;
	int dim = 4;
	while(number_c < 4){
		try{
			Coord punta = UCoord::random_coord();
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

bool GamePlayer::special_insert(std::string first, std::string second){
	if(first == "XX"){
		if(second == "XX"){
			print_attack(1);
			print_defence(1);
			return true;
		}else{
			throw std::invalid_argument("Errore");
		}
	}else if(first == "AA"){
		if(second == "AA"){
			att_grid1_.remove_detections();
			return true;
		}else{
			throw std::invalid_argument("Errore");
		}
	}else if(first == "BB"){
		if(second == "BB"){
			att_grid1_.remove_hit();
			return true;
		}else{
			throw std::invalid_argument("Errore");
		}
	}else if(first == "CC"){
		if(second == "CC"){
			att_grid1_.remove_water();
			return true;
		}else{
			throw std::invalid_argument("Errore");
		}
	}
	return false;
}	


void GamePlayer::start(){
	std::cout << "   Il tuo posizionamento iniziale" << std::endl;
	print_defence(1);
	while(!end(false)){
		increment_turn();
		std::cout << "\n	Turno " << turn() << std::endl;
		make_move(starter());
		make_move((starter()%2)+1);
	}
	if(end(true)){
		std::cout << "\nChiusura programma...\n" << std::endl; 
	}
}



