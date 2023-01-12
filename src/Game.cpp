#include "../include/Game.h"
#include "../include/GamePlayer.h"
#include "../include/Game.h"
#include "../include/Grid.h"
#include "../include/DefenceGrid.h"
#include "../include/AttackGrid.h"
#include "../include/Coord.h"
#include "../include/Battleship.h"
#include "../include/HelpShip.h"
#include "../include/ExplorationSubmarine.h"


#include <time.h>
#include <stdlib.h>
#include <iostream>

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




void Game::make_move(int s){
 	turn_++;
	int pl1 = 0;
	int pl2 = 0;
	if(starter_==1){
		pl1 = 1;
		pl2 = 2;
	}else{
		pl1 = 2;
		pl2 = 1;
	}
	std::pair<Coord, Coord> move = select_move(pl1);
	Coord def = move.first;
	Coord att = move.second;

	move = select_move(pl1);
	def = move.first;
	att = move.second;
	if(pl1 == 1){
		int pos = def_grid_.first.find_ship(def);
		int type = def_grid_.first.type_ship(pos);
		if(type == 1){
			
		}else if(type == 2){

		}else if(type == 3){

		}

	}
}

std::pair<Coord, Coord> Game::select_move(int player){
	int x, y;
	if(player == 1){
		srand(time(NULL));
		int ran = rand()%(def_grid_.first.number_ship());
		x = def_grid_.first.ships().at(ran).center().X();
		y = def_grid_.first.ships().at(ran).center().Y();
	}else{
		int x, y;
		srand(time(NULL));
		int ran = rand()%(def_grid_.second.number_ship());
		x = def_grid_.second.ships().at(ran).center().X();
		y = def_grid_.second.ships().at(ran).center().Y();
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

void Game::attack(int pl, Coord c){

}

void Game::heal(int pl, int pos, Coord c){
	if(pl == 1){
		HelpShip& ship = dynamic_cast<HelpShip&>(def_grid_.first.ships().at(pos));
		ship
	}else{
		HelpShip& ship = dynamic_cast<HelpShip&>(def_grid_.second.ships().at(pos));
	}
}

void Game::exploration(int pl, int pos, Coord c){

}
