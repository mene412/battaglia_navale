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

	// Inseriamo le navi nella griglia di pl1
	// Creazione e inserimento corazzate - pl1
	int number_c = 0;
	int t = 1;
	int dim = 4;
	while(number_c < 3){
		try{
			Coord punta = UCoord::random_coord();
			Coord coda = UCoord::random_coord(punta, dim);
			Game::add_ship(pl1, punta, coda, t);
			number_c++;
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
	// Creazione e inserimento sottomarini - pl1
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
	// Inseriamo le navi nella griglia di pl2
	// Creazione e inserimento corazzate - pl2
	number_c = 1;
	t = 1;
    dim = 4;
	while(number_c < 4){
		try{
			Coord punta = UCoord::random_coord();
			Coord coda = UCoord::random_coord(punta, dim);
			Game::add_ship(pl2, punta, coda, t);
			number_c++;
		}catch(std::invalid_argument& e){}
	}
	// Creazione e inserimento navi di supporto - pl2
	number_s = 1;
	t = 2;
	dim = 2;
	while(number_s < 4){
		try{
			Coord punta = UCoord::random_coord();
			Coord coda = UCoord::random_coord(punta, dim);
			Game::add_ship(pl2, punta, coda, t);
			number_s++;
		}catch(std::invalid_argument& e){}
	}		
	// Creazione e inserimento sottomarini - pl2
	number_e = 1;
	t = 3;
	while(number_e < 3){
		try{
			Coord punta = UCoord::random_coord();
			Coord coda = punta;
			Game::add_ship(pl2, punta, coda, t);
			number_e++;
		}catch(std::invalid_argument& e){}
	}

	std::cout << "Navi corrette" << std::endl;
}

void GamePc::start(void){
		// Testo di controllo
		std::cout << "Player 1: \nNumero navi: " << def_grid1_.number_ship() << std::endl;
		for (int i = 0; i < def_grid1_.number_ship(); i++) {
			std::cout << "\tNave " << i << ": tipo " << def_grid1_.type_ship(i) << std::endl;
		}
		std::cout << "Player 2: \nNumero navi: " << def_grid2_.number_ship() << std::endl;
		for (int i = 0; i < def_grid2_.number_ship(); i++) {
			std::cout << "\tNave " << i << ": tipo " << def_grid2_.type_ship(i) << std::endl;
		}
		// Fine testo di controllo da cancellare
		print_defence(1);
		print_attack(1);
		print_defence(2);
		print_attack(2);
	while(!end(false)){
		make_move(starter());
		make_move((starter()%2)+1);
	}
		print_defence(1);
		print_attack(1);
		print_defence(2);
		print_attack(2);
	if(end(true)){
		std::cout << "\nChiusura programma...\n" << std::endl; 
	}
}