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
    int pl = (starter_);
	
	int number_c = 1;
	char t = 1;
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
		}catch(std::invalid_argument& e){
			std::cout << "Errore";
		}
	}

	print_defence(pl);

    if(pl==1){
        pl=2;
    }else{
        pl=1;
    }

    number_c = 1;
	t = 1;
    dim = 4;
	while(number_c < 4){
		try{
			Coord punta = UCoord::random_coord();
			Coord coda = UCoord::random_coord(punta, dim);
			Game::add_ship(pl, punta, coda, t);
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
			Game::add_ship(pl, punta, coda, t);
			number_s++;
		}catch(std::invalid_argument& e){std::cout << "Errore";}
	}		
	
	number_e = 1;
	t = 3;
	while(number_e < 3){
		try{
			Coord punta = UCoord::random_coord();
			Coord coda = punta;
			Game::add_ship(pl, punta, coda, t);
			number_e++;
		}catch(std::invalid_argument& e){std::cout << "Errore";}
	}

	print_defence(pl);
}

void GamePc::start(void){
	while(!end()){
		make_move(starter());
	}
}