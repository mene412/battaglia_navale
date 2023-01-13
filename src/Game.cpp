#include "../include/Game.h"
#include "../include/DefenceGrid.h"
#include "../include/AttackGrid.h"


#include <ctime>
#include <cstdlib>
#include <iostream>
#include <cmath>

Game::Game(void)
	: def_grid_{DefenceGrid{}, DefenceGrid{}}, att_grid_{AttackGrid{}, AttackGrid{}}, turn_{0}, starter_{0}, log{"../log.txt"}
{
	std::cout << "Inizio gioco.\n" << std::endl; 
}

void Game::select_starter(void){
	std::srand(time(NULL));
	int s = rand()%2+1;
	if(s==1){
		std::cout << "Inizia il player " << s << std::endl;
	}else if(s==2){
		std::cout << "Inizia il player " << s << std::endl;
	}
	starter_ = s;
	write_log(std::to_string(s));
}

void Game::add_ship(int player, Coord p, Coord c, char type){
	if(player == 1){
		switch(type){
			case 'C':
				def_grid_.first.add_ship(Battleship{p, c});
				break;
			case 'S':
				def_grid_.first.add_ship(HelpShip{p, c});
				break;
			case 'E':
				def_grid_.first.add_ship(ExplorationSubmarine{p, c});
				break;
		}
	}else{
		switch(type){
			case 'C':
				def_grid_.second.add_ship(Battleship{p, c});
				break;
			case 'S':
				def_grid_.second.add_ship(HelpShip{p, c});
				break;
			case 'E':
				def_grid_.second.add_ship(ExplorationSubmarine{p, c});
				break;
		}
	}
}

void Game::increment_turn(void){
	turn_++;
	if(turn_ == MAX_TURNS){
		return;
	}
}

void Game::make_move(int s){
 	increment_turn();
	int pl1 = 0;
	int pl2 = 0;
	if(starter_==1){
		pl1 = 1;
		pl2 = 2;
	}else{
		pl1 = 2;
		pl2 = 1;
	}
	bool valid = false;
	std::pair<Coord, Coord> move;
	Coord def, att;
	move = select_move(pl1);
	def = move.first;
	att = move.second;
	if(pl1 == 1){
		int pos = def_grid_.first.find_ship(def);
		int type = def_grid_.first.type_ship(pos);
		if(type == 1){
			fire(pl1, pos, att);
		}else if(type == 2){
			move_help(pl1, pos, att);
			heal(pl1, pos, att);
		}else if(type == 3){
			move_sub(pl1, pos, att);
			exploration(pl1, pos, att);
		}
	}
	if(pl1 == 2){
		int pos = def_grid_.second.find_ship(def);
		int type = def_grid_.second.type_ship(pos);
		if(type == 1){
			fire(pl1, pos, att);
		}else if(type == 2){
			move_help(pl1, pos, att);
			heal(pl1, pos, att);
		}else if(type == 3){
			move_sub(pl1, pos, att);
			exploration(pl1, pos, att);
		}
	}
	valid = false;
	while(!valid){
		try{
			move = select_move(pl1);
			def = move.first;
			att = move.second;
			if(pl2 == 1){
				int pos = def_grid_.first.find_ship(def);
				int type = def_grid_.first.type_ship(pos);
				if(type == 1){
					fire(pl2, pos, att);
				}else if(type == 2){
					move_help(pl2, pos, att);
					heal(pl2, pos, att);
				}else if(type == 3){
					move_sub(pl2, pos, att);
					search(pl2, pos, att);
				}
			}
			if(pl2 == 2){
				int pos = def_grid_.second.find_ship(def);
				int type = def_grid_.second.type_ship(pos);
				if(type == 1){
					fire(pl2, pos, att);
				}else if(type == 2){
					move_help(pl2, pos, att);
					heal(pl2, pos, att);
				}else if(type == 3){
					move_sub(pl2, pos, att);
					search(pl2, pos, att);
				}
			}
		}catch(std::invalid_argument& e){
			valid  = false;
			if(pl2 == 1){
				std::cout << "Coordinate non valide" << std::endl;
			}
		}
	}
}

std::pair<Coord, Coord> Game::select_move(int player){
	int x, y;
	if(player == 1){
		srand(time(NULL));
		int ran = rand()%(def_grid_.first.number_ship());
		x = def_grid_.first.ships().at(ran)->center().X();
		y = def_grid_.first.ships().at(ran)->center().Y();
	}else{
		int x, y;
		srand(time(NULL));
		int ran = rand()%(def_grid_.second.number_ship());
		x = def_grid_.second.ships().at(ran)->center().X();
		y = def_grid_.second.ships().at(ran)->center().Y();
	}

	Coord first{x,y};
	Coord second = UCoord::random_coord();
	std::pair<Coord, Coord> coord{first, second};
	return coord;
}


void Game::write_log(std::string x){
	log << x << std::endl;
}

void Game::write_log(std::pair<Coord, Coord>& x){
	log << x.first << " " << x.second << std::endl;
}

void Game::write_log(std::vector<std::string>& x){
	for(int i = 0; i<x.size(); i++){
		log << x.at(i);
		if(i!=(x.size()-1)){
			log << " ";
		}
	}
	log << std::endl;
}

bool Game::end_max_turn(void) const {
	if(turn_>=MAX_TURNS){
		exit(1);
	}
}


void Game::move(int pl, int pos, Coord c){
	if(pl == 1){
		HelpShip* ship = dynamic_cast<HelpShip*>(def_grid_.first.ships().at(pos));
		ship->move(def_grid_.first, c);
	}else{
		HelpShip* ship = dynamic_cast<HelpShip*>(def_grid_.second.ships().at(pos));
		ship->move(def_grid_.second, c);
	}
}

void Game::heal(int pl, int pos, Coord c){
	if(pl == 1){
		HelpShip* ship = dynamic_cast<HelpShip*>(def_grid_.first.ships().at(pos));
		ship->heal(def_grid_.first, c);
	}else{
		HelpShip* ship = dynamic_cast<HelpShip*>(def_grid_.second.ships().at(pos));
		ship->heal(def_grid_.second, c);
	}
}




void Game::fire(int pl, int pos, Coord c){
    if(pl = 1){
		for(int i = 0; i<def_grid_.second.number_ship(); i++){
			for(int j = 0; j<def_grid_.second.ships().at(i)->coord().size(); j++){
				if(def_grid_.second.ships().at(i)->coord().at(j) == c){
					att_grid_.first.add_char('x', c);
					def_grid_.second.ships().at(i) -> dec_armor();
					if(def_grid_.second.destroyed(i)){
						std::cout << "Nave abbattuta." << std::endl;
					}
					return;
				}
			}
		}
    	att_grid_.first.add_char('o', c);
    	return;
	}else{
		for(int i = 0; i<def_grid_.first.number_ship(); i++){
			for(int j = 0; j<def_grid_.first.ships().at(i)->coord().size(); j++){
				if(def_grid_.first.ships().at(i)->coord().at(j) == c){
					att_grid_.second.add_char('x', c);
					def_grid_.first.ships().at(i) -> dec_armor();
					if(def_grid_.first.destroyed(i)){
						std::cout << "Nave abbattuta." << std::endl;
					}
					return;
				}
			}
		}
    	att_grid_.first.add_char('o', c);
    	return;
	} 
}

void Game::titanic(int pl, int pos){
    if(pl == 1){
		for(int i = 0; i<def_grid_.second.ships().at(pos)->coord().size(); i++){
			att_grid_.first.add_char('X', def_grid_.second.ships().at(pos)->coord().at(i));
		}
		def_grid_.second.remove_ship(pos);
		return;
	}else{
		for(int i = 0; i<def_grid_.first.ships().at(pos)->coord().size(); i++){
			att_grid_.second.add_char('X', def_grid_.first.ships().at(pos)->coord().at(i));
		}
		def_grid_.first.remove_ship(pos);
		return;
	}
}






void Game::search(int pl, int pos, Coord c) {
    if(pl == 1){
		for (int i = (c.Y()-2); i < (c.Y()+3); i++) {
			for (int j = (c.X()-2); j < (c.X()+3); j++) {
				if (j < 0 || i < 0){
					continue;
				}else if (def_grid_.second.grid().at(i).at(j) != ' ') {
					char valueFind = att_grid_.first.grid()[i][j];
					if (valueFind == 'C' || valueFind == 'E' || valueFind == 'S') {
						att_grid_.first.grid().at(i).at(j) = 'Y';
					}
					else if (valueFind == 'c' || valueFind == 'e' || valueFind == 's') {
						att_grid_.first.grid()[i][j] = 'x';
					}
				}
        	}
    	}
	}else{
		for (int i = (c.Y()-2); i < (c.Y()+3); i++) {
			for (int j = (c.X()-2); j < (c.X()+3); j++) {
				if (j < 0 || i < 0){
					continue;
				}else if (enemyGrid.grid().at(i).at(j) != ' ') {
					char valueFind = enemyGrid.grid()[i][j];
					if (valueFind == 'C' || valueFind == 'E' || valueFind == 'S') {
						myGrid.grid()[i][j] = 'Y';
					}
					else if (valueFind == 'c' || valueFind == 'e' || valueFind == 'd') {
						myGrid.grid()[i][j] = 'X';
					}
				}
        	}
    	}
	}
}





void util::to_upper(std::string& x){
	for(int i = 0; i<x.size(); i++){
		x.at(i) = std::toupper(x.at(i));
	}
}