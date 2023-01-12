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
			std::cin >> coda;
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
			std::cin >> coda;
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
			std::cout << "Inserire le coordinate del sottomarino di esplorazione " << number_e << ": ";
			std::cin >> punta;
			std::cin >> coda;
			Game::add_ship(pl, UCoord::from_string_to_coord(punta), UCoord::from_string_to_coord(coda), t);
			number_e++;
		}catch(std::invalid_argument& e){
			std::cout << "Coordinate non valide, reinserire." << std::endl;
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
			std::cout << "Prossima mossa --> ";
			std::cin >> first >> second;
			Coord f = UCoord::from_string_to_coord(first);
			Coord s = UCoord::from_string_to_coord(second);
			for(int i = 0; i<def_grid_.first.number_ship(); i++){
				if(def_grid_.first.ships().at(i).center() == f){
					end = true;
					break;
				}
			}
			if(!end){
				std::cout << "Coordinate inserite non valide." << std::endl;
			}
		}
		std::pair<Coord, Coord> coord{f, s};
		return coord;
	}else{
		int x, y;
		srand(time(NULL));
		int ran = rand()%(def_grid_.second.number_ship());
		x = def_grid_.second.ships().at(ran).center().X();
		y = def_grid_.second.ships().at(ran).center().Y();
		Coord first{x,y};
		Coord second = UCoord::random_coord();
		std::pair<Coord, Coord> coord{first, second};
		return coord;
	}
}