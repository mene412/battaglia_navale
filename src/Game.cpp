#include "../include/Game.h"

#include <ctime>
#include <cstdlib>
#include <cmath>

Game::Game(void)
	: def_grid1_{}, def_grid2_{}, att_grid1_{}, att_grid2_{}, turn_{0}, starter_{0}, log{"../log.txt"}
{
	std::cout << "Inizio gioco.\n" << std::endl; 
}

void Game::select_starter(void){
	int s = rand()%2+1;
	if(s==1){
		std::cout << "Inizia il player " << s << std::endl;
	}else if(s==2){
		std::cout << "Inizia il player " << s << std::endl;
	}
	starter_ = s;
	write_log(std::to_string(s));
}

void Game::add_ship(int player, Coord& p, Coord& c, int type){
	if(player == 1){
		if(type == 1 && def_grid1_.check_position(p, c, 5)){
			def_grid1_.add_ship(p, c, type);
			std::pair<Coord, Coord> coord{p, c}; 
			write_log(coord);
		}else if(type == 2 && def_grid1_.check_position(p, c, 3)){
			def_grid1_.add_ship(p, c, type);
			std::pair<Coord, Coord> coord{p, c}; 
			write_log(coord);
		}else if(type == 3 && def_grid1_.check_position(p, c, 1)){
			def_grid1_.add_ship(p, c, type);
			std::pair<Coord, Coord> coord{p, c}; 
			write_log(coord);
		}else{
			throw std::invalid_argument("Non puoi aggiungere una nave qua - linea 40");
		}
	}else{
		if(type == 1 && def_grid2_.check_position(p, c, 5)){
			def_grid2_.add_ship(p, c, type);
			std::pair<Coord, Coord> coord{p, c}; 
			write_log(coord);
		}else if(type == 2 && def_grid2_.check_position(p, c, 3)){
			def_grid2_.add_ship(p, c, type);
			std::pair<Coord, Coord> coord{p, c}; 
			write_log(coord);
		}else if(type == 3 && def_grid2_.check_position(p, c, 1)){
			def_grid2_.add_ship(p, c, type);
			std::pair<Coord, Coord> coord{p, c}; 
			write_log(coord);
		}else{
			throw std::invalid_argument("Non puoi aggiungere una nave qua - linea 56");
		}
	}
}

void Game::increment_turn(void){
	if(turn_ == MAX_TURNS){
		return;
	}
	turn_++;
}

void Game::make_move(int s){
	// controlla che la partita non sia finita:
	// - player senza navi
	// - limite turni raggiunto
	if(end(false)){
		return;
	}
	bool valid = false;
	Coord def, att;
	// TEST
	std::cout << "\n* * Turno " << turn() << "\tPlayer " << s <<std::endl;	
	// FINE TEST
	while(!valid){
		try{
			valid = true;
			// Seleziono la nave
			int pos = select_ship(s);
			// Seleziono delle coordinate random dove attaccare
			att = UCoord::random_coord();
			// Determino il numero del player per modificare la griglia giusta
			if(s == 1){
				// Definisco il tipo di nave per l'azione da fare
				int type = def_grid1_.type_ship(pos);
				std::cout << "\tTipo:" << type;
				if(type == 1){					// BATTLESHIP
					fire(s, pos, att); 
				} else if(type == 2) {	
					std::cout << "\n\nOLEEEE\n\n" << std::endl;		// HELPSHIP
					// mofifica la ship
					move_ship(s, pos, att);
					heal(s, pos, att);
				} else if(type == 3) {			// EXPL SUBMARINE
					move_ship(s, pos, att);
					search(s, pos, att);
				}
				// TEST
				std::cout << "\nScelta ed eseguita azione con nave in di tipo " << type << " in posizione " << pos << std::endl;	
				// FINE TEST
				// Scrive la casella di arrivo della nave
				def = def_grid1_.ship(pos) -> center();
			}
			if(s == 2){
				int type = def_grid2_.type_ship(pos);
				std::cout << "\tTipo:" << type;
				if(type == 1){					// BATTLESHIP
					fire(s, pos, att); 
				} else if(type == 2) {		
					std::cout << "\n\nOLEEEE\n\n" << std::endl;	// HELPSHIP
					move_ship(s, pos, att);
					heal(s, pos, att);
				} else if(type == 3) {			// EXPL SUBMARINE
					move_ship(s, pos, att);
					search(s, pos, att);
				}
				// TEST
				std::cout << "\nScelta ed eseguita azione con nave di tipo " << type << " in posizione " << pos << std::endl;		
				// FINE TEST
				def = def_grid2_.ship(pos) -> center();
			}
		}catch(std::invalid_argument& e){
			std::cout << " Questo tipo non va ";
			valid  = false;
		}
	}
	
	std::pair<Coord, Coord> coord{def, att}; 
	write_log(coord);
	if(end(false)){
		return;
	}

	// valid = false;
	// while(!valid){
	// 	try{
	// 		valid = true;
	// 		int pos = select_ship(pl2);
	// 		att = UCoord::random_coord();
	// 		if(pl2 == 1){
	// 			int type = def_grid1_.type_ship(pos);
	// 			if(type == 1){
	// 				fire(pl2, pos, att);
	// 			}else if(type == 2){
	// 				move_ship(pl2, pos, att);
	// 				heal(pl2, pos, att);
	// 			}else if(type == 3){
	// 				move_ship(pl2, pos, att);
	// 				search(pl2, pos, att);
	// 			}
	// 			def = def_grid1_.ship(pos) -> center();
	// 		}
	// 		if(pl2 == 2){
	// 			int type = def_grid2_.type_ship(pos);
	// 			if(type == 1){
	// 				fire(pl2, pos, att);
	// 			}else if(type == 2){
	// 				move_ship(pl2, pos, att);
	// 				heal(pl2, pos, att);
	// 			}else if(type == 3){
	// 				move_ship(pl2, pos, att);
	// 				search(pl2, pos, att);
	// 			}
	// 			def = def_grid2_.ship(pos) -> center();
	// 		}
	// 	}catch(std::invalid_argument& e){
	// 		valid  = false;
	// 	}
	// }
	// std::pair<Coord, Coord> coord2{def, att}; 
	// write_log(coord2);
}

int Game::select_ship(int player){
	if(player == 1){
		int ran = rand()%(def_grid1_.number_ship());
		return ran;
	}else{
		int ran = rand()%(def_grid2_.number_ship());
		return ran;
	}
}


void Game::write_log(std::string x){
	log << x << std::endl;
}

void Game::write_log(std::pair<Coord, Coord>& x){
	log << x.first << " " << x.second << std::endl;
}


bool Game::end(bool over){
	if(turn_>=MAX_TURNS){
		if(over){
			std::cout << "\n\nPareggio!" << std::endl;
		}
		return true;
	}
	if(def_grid1_.number_ship()==0){
		if(over){
			std::cout << "\n\nPlayer 2 ha vinto!" << std::endl;
		}
		return true;	
	}
	if(def_grid2_.number_ship()==0){		
		if(over){
			std::cout << "\n\nPlayer 1 ha vinto!" << std::endl;
		}
		return true;
	}
	return false;
}

void Game::fire(int pl, int pos, Coord& c){
    if(pl == 1){
		// scorre le navi nella  defGrid nemica
		for(int i = 0; i<def_grid2_.number_ship(); i++){
			// scorre le coord di ogni nave
			for(int j = 0; j<def_grid2_.ship(i)->dim(); j++){
				// Se trova la nave nella posizione colipta 
				if(def_grid2_.ship(i)->coord().at(j) == c){
					// stampa nella griglia di attacco una x
					att_grid1_.add_char('x', c);
					// segna nella nave che è stata colpita
					def_grid2_.ship(i) -> hit(c);
					// segna nella defGrid nemica che è stata colpita
					def_grid2_.hit(c);
					// TEST
					std::cout << "\nNave colpita in posizione " << c << std::endl;
					// FINE TEST
					// controlla che la nave non sia distrutta
					if(def_grid2_.destroyed(i)){
						// se è distrutta
						// 
						titanic(pl, i);
						// 
						def_grid2_.reload();
						// Stampa a schermo le navi rimaste
						std::cout << "Nave abbattuta del player 2 - rimaste: " << def_grid2_.number_ship() << std::endl;
					}
					return;
				}
			}
		}
		// se non trova la nave, segna acqua ("O")
    	att_grid1_.add_char('O', c);
		// TEST
			std::cout << "\nAcqua in " << c << std::endl;
		// FINE TEST
    	return;
	}else{
		for(int i = 0; i<def_grid1_.number_ship(); i++){
			for(int j = 0; j<def_grid1_.ship(i)->dim(); j++){
				if(def_grid1_.ship(i)->coord().at(j) == c){
					att_grid2_.add_char('x', c);
					def_grid1_.ship(i) -> hit(c);
					def_grid1_.hit(c);
					// TEST
					std::cout << "\nNave colpita in posizione " << c << std::endl;
					// FINE TEST
					if(def_grid1_.destroyed(i)){
						titanic(pl, i);
						def_grid1_.reload();
						std::cout << "Nave abbattuta del player 1 - rimaste:";
						std::cout << def_grid1_.number_ship() << std::endl;
					}
					return;
				}
			}
		}
    	att_grid2_.add_char('O', c);
		// TEST
			std::cout << "\nAcqua in " << c << std::endl;
		// FINE TEST
    	return;
	} 
}

void Game::titanic(int pl, int pos){
    if(pl == 1){
		for(int i = 0; i<def_grid2_.ship(pos)->dim(); i++){
			att_grid1_.add_char('X', def_grid2_.ship(pos)->coord().at(i));
		}
		def_grid2_.remove_ship(pos);
		return;
	}else{
		for(int i = 0; i<def_grid1_.ship(pos)->dim(); i++){
			att_grid2_.add_char('X', def_grid1_.ship(pos)->coord().at(i));
		}
		def_grid1_.remove_ship(pos);
		return;
	}
}


void Game::heal(int pl, int pos, Coord& c){
	std::vector<Coord> coord_heal;
	for(int i = 0; i<3; i++){
		coord_heal.push_back(Coord{c.X()-1, c.Y()-1+i});
	}
	for(int i = 0; i<3; i++){
		coord_heal.push_back(Coord{c.X(), c.Y()-1+i});
	}
	for(int i = 0; i<3; i++){
		coord_heal.push_back(Coord{c.X()+1, c.Y()-1+i});
	}
	if(pl == 1){
		std::vector<Coord> coord = def_grid1_.ship(pos) -> coord();
		def_grid1_.ship(pos)->set_healed(true);
		// scorro la griglia 3x3 da curare
		for(int i = 0; i<coord_heal.size(); i++){
			// se è occupata cerca la nave
			if (!def_grid1_.check_position(coord_heal.at(i))) {
                int p = def_grid1_.find_ship(coord_heal.at(i));
                if(!def_grid1_.ship(p) -> healed()){
                    def_grid1_.ship(p) -> heal();
					// TEST
					std::cout << "Nave curata " << std::endl;
					// FINE TEST
                }
			}
		}
		def_grid1_.reload();
	}else{
		std::vector<Coord> coord = def_grid2_.ship(pos) -> coord();
		def_grid2_.ship(pos)->set_healed(true);
		for(int i = 0; i<coord_heal.size(); i++){
			if (!def_grid2_.check_position(coord_heal.at(i))) {
				int p = def_grid2_.find_ship(coord_heal.at(i));
            	if(!def_grid2_.ship(p) -> healed()){
                	def_grid2_.ship(p) -> heal();
					// TEST
					std::cout << "Nave curata " << std::endl;
					// FINE TEST
            	}
			}
		}
		def_grid2_.reload();
	}
}



void Game::search(int pl, int pos, Coord& c) {
    if(pl == 1){
		std::vector<Coord> coord;
		for(int i = 0; i<5; i++){
			Coord temp{c.X()-2, c.Y()-2+i};
			coord.push_back(temp);
		}
		for(int i = 0; i<5; i++){
			Coord temp{c.X()-1, c.Y()-2+i};
			coord.push_back(temp);
		}
		for(int i = 0; i<5; i++){
			Coord temp{c.X(), c.Y()-2+i};
			coord.push_back(temp);
		}
		for(int i = 0; i<5; i++){
			Coord temp{c.X()+1, c.Y()-2+i};
			coord.push_back(temp);
		}
		for(int i = 0; i<5; i++){
			Coord temp{c.X()+2, c.Y()-2+i};
			coord.push_back(temp);
		}

		for(int i = 0; i<coord.size(); i++){
			try{
				int pos = def_grid2_.find_ship(coord.at(i));
				att_grid1_.add_char('Y', coord.at(i));
			}catch(std::invalid_argument& e){}
		}
	}else{
		std::vector<Coord> coord;
		for(int i = 0; i<5; i++){
			Coord temp{c.X()-2, c.Y()-2+i};
			coord.push_back(temp);
		}
		for(int i = 0; i<5; i++){
			Coord temp{c.X()-1, c.Y()-2+i};
			coord.push_back(temp);
		}
		for(int i = 0; i<5; i++){
			Coord temp{c.X(), c.Y()-2+i};
			coord.push_back(temp);
		}
		for(int i = 0; i<5; i++){
			Coord temp{c.X()+1, c.Y()-2+i};
			coord.push_back(temp);
		}
		for(int i = 0; i<5; i++){
			Coord temp{c.X()+2, c.Y()-2+i};
			coord.push_back(temp);
		}

		for(int i = 0; i<coord.size(); i++){
			try{
				int pos = def_grid1_.find_ship(coord.at(i));
				att_grid2_.add_char('Y', coord.at(i));
			}catch(std::invalid_argument& e){}
		}
	}
}



void Game::move_ship(int pl, int pos, Coord& c){
	if(pl == 1){
		// determino il tipo di nave che devo muovere
		int type = def_grid1_.type_ship(pos);
		// caso: HELPSHIP
		if(type == 2){
			// Creo il vettore di coord dove andrà la nave
			std::vector<Coord> new_coord;
			if(def_grid1_.ship(pos)->orizzontal()){
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
			if(def_grid1_.check_position(new_coord)){
				HelpShip* s = dynamic_cast<HelpShip*>(def_grid1_.ship(pos));
				s -> move(c);
				// TEST
				std::cout << "Helpship spostata in " << c << std::endl;
				// FINE TEST
				return;
			}else{
				throw std::invalid_argument("Errore");
			}
		}
		// caso: SUBMARINE
		else if(type == 3){
			// controllo che la cella sia libera
			if(def_grid1_.check_position(c)){
				ExplorationSubmarine* s = dynamic_cast<ExplorationSubmarine*>(def_grid1_.ship(pos));
				s -> move(c);
				// TEST
				std::cout << "Submarine spostato in " << c << std::endl;
				// FINE TEST
				return;
			}else{
				throw std::invalid_argument("Errore");
			}
		}else{
			throw std::invalid_argument("Errore");
		}
	}else{
		int type = def_grid2_.type_ship(pos);
		if(type == 2){
			// Creo il vettore di coord dove andrà la nave
			std::vector<Coord> new_coord;
			if(def_grid1_.ship(pos)->orizzontal()){
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
			if(def_grid1_.check_position(new_coord)){
				HelpShip* s = dynamic_cast<HelpShip*>(def_grid1_.ship(pos));
				s -> move(c);
				// TEST
				std::cout << "Helpship spostata in " << c << std::endl;
				// FINE TEST
				return;
			}else{
				throw std::invalid_argument("Errore");
			}
		}else if(type == 3){
			std::vector<Coord>cord {c};
			if(def_grid2_.check_position(cord)){
				ExplorationSubmarine* s = dynamic_cast<ExplorationSubmarine*>(def_grid1_.ship(pos));
				s -> move(c);
				// TEST
				std::cout << "Submarine spostato in " << c << std::endl;
				// FINE TEST
				return;
			}else{
				throw std::invalid_argument("Errore");
			}
		}else{
			throw std::invalid_argument("Errore");
		}
	}
}

void util::to_upper(std::string& x){
	for(int i = 0; i<x.size(); i++){
		x.at(i) = std::toupper(x.at(i));
	}
}

void Game::print_defence(int pl){
	if(pl == 1){
		std::cout << "Player " << pl << " - " << def_grid1_;
	}else{
		std::cout << "Player " << pl << " - " << def_grid2_;
	}
}

void Game::print_attack(int pl){
	if(pl == 1){
		std::cout << "Player " << pl << " - " << att_grid1_;
	}else{
		std::cout << "Player " << pl << " - " << att_grid2_;
	}
}