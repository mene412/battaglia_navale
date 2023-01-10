#include "Game.h"
#include "GamePlayer.h"
#include "GamePc.h"

#include <time.h>
#include <stdlib.h>


Game::Game(void)
	: def_grid1_{DefenseGrid{}}, att_grid1_{AttackGrid{}}, def_grid2_{DefenseGrid{}}, att_grid2_{AttackGrid{}}, turn_{0} 
{
	std::cout << "Inizio gioco.\n" << std::endl; 
}

void Game::select_starter(void){
	std::srand(time(NULL));
	int s = rand()%2+1;
	if(s==1){
		std::cout << "Inizia il player " << s << std::endl;
	}else if(s==2)
		std::cout << "Inizia il player " << s << std::endl;
	}
	starter_{s};
}


GamePlayer::GamePlayer(void)
	: Game{}, starter_{0}
{
	select_starter();
	positioning();
}

void GamePlayer::select_starter(void) override{
	std::srand(time(NULL));
	int s = rand()%2+1;
	if(s==1){
		std::cout << "Inizia il player " << s << " (You)" << std::endl;
	}else if(s==2)
		std::cout << "Inizia il player " << s << " (Pc)" << std::endl;
	}
	starter_{s};
}

void GamePlayer::positioning(void){
 	if(starter_==0){
 		throw new std::illegal_argument();
 	}
 	if(starter_==1){
 		positioning_player();
 		positioning_pc();
 	else{
 		positionin_pc();
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
			Game::add_ship(pl, from_string_to_coord(punta), from_string_to_coord(coda), t);
			number_c++;
		}catch(){
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
			Game::add_ship(pl, from_string_to_coord(punta), from_string_to_coord(coda), t);
			number_s++;
		}catch(){
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
			Game::add_ship(pl, from_string_to_coord(punta), from_string_to_coord(coda), t);
			number_e++;
		}catch(){
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
			Coord punta = Coord::random_coord();
			Coord coda = Coord::random_coord(punta, dim);
			Game::add_ship(pl, punta, coda, t);
			number_c++;
		}catch(){}
	}
	
	int number_s = 1;
	t = 'S';
	dim = 2;
	while(number_s < 4){
		try{
			Coord punta = Coord::random_coord();
			Coord coda = Coord::random_coord(punta, dim);
			Game::add_ship(pl, punta, coda, t);
			number_s++;
		}catch(){}
	}		
	
	int number_e = 1;
	t = 'E';
	while(number_e < 3){
		try{
			Coord punta = Coord::random_coord();
			Coord coda = Coord::punta;
			Game::add_ship(pl, punta, coda, t);
			number_e++;
		}catch(){}
	}
}

void Game::make_move(int s){
 	
}

 
