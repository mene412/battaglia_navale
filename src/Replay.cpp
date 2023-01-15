// Autore: Andrea Mutti

#include "../include/Replay.h"

Replay::Replay(std::string file_log)
    : log{file_log}, def_grid1_{}, def_grid2_{}, att_grid1_{}, att_grid2_{}, turn_{0}
{
    std::cout << "Replay: " << file_log << std::endl;
}

void Replay::start(void){
    int first, second;
    log >> first;
    if(first==1){
        second = 2;
    }else if(first==2){
        second = 1;
    }
    //_sleep(1);
    std::cout << "Inizia il player " << first << "." << std::endl;
    //_sleep(1);
    if(first == 1){
        take_ships(first);
        std::cout << def_grid1_;
        //_sleep(1);
        take_ships(second);
        std::cout << def_grid2_;
        //_sleep(1);
    }else{
        take_ships(first);
        std::cout << def_grid2_;
        //_sleep(1);
        take_ships(second);
        std::cout << def_grid1_;
        //_sleep(1);
    }

    while(!log.eof()){
        turn_++;
        if(first==1){
            move_first();
            std::cout << def_grid1_;
            std::cout << att_grid1_;
            //_sleep(1);
            move_second();
            std::cout << def_grid2_;
            std::cout << att_grid2_;
            //_sleep(1);
        }else{
            move_second();
            std::cout << def_grid1_;
            std::cout << att_grid1_;
            //_sleep(1);
            move_first();
            std::cout << def_grid2_;
            std::cout << att_grid2_;
            //_sleep(1);
        }
    }
    std::cout << "Replay terminato." << std::endl;
}

void Replay::start(std::string file_output){
    std::ofstream output(file_output);
    
    int first, second;
    log >> first;
    if(first==1){
        second = 2;
    }else if(first==2){
        second = 1;
    }
    output << "Inizia il player " << first << ".\n" << std::endl;
    if(first == 1){
        take_ships(first);
        output << def_grid1_;
        take_ships(second);
        output << def_grid2_;
    }else{
        take_ships(first);
        output << def_grid2_;
        take_ships(second);
        output << def_grid1_;
    }
    while(!log.eof()){
        turn_++;
        output << "Turno " << turn_  << std::endl;
        if(first==1){
            move_first();
            output << def_grid1_;
            output << att_grid1_;
            move_second();
            output << def_grid2_;
            output << att_grid2_;
        }else{
            move_second();
            output << def_grid1_;
            output << att_grid1_;
            move_first();
            output << def_grid2_;
            output << att_grid2_;
        }
    }
    std::cout << "Raplay completato e salvato su file." << std::endl;
}

void Replay::move_first(void){
    if(log.eof()){
        return;
    }
    std::string head, tail;
    log >> head >> tail;
    Coord h{UCoord::from_string_to_coord(head)};
    Coord t{UCoord::from_string_to_coord(tail)};
    int s = def_grid1_.find_ship(h);
    if(s==-1){
        throw std::invalid_argument("Errore");
    }
    def_grid1_.ship(s)->set_coord_center(t);
    attack_first(h, t);
}

void Replay::move_second(void){
    if(log.eof()){
        return;
    }
    std::string head, tail;
    log >> head >> tail;
    Coord h{UCoord::from_string_to_coord(head)};
    Coord t{UCoord::from_string_to_coord(tail)};
    int s = def_grid2_.find_ship(h);
    if(s==-1){
        throw std::invalid_argument("Errore");
    }
    def_grid2_.ship(s)->set_coord_center(t);
    attack_second(h, t);
}

void Replay::take_ships(int player){
    if (player == 1){
            for(int i = 0; i<3; i++){
            std::string punta;
            std::string coda;
            log >> punta >> coda;
            Coord p{UCoord::from_string_to_coord(punta)};
            Coord c{UCoord::from_string_to_coord(coda)};
            Battleship ship{p, c};
            Ship* s = &ship;
            def_grid1_.add_ship(c, c, 1);
        }
        for(int i = 0; i<3; i++){
            std::string punta;
            std::string coda;
            log >> punta >> coda;
            Coord p{UCoord::from_string_to_coord(punta)};
            Coord c{UCoord::from_string_to_coord(coda)};
            HelpShip ship{p, c};
            Ship* s = &ship;
            def_grid1_.add_ship(c , c, 2);
        }
        for(int i = 0; i<2; i++){
            std::string punta;
            std::string coda;
            log >> punta >> coda;
            Coord c{UCoord::from_string_to_coord(coda)};
            def_grid1_.add_ship(c, c, 3);
        }
    }else{
        for(int i = 0; i<3; i++){
            std::string punta;
            std::string coda;
            log >> punta >> coda;
            Coord p{UCoord::from_string_to_coord(punta)};
            Coord c{UCoord::from_string_to_coord(coda)};
            Battleship ship{Battleship{p, c}};
            Ship* s = &ship;
            def_grid2_.add_ship(p, c, 1);
        }
        for(int i = 0; i<3; i++){
            std::string punta;
            std::string coda;
            log >> punta >> coda;
            Coord p{UCoord::from_string_to_coord(punta)};
            Coord c{UCoord::from_string_to_coord(coda)};
            HelpShip ship{p, c};
            Ship* s = &ship;
            def_grid2_.add_ship(p, c, 2);
        }
        for(int i = 0; i<2; i++){
            std::string punta;
            std::string coda;
            log >> punta >> coda;
            Coord c{UCoord::from_string_to_coord(punta)};
            ExplorationSubmarine ship{c};
            Ship* s = &ship;
            def_grid2_.add_ship(c, c, 3);
        }
    }
}

void Replay::attack_first(Coord& a, Coord& b){
    int pos = position(def_grid1_, a);
    if(def_grid1_.type_ship(pos) == 1){
        attack(1, pos, b);
    }else if(def_grid1_.type_ship(pos) == 2){
        move_help(1, pos, b);
        heal(1, pos, b);
    }else if(def_grid1_.type_ship(pos) == 3){
        move_sub(1, pos, b);
        exploration(1, pos, b);
    }
}



void Replay::attack_second(Coord& a, Coord& b){
    int pos = position(def_grid2_, a);
    if(def_grid1_.type_ship(pos) == 1){
        attack(2, pos, b);
    }else if(def_grid2_.type_ship(pos) == 2){
        move_help(2, pos, b);
        heal(2, pos, b);
    }else if(def_grid2_.type_ship(pos) == 3){
        move_sub(2, pos, b);
        exploration(2, pos, b);
    }
}

void Replay::attack(int pl, int pos, Coord& c){
    if(pl = 1){
		for(int i = 0; i<def_grid2_.number_ship(); i++){
			for(int j = 0; j<def_grid2_.ship(i)->dim(); j++){
				if(def_grid2_.ship(i)->coord().at(j) == c){
					att_grid1_.add_char('x', c);
					def_grid2_.ship(i) -> hit(c);
					def_grid2_.hit(c);
					if(def_grid2_.destroyed(i)){
						def_grid2_.reload();
					}
					return;
				}
			}
		}
    	att_grid1_.add_char('o', c);
	}else{
		for(int i = 0; i<def_grid1_.number_ship(); i++){
			for(int j = 0; j<def_grid1_.ship(i)->dim(); j++){
				if(def_grid1_.ship(i)->coord().at(j) == c){
					att_grid2_.add_char('x', c);
					def_grid1_.ship(i) -> hit(c);
					def_grid1_.hit(c);
					if(def_grid1_.destroyed(i)){
						def_grid1_.reload();
					}
					return;
				}
			}
		}
    	att_grid1_.add_char('o', c);
    }
}

void Replay::heal(int pl, int pos, Coord& c){
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

void move_help(int pl, int pos, Coord& b){

}

void move_sub(int pl, int pos, Coord& b){

}

void exploration(int pl, int pos, Coord& b){

}


int Replay::position(DefenceGrid& def_grid, Coord& c){
    for(int i = 0; i<def_grid.number_ship(); i++){
        if(def_grid.ship(i)->center()==c){
            return i;
        }
    }
    throw std::invalid_argument("Errore");
}
