#include "../include/GamePlayer.h"


#include <ctime>
#include <cstdlib>

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
	int t = 1;
	while(number_c < 4){
		try{
			std::cout << "Inserire le coordinate della nave corazzata " << number_c << ": ";
			std::cin >> punta;
			util::to_upper(punta);
			std::cin >> coda;
			util::to_upper(coda);
			Coord p{UCoord::from_string_to_coord(punta)};
			Coord c{UCoord::from_string_to_coord(coda)};
			Game::add_ship(pl, p, c, t);
			number_c++;
		}catch(std::invalid_argument& e){
			std::cout << "Coordinate non valide, reinserire." << std::endl;
		}
	}
	
	int number_s = 1;
	t = 2;
	while(number_s < 4){
		try{
			std::cout << "Inserire le coordinate della nave di supporto " << number_s << ": ";
			std::cin >> punta;
			util::to_upper(punta);
			std::cin >> coda;
			util::to_upper(coda);			
			Coord p{UCoord::from_string_to_coord(punta)};
			Coord c{UCoord::from_string_to_coord(coda)};
			Game::add_ship(pl, p, c, t);
			number_s++;
		}catch(std::invalid_argument& e){
			std::cout << "Coordinate non valide, reinserire." << std::endl;
		}
	}		
	
	int number_e = 1;
	t = 3;
	while(number_e < 3){
		try{
			std::cout << "Inserire la coordinata del sottomarino di esplorazione " << number_e << ": ";
			std::cin >> punta;
			util::to_upper(punta);
			Coord p{UCoord::from_string_to_coord(punta)};
			Coord c{UCoord::from_string_to_coord(punta)};
			Game::add_ship(pl, p, c, t);
			number_e++;
		}catch(std::invalid_argument& e){
			std::cout << "Coordinate non valide, reinserire." << std::endl;
		}
	}
}

//void GamePlayer::make_move(int s){
// 	increment_turn();
//	int pl1 = 0;
//	int pl2 = 0;
//	if(starter_==1){
//		pl1 = 1;
//		pl2 = 2;
//	}else{
//		pl1 = 2;
//		pl2 = 1;
//	}
//	std::pair<Coord, Coord> move;
//	Coord def;
//	Coord att;
//	bool valid = false;
//	while(!valid){
//		try{
//			//move = select_move(pl1);
//			def = move.first;
//			att = move.second;
//			if(pl2 == 1){
//				int pos = def_grid1_.find_ship(def);
//				int type = def_grid1_.type_ship(pos);
//				if(type == 1){
//					fire(pl2, pos, att);
//				}else if(type == 2){
//					move_ship(pl2, pos, att);
//					heal(pl2, pos, att);
//				}else if(type == 3){
//					move_ship(pl2, pos, att);
//					search(pl2, pos, att);
//				}
//			}
//			if(pl2 == 2){
//				int pos = def_grid2_.find_ship(def);
//				int type = def_grid2_.type_ship(pos);
//				if(type == 1){
//					fire(pl2, pos, att);
//				}else if(type == 2){
//					move_ship(pl2, pos, att);
//					heal(pl2, pos, att);
//				}else if(type == 3){
//					move_ship(pl2, pos, att);
//					search(pl2, pos, att);
//				}
//			}
//		}catch(std::invalid_argument& e){
//			valid  = false;
//		}
//	}
//
//	valid = false;
//	while(!valid){
//		try{
			//move = select_move(pl1);
//			def = move.first;
//			att = move.second;
//			if(pl2 == 1){
//				int pos = def_grid1_.find_ship(def);
//				int type = def_grid1_.type_ship(pos);
//				if(type == 1){
//					fire(pl2, pos, att);
//				}else if(type == 2){
//					move_ship(pl2, pos, att);
//					heal(pl2, pos, att);
//				}else if(type == 3){
//					move_ship(pl2, pos, att);
//					search(pl2, pos, att);
//				}
//			}
//			if(pl2 == 2){
//				int pos = def_grid2_.find_ship(def);
//				int type = def_grid2_.type_ship(pos);
//				if(type == 1){
//					fire(pl2, pos, att);
//				}else if(type == 2){
//					move_ship(pl2, pos, att);
//					heal(pl2, pos, att);
//				}else if(type == 3){
//					move_ship(pl2, pos, att);
//					search(pl2, pos, att);
//				}
//			}
//		}catch(std::invalid_argument& e){
//			valid  = false;
//		}
//	}
//}

void GamePlayer::make_move(int s){
     increment_turn();
    int computer=2;
    int player=1;
    std::string coord_nave;
    std::string coord_move;
    int nave;
    bool valid = true;
    bool check=true;
    while(valid==true){
        try{
            if(s == player){                //caso player
                while(check==true){
                try{
    
                std::cout<<"Inserisci coordinate azione"<<std::endl;
                std::cin>>coord_nave;
                util::to_upper(coord_nave);
                std::cin>>coord_move;
                util::to_upper(coord_move);
                Coord cNave{UCoord::from_string_to_coord(coord_nave)};
                Coord cMove{UCoord::from_string_to_coord(coord_move)};
                int pos = def_grid1_.find_ship(cNave);
    
                int type = def_grid1_.type_ship(pos);
                if(type == 1){
                    fire(player, pos, cMove);
                }else if(type == 2){
                    move_ship(player, pos, cMove);
                    heal(player, pos, cMove);
                }else if(type == 3){
                    move_ship(player, pos, cMove);
                    search(player, pos, cMove);
                }check=false;
                }catch(std::invalid_argument& e){std::cout<<"Non centro o coord...reinserire coordinate"<<std::endl;
                check=true;}
                }
    
            }
            else if(s == computer){             //caso computer
                nave=select_ship(computer);
                Coord cMove;
                cMove=UCoord::random_coord();
                //TEST
                std::cout<<cMove.X()<<"   "<<cMove.Y()<<std::endl;
                std::cout<<"Azione: "<<cMove.X()<<" "<<cMove.Y()<<std::endl;
                //FINE TEST
                int type = def_grid2_.type_ship(nave);
                if(type == 1){
                    fire(computer, nave, cMove);
                    //TEST
                    std::cout<<"Fuoco"<<std::endl;
                    //FINE TEST
                }else if(type == 2){
                    move_ship(computer, nave, cMove);
                    heal(computer, nave , cMove);
                    //TEST
                    std::cout<<"Move e HEal"<<std::endl;
                    //FINE TEST
                }else if(type == 3){
                    move_ship(computer, nave, cMove);
                    search(computer, nave, cMove);
                    //TEST
                    std::cout<<"Move e search"<<std::endl;
                    //FINE TEST
                }
            }
        }catch(std::invalid_argument& e){
            valid  = true;
        }
    valid=false;
    }
}


void GamePlayer::positioning_pc(void){
	int const pl = 2;
	int number_c = 1;
	int t = 1;
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
		}catch(std::invalid_argument& e){}
	}
}

int GamePlayer::select_ship(int player){
	return 0;
}

// std::pair<Coord,Coord> GamePlayer::select_move(int player){
// 	if(player == 1){
// 		bool end = false;
// 		std::string first;
// 		std::string second;
// 		Coord f{};
// 		Coord s{};
// 		while(!end){
// 			bool choice = false;
// 			while(!choice){
// 				std::cout << "Prossima mossa --> ";
// 				std::cin >> first >> second;
// 				choice = true;
// 				util::to_upper(first);
// 				if(first=="XX" && second=="XX"){
// 					std::cout << att_grid1_;
// 					choice = false;
// 				}
// 				if(first=="AA" && second=="AA"){
// 					att_grid1_.remove_detections();
// 					choice = false;
// 				}
// 				if(first=="BB" && second=="BB"){
// 					att_grid1_.remove_hit();
// 					choice = false;
// 				}
// 				if(first=="CC" && second=="CC"){
// 					att_grid1_.remove_water();
// 					choice = false;
// 				}
// 			}
// 			try{
// 				Coord f = UCoord::from_string_to_coord(first);
// 				Coord s = UCoord::from_string_to_coord(second);
				
// 				if(!end){
// 					std::cout << "Coordinate inserite non valide." << std::endl;
// 				}
// 			}catch(std::invalid_argument& e){
// 				std::cout << "Coordinate inserite non valide." << std::endl;
// 			}
// 		}
// 		std::pair<Coord, Coord> coord{f, s};
// 		return coord;
// 	}else{
// 		int x, y;
// 		srand(time(NULL));
// 		int ran = rand()%(def_grid2_.number_ship());
// 		x = def_grid2_.ship(ran)->center().X();
// 		y = def_grid2_.ship(ran)->center().Y();
// 		Coord first{x,y};
// 		Coord second = UCoord::random_coord();
// 		std::pair<Coord, Coord> coord{first, second};
// 		return coord;
// 	}
// }

void GamePlayer::start(){
//	std::cout << def_grid2_.number_ship() << std::endl;
//	std::cout << def_grid1_.ship(4)->center() << std::endl;
//	for(int i = 0; i<def_grid1_.number_ship(); i++){
//		std::cout << def_grid1_.ship(i)->center() << std::endl;
//		std::cout << def_grid1_.ship(i)->center().X() << std::endl;
//	}
    
    while(!end(false)){
        make_move(starter());
        if(starter()==1){
            std::cout<<"Mossa player fatta"<<std::endl;
            //TEST
            std::cout<<def_grid1_<<"      "<<att_grid1_<<std::endl;
            //FINE TEST
        }
        else{
            //TEST
            std::cout<<"Mossa computer fatta"<<std::endl;
            //FINE TEST
            std::cout<<def_grid2_<<"      "<<att_grid2_<<std::endl;
        }
        make_move((starter()%2)+1);
        if((starter()%2+1)==1){
            std::cout<<"Mossa player fatta"<<std::endl;
            //TEST
            std::cout<<def_grid1_<<"      "<<att_grid1_<<std::endl;
            //FINE TEST
        }
        else{
            std::cout<<"Mossa computer fatta"<<std::endl;
            //TEST
            std::cout<<def_grid2_<<"      "<<att_grid2_<<std::endl;
            //FINE TEST
        }
        
       
    }
}


}
