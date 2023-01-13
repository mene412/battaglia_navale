#include "../include/GamePlayer.h"
#include "../include/Game.h"


#include <time.h>
#include <stdlib.h>
#include <iostream>

GamePlayer::GamePlayer(void)
	: Game{}
{
	select_starter();
	positioning();
}

void GamePlayer::select_starter(void) {
	std::srand(time(NULL));
	int s = rand()%2+1;
	if(s==1){
		std::cout << "Inizia il player " << s << " (You)" << std::endl;
	}else if(s==2){
		std::cout << "Inizia il player " << s << " (Pc)" << std::endl;
	}
	starter_ = s;
}

void GamePlayer::positioning(void){
 	if(starter_==0){
 		throw std::invalid_argument("Errore");
 	}
 	if(starter_==1){
 		positioning_player();
 		positioning_pc();
 	}else{
 		positioning_pc();
 		positioning_player();
 	}
 	std::cout << "\nPosizionamento navi terminato.\n" << std::endl;
}

void GamePlayer::positioning_player(void){
	int const pl = 1;
	int number_c = 1;
	std::string punta;
	std::string coda;
	char t = 'C';
	while(number_c < 4){
		try{
			std::cout << "Inserire le coordinate della nave corazzata " << number_c << ": ";
			std::cin >> punta;
			util::to_upper(punta);
			std::cin >> coda;
			util::to_upper(coda);
			Game::add_ship(pl, UCoord::from_string_to_coord(punta), UCoord::from_string_to_coord(coda), t);
			number_c++;
		}catch(std::invalid_argument& e){
			std::cout << "Coordinate non valide, reinserire." << std::endl;
		}
	}
	
	int number_s = 1;
	t = 'S';
	while(number_s < 4){
		try{
			std::cout << "Inserire le coordinate della nave di supporto " << number_s << ": ";
			std::cin >> punta;
			util::to_upper(punta);
			std::cin >> coda;
			util::to_upper(coda);
			Game::add_ship(pl, UCoord::from_string_to_coord(punta), UCoord::from_string_to_coord(coda), t);
			number_s++;
		}catch(std::invalid_argument& e){
			std::cout << "Coordinate non valide, reinserire." << std::endl;
		}
	}		
	
	int number_e = 1;
	t = 'E';
	while(number_e < 3){
		try{
			std::cout << "Inserire la coordinata del sottomarino di esplorazione " << number_e << ": ";
			std::cin >> punta;
			util::to_upper(punta);
			Game::add_ship(pl, UCoord::from_string_to_coord(punta), UCoord::from_string_to_coord(punta), t);
			number_e++;
		}catch(std::invalid_argument& e){
			std::cout << "Coordinate non valide, reinserire." << std::endl;
		}
	}
}

void GamePlayer::make_move(int s){
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
	std::pair<Coord, Coord> move;
	Coord def;
	Coord att;
	bool valid = false;
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
					move_ship(pl2, pos, att);
					heal(pl2, pos, att);
				}else if(type == 3){
					move_ship(pl2, pos, att);
					search(pl2, pos, att);
				}
			}
			if(pl2 == 2){
				int pos = def_grid_.second.find_ship(def);
				int type = def_grid_.second.type_ship(pos);
				if(type == 1){
					fire(pl2, pos, att);
				}else if(type == 2){
					move_ship(pl2, pos, att);
					heal(pl2, pos, att);
				}else if(type == 3){
					move_ship(pl2, pos, att);
					search(pl2, pos, att);
				}
			}
		}catch(std::invalid_argument& e){
			valid  = false;
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
					move_ship(pl2, pos, att);
					heal(pl2, pos, att);
				}else if(type == 3){
					move_ship(pl2, pos, att);
					search(pl2, pos, att);
				}
			}
			if(pl2 == 2){
				int pos = def_grid_.second.find_ship(def);
				int type = def_grid_.second.type_ship(pos);
				if(type == 1){
					fire(pl2, pos, att);
				}else if(type == 2){
					move_ship(pl2, pos, att);
					heal(pl2, pos, att);
				}else if(type == 3){
					move_ship(pl2, pos, att);
					search(pl2, pos, att);
				}
			}
		}catch(std::invalid_argument& e){
			valid  = false;
		}
	}
}

void GamePlayer::positioning_pc(void){
	int const pl = 2;
	int number_c = 1;
	char t = 'C';
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
	t = 'S';
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
	t = 'E';
	while(number_e < 3){
		try{
			Coord punta = UCoord::random_coord();
			Coord coda = punta;
			Game::add_ship(pl, punta, coda, t);
			number_e++;
		}catch(std::invalid_argument& e){}
	}
}

std::pair<Coord,Coord> GamePlayer::select_move(int player){
	if(player == 1){
		bool end = false;
		std::string first;
		std::string second;
		Coord f{};
		Coord s{};
		while(!end){
			bool choice = false;
			while(!choice){
				std::cout << "Prossima mossa --> ";
				std::cin >> first >> second;
				choice = true;
				util::to_upper(first);
				if(first=="XX" && second=="XX"){
					std::cout << att_grid_.first;
					choice = false;
				}
				if(first=="AA" && second=="AA"){
					att_grid_.first.remove_detections();
					choice = false;
				}
				if(first=="BB" && second=="BB"){
					att_grid_.first.remove_hit();
					choice = false;
				}
				if(first=="CC" && second=="CC"){
					att_grid_.first.remove_water();
					choice = false;
				}
			}
			try{
				Coord f = UCoord::from_string_to_coord(first);
				Coord s = UCoord::from_string_to_coord(second);
				
				if(!end){
					std::cout << "Coordinate inserite non valide." << std::endl;
				}
			}catch(std::invalid_argument& e){
				std::cout << "Coordinate inserite non valide." << std::endl;
			}
		}
		std::pair<Coord, Coord> coord{f, s};
		return coord;
	}else{
		int x, y;
		srand(time(NULL));
		int ran = rand()%(def_grid_.second.number_ship());
		x = def_grid_.second.ships().at(ran)->center().X();
		y = def_grid_.second.ships().at(ran)->center().Y();
		Coord first{x,y};
		Coord second = UCoord::random_coord();
		std::pair<Coord, Coord> coord{first, second};
		return coord;
	}
}

