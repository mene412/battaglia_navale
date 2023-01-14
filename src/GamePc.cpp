// Autore: Andrea Mutti
#include "../include/GamePc.h"

#include <ctime>
#include <cstdlib>

GamePc::GamePc(void)
:   Game{}
{
    select_starter();
	positioning();
}

void GamePc::positioning(void){
    int pl1 = (starter_);
	int pl2;
	if(pl1 == 1){
		pl2 = 2;
	}else{
		pl2 = 1;
	}
	int number_c = 0;
	int t = 1;
	int dim = 4;
	while(number_c < 3){
		try{
			Coord punta = UCoord::random_coord();
			Coord coda = UCoord::random_coord(punta, dim);
			Game::add_ship(pl1, punta, coda, t);
			number_c++;
			std::cout << std::to_string(number_c) << std::endl;
		}catch(std::invalid_argument& e){}
	}
	
	int number_s = 0;
	t = 2;
	dim = 2;
	while(number_s < 3){
		try{
			Coord punta = UCoord::random_coord();
			Coord coda = UCoord::random_coord(punta, dim);
			Game::add_ship(pl1, punta, coda, t);
			number_s++;
		}catch(std::invalid_argument& e){}
	}		
	
	int number_e = 0;
	t = 3;
	while(number_e < 2){
		try{
			Coord punta = UCoord::random_coord();
			Coord coda = punta;
			Game::add_ship(pl1, punta, coda, t);
			number_e++;
		}catch(std::invalid_argument& e){}
	}

	print_defence(pl1);
    
	std::cout << "OK";

	number_c = 1;
	t = 1;
    dim = 4;
	while(number_c < 4){
		try{
			Coord punta = UCoord::random_coord();
			Coord coda = UCoord::random_coord(punta, dim);
			Game::add_ship(pl2, punta, coda, t);
			number_c++;
		}catch(std::invalid_argument& e){std::cout << "Errore";}
	}
	number_s = 1;
	t = 2;
	dim = 2;
	while(number_s < 4){
		try{
			Coord punta = UCoord::random_coord();
			Coord coda = UCoord::random_coord(punta, dim);
			Game::add_ship(pl2, punta, coda, t);
			number_s++;
		}catch(std::invalid_argument& e){std::cout << "Errore";}
	}		
	
	number_e = 1;
	t = 3;
	while(number_e < 3){
		try{
			Coord punta = UCoord::random_coord();
			Coord coda = punta;
			Game::add_ship(pl2, punta, coda, t);
			number_e++;
		}catch(std::invalid_argument& e){std::cout << "Errore";}
	}

	print_defence(pl2);
}

void GamePc::start(void){
	while(!end()){
		make_move(starter());
	}
}