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
	// incrementa il turno senza superare il limite
 	increment_turn();
	// controlla che la partita non sia finita:
	// - player senza navi
	// - limite turni raggiunto
	if(end(false)){
		return;
	}
	int pl1 = s;
	bool valid = false;
	Coord def, att;
	while(!valid){
		try{
			valid = true;
			// Seleziono la nave
			int pos = select_ship(pl1);
			std::cout << "Nave selezionata";
			// Seleziono delle coordinate random dove attaccare
			att = UCoord::random_coord();
			// Determino il numero del player per modificare la griglia giusta
			if(pl1 == 1){
				// Definisco il tipo di nave per l'azione da fare
				int type = def_grid1_.type_ship(pos);
				
				if(type == 1){					// BATTLESHIP
					fire(pl1, pos, att); 
				} else if(type == 2) {			// HELPSHIP
					move_ship(pl1, pos, att);
					heal(pl1, pos, att);
				} else if(type == 3) {			// EXPL SUBMARINE
					move_ship(pl1, pos, att);
					search(pl1, pos, att);
				}
				// Scrive la casella di arrivo della nave
				def = def_grid1_.ship(pos) -> center();
			}
			if(pl1 == 2){
				int type = def_grid2_.type_ship(pos);
				if(type == 1){					// BATTLESHIP
					fire(pl1, pos, att); 
				} else if(type == 2) {			// HELPSHIP
					move_ship(pl1, pos, att);
					heal(pl1, pos, att);
				} else if(type == 3) {			// EXPL SUBMARINE
					move_ship(pl1, pos, att);
					search(pl1, pos, att);
				}
				def = def_grid2_.ship(pos) -> center();
			}
		}catch(std::invalid_argument& e){
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
    if(pl = 1){
		for(int i = 0; i<def_grid2_.number_ship(); i++){
			for(int j = 0; j<def_grid2_.ship(i)->dim(); j++){
				if(def_grid2_.ship(i)->coord().at(j) == c){
					att_grid1_.add_char('x', c);
					def_grid2_.ship(i) -> hit(c);
					def_grid2_.hit(c);
					if(def_grid2_.destroyed(i)){
						titanic(pl, i);
						def_grid2_.reload();
						std::cout << "Nave abbattuta." << std::endl;
						std::cout << def_grid2_.number_ship() << std::endl;
					}
					return;
				}
			}
		}
    	att_grid1_.add_char('O', c);
    	return;
	}else{
		for(int i = 0; i<def_grid1_.number_ship(); i++){
			for(int j = 0; j<def_grid1_.ship(i)->dim(); j++){
				if(def_grid1_.ship(i)->coord().at(j) == c){
					att_grid2_.add_char('x', c);
					def_grid1_.ship(i) -> hit(c);
					def_grid1_.hit(c);
					if(def_grid1_.destroyed(i)){
						titanic(pl, i);
						def_grid1_.reload();
						std::cout << "Nave abbattuta." << std::endl;
						std::cout << def_grid1_.number_ship() << std::endl;
					}
					return;
				}
			}
		}
    	att_grid2_.add_char('O', c);
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
	if(pl = 1){
		std::vector<Coord> coord = def_grid1_.ship(pos) -> coord();
		bool heal = true;
		for(int i = 0; i<coord_heal.size(); i++){
			for(int j = 0; j<coord.size(); j++){
				if(coord_heal.at(i) == coord.at(j)){
					heal = false;
				}
            }
            if(heal){
                int p = def_grid1_.find_ship(coord_heal.at(i));
                if(!def_grid1_.ship(p) -> healed()){
                    def_grid1_.ship(p) -> heal();
                }
            }
            heal = true;
		}
		def_grid1_.reload();
	}else{
		std::vector<Coord> coord = def_grid2_.ship(pos) -> coord();
		bool heal = true;
		for(int i = 0; i<coord_heal.size(); i++){
			for(int j = 0; j<coord.size(); j++){
				if(coord_heal.at(i) == coord.at(j)){
					heal = false;
				}
			}
			if(heal){
                int p = def_grid2_.find_ship(coord_heal.at(i));
				if(!def_grid2_.ship(p) -> healed()){
					def_grid2_.ship(p) -> heal();
				}
			}
            heal = true;
		}
		def_grid2_.reload();
	}
}



void Game::search(int pl, int pos, Coord& c) {
    if(pl == 1){
		for (int i = (c.Y()-2); i < (c.Y()+3); i++) {
			for (int j = (c.X()-2); j < (c.X()+3); j++) {
				Coord c{i, j};
				if (j < 0 || i < 0){
					continue;
				}else if (def_grid2_.get_char(c) != ' ') {
					char valueFind = def_grid1_.get_char(c);
					if (valueFind == 'C' || valueFind == 'E' || valueFind == 'S') {
						att_grid1_.insert_char('Y', c);
					}else if (valueFind == 'c' || valueFind == 'e' || valueFind == 's') {
						att_grid1_.insert_char('x', c);
					}
				}
        	}
    	}
	}else{
		for (int i = (c.Y()-2); i < (c.Y()+3); i++) {
			for (int j = (c.X()-2); j < (c.X()+3); j++) {
				Coord c{i, j};
				if (j < 0 || i < 0){
					continue;
				}else if (def_grid1_.get_char(c) != ' ') {
					char valueFind = def_grid1_.get_char(c);
					if (valueFind == 'C' || valueFind == 'E' || valueFind == 'S') {
						att_grid2_.insert_char('Y', c);
					}else if (valueFind == 'c' || valueFind == 'e' || valueFind == 'd') {
						att_grid2_.insert_char('x', c);
					}
				}
        	}
    	}
	}
}



void Game::move_ship(int pl, int pos, Coord& c){
	if(pl == 1){
		int type = def_grid1_.type_ship(pos);
		if(type == 2){
			std::vector<Coord> coord;
			if(def_grid1_.ship(pos)->orizzontal()){
				Coord c{def_grid1_.ship(pos)->x(), def_grid1_.ship(pos)->y()-1};
				coord.push_back(c);
				c = Coord{def_grid1_.ship(pos)->center()};
				coord.push_back(c);
				c = Coord{def_grid1_.ship(pos)->x(),def_grid1_.ship(pos)->y()+1};
				coord.push_back(c);
			}else{
				Coord c{def_grid1_.ship(pos)->x()-1, def_grid1_.ship(pos)->y()};
				coord.push_back(c);
				c = Coord{def_grid1_.ship(pos)->center()};
				coord.push_back(c);
				c = Coord{def_grid1_.ship(pos)->x()+1,def_grid1_.ship(pos)->y()};
				coord.push_back(c);
			}
			if(def_grid1_.check_position(coord)){
				dynamic_cast<HelpShip*>(def_grid1_.ship(pos)) -> move(c);
				return;
			}else{
				throw std::invalid_argument("Errore");
			}
		}else if(type == 3){
			if(def_grid1_.check_position(c)){
				dynamic_cast<ExplorationSubmarine*>(def_grid1_.ship(pos)) -> move(c);
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
			std::vector<Coord> coord;
			if(def_grid2_.ship(pos)->orizzontal()){
				Coord c{def_grid2_.ship(pos)->x(), def_grid2_.ship(pos)->y()-1};
				coord.push_back(c);
				c = Coord{def_grid2_.ship(pos)->center()};
				coord.push_back(c);
				c = Coord{def_grid2_.ship(pos)->x(),def_grid2_.ship(pos)->y()+1};
				coord.push_back(c);
			}else{
				Coord c{def_grid2_.ship(pos)->x()-1, def_grid2_.ship(pos)->y()};
				coord.push_back(c);
				c = Coord{def_grid2_.ship(pos)->center()};
				coord.push_back(c);
				c = Coord{def_grid2_.ship(pos)->x()+1,def_grid2_.ship(pos)->y()};
				coord.push_back(c);
			}
			if(def_grid2_.check_position(coord)){
				dynamic_cast<HelpShip*>(def_grid2_.ship(pos)) -> move(c);
				return;
			}else{
				throw std::invalid_argument("Errore");
			}
		}else if(type == 3){
			std::vector<Coord>cord {c};
			if(def_grid2_.check_position(cord)){
				dynamic_cast<ExplorationSubmarine*>(def_grid2_.ship(pos)) -> move(c);
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