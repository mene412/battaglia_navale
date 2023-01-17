// Autore: Andrea Mutti

#include "../include/Replay.h"

Replay::Replay(std::string file_log)
    : log_{file_log}, def_grid1_{}, def_grid2_{}, att_grid1_{}, att_grid2_{}, turn_{0}
{
    std::cout << "   Replay del file di log -> " << file_log << std::endl;
}

void Replay::start(void){
    int first, second;
    log_ >> first;
    if(first==1){
        second = 2;
    }else if(first==2){
        second = 1;
    }else{
        throw std::runtime_error("File di log errato");
    }
    std::cout << "   Inizia il player " << first << "." << std::endl;
    std::cout << "\n   Posizionamento iniziale\n" << std::endl;
    //_sleep(1);
    if(first == 1){
        take_ships(first);
        def_grid1_.reload();
        std::cout << "Player " << first << "\n" << def_grid1_;
        //_sleep(1);
        take_ships(second);
        def_grid2_.reload();
        std::cout << "Player " << second << "\n" << def_grid2_;
    }else{
        take_ships(first);
        def_grid2_.reload();
        std::cout << "Player " << first << "\n" << def_grid2_;
        //_sleep(1);
        take_ships(second);
        def_grid1_.reload();
        std::cout << "Player " << second << "\n" << def_grid1_;
    }

    while(!log_.eof()){
        increment_turn();
        std::cout << "\nTurno " << turn_  << std::endl;
        if(first==1){
            //_sleep(1);
            move_first();
            def_grid1_.reload();
            std::cout << "Player " << first << "\n" << def_grid1_;
            std::cout << att_grid1_;
            //_sleep(1);
            
            move_second();
            def_grid2_.reload();
            std::cout << "Player " << second << "\n" << def_grid2_;
            std::cout << att_grid2_;            
        }else{
            //_sleep(1);
            move_second();
            def_grid2_.reload();
            std::cout << "Player " << first << "\n" << def_grid2_;
            std::cout << att_grid2_;
            //_sleep(1);
            
            move_first();
            def_grid1_.reload();
            std::cout << "Player " << second << "\n" << def_grid1_;
            std::cout << att_grid1_;
        }
    }
    std::cout << "   Replay terminato." << std::endl;
}

void Replay::start(std::string file_output){
    std::ofstream output(file_output);
    int first, second;
    log_ >> first;
    if(first==1){
        second = 2;
    }else if(first==2){
        second = 1;
    }else{
        throw std::runtime_error("File di log errato");
    }
    output << "   Inizia il player " << first << ".\n" << std::endl;
    if(first == 1){
        take_ships(first);
        def_grid1_.reload();
        output << def_grid1_;

        take_ships(second);
        def_grid2_.reload();
        output << def_grid2_;
    }else{
        take_ships(first);
        def_grid2_.reload();
        output << def_grid2_;

        take_ships(second);
        def_grid1_.reload();
        output << def_grid1_;
    }
    while(!log_.eof()){
        increment_turn();
        output << "Turno " << turn_  << std::endl;
        if(first==1){
            move_first();
            def_grid1_.reload();
            output << def_grid1_;
            output << att_grid1_;
            move_second();
            def_grid2_.reload();
            output << def_grid2_;
            output << att_grid2_;
        }else{
            move_second();
            def_grid2_.reload();
            output << def_grid1_;
            output << att_grid1_;
            move_first();
            def_grid1_.reload();
            output << def_grid2_;
            output << att_grid2_;
        }
    }
    std::cout << "   Replay completato e salvato su file." << std::endl;
}

void Replay::move_first(void){
    if(log_.eof()){
        return;
    }
    std::string head, tail;
    log_ >> head >> tail;
    Coord h{UCoord::from_string_to_coord(head)};
    Coord t{UCoord::from_string_to_coord(tail)};
    attack_first(h, t);
}

void Replay::move_second(void){
    if(log_.eof()){
        return;
    }
    std::string head, tail;
    log_ >> head >> tail;
    Coord h{UCoord::from_string_to_coord(head)};
    Coord t{UCoord::from_string_to_coord(tail)};
    attack_second(h, t);
}

void Replay::take_ships(int player){
    if(player == 1){
        int type;
        for(int i = 0; i<3; i++){
            type = 1;
            std::string punta;
            std::string coda;
            log_ >> punta >> coda;
            Coord p{UCoord::from_string_to_coord(punta)};
            Coord c{UCoord::from_string_to_coord(coda)};
            if(type == 1 && def_grid1_.check_position(p, c, 5)){
                def_grid1_.add_ship(p, c, 1);
            }else{
                throw std::runtime_error("File di log errato");
            }
        }

        for(int i = 0; i<3; i++){
            type = 2;
            std::string punta;
            std::string coda;
            log_ >> punta >> coda;
            Coord p{UCoord::from_string_to_coord(punta)};
            Coord c{UCoord::from_string_to_coord(coda)};
            if(type == 2 && def_grid1_.check_position(p, c, 3)){
                def_grid1_.add_ship(p, c, 2);
            }else{
                throw std::runtime_error("File di log errato");
            }
        }
      
        for(int i = 0; i<2; i++){
            type = 3;
            std::string punta;
            std::string coda;
            log_ >> punta >> coda;
            if(punta != coda){
                throw std::runtime_error("File di log errato");
            }
            Coord c{UCoord::from_string_to_coord(coda)};
            if(type == 3 && def_grid1_.check_position(c)){
                def_grid1_.add_ship(c, c, 3);
            }else{
                throw std::runtime_error("File di log errato");
            }
        }
    }else{
        int type;
        for(int i = 0; i<3; i++){
            type = 1;
            std::string punta;
            std::string coda;
            log_ >> punta >> coda;
            Coord p{UCoord::from_string_to_coord(punta)};
            Coord c{UCoord::from_string_to_coord(coda)};
            if(type == 1 && def_grid2_.check_position(p, c, 5)){
                def_grid2_.add_ship(p, c, 1);
            }else{
                throw std::runtime_error("File di log errato");
            }
        }
        for(int i = 0; i<3; i++){
            type = 2;
            std::string punta;
            std::string coda;
            log_ >> punta >> coda;
            Coord p{UCoord::from_string_to_coord(punta)};
            Coord c{UCoord::from_string_to_coord(coda)};
            if(type == 2 && def_grid2_.check_position(p, c, 3)){
                def_grid2_.add_ship(p, c, 2);
            }else{
                throw std::runtime_error("File di log errato");
            }
        }
        for(int i = 0; i<2; i++){
            type = 3;
            std::string punta;
            std::string coda;
            log_ >> punta >> coda;
            if(punta != coda){
                throw std::runtime_error("File di log errato");
            }
            Coord c{UCoord::from_string_to_coord(punta)};
            if(type == 3 && def_grid2_.check_position(c)){
                def_grid2_.add_ship(c, c, 3);
            }else{
                throw std::runtime_error("File di log errato");
            }
        }
    }
}

void Replay::attack_first(Coord& a, Coord& b){  
    int pos = def_grid1_.find_ship(a);
    if(def_grid1_.type_ship(pos) == 1){
        attack(1, pos, b);
    }else if(def_grid1_.type_ship(pos) == 2){
        move_help(1, pos, b);
        heal(1, pos, b);
    }else if(def_grid1_.type_ship(pos) == 3){
        move_sub(1, pos, b);
        search(1, pos, b);
    }
}



void Replay::attack_second(Coord& a, Coord& b){
    int pos = def_grid2_.find_ship(a);
    if(def_grid2_.type_ship(pos) == 1){
        attack(2, pos, b);
    }else if(def_grid2_.type_ship(pos) == 2){
        move_help(2, pos, b);
        heal(2, pos, b);
    }else if(def_grid2_.type_ship(pos) == 3){
        move_sub(2, pos, b);
        search(2, pos, b);
    }
}

void Replay::attack(int pl, int pos, Coord& c){
    if(pl == 1){
		for(int i = 0; i<def_grid2_.number_ship(); i++){
			for(int j = 0; j<def_grid2_.ship(i)->dim(); j++){
				if(def_grid2_.ship(i)->coord().at(j) == c){
					att_grid1_.add_char('x', c);
					def_grid2_.ship(i) -> hit(c);
					def_grid2_.hit(c);
					if(def_grid2_.destroyed(i)){
                        titanic(pl, pos);
						def_grid2_.reload();
					}
					return;
				}
			}
		}
    	att_grid1_.add_char('O', c);
	}else{
		for(int i = 0; i<def_grid1_.number_ship(); i++){
			for(int j = 0; j<def_grid1_.ship(i)->dim(); j++){
				if(def_grid1_.ship(i)->coord().at(j) == c){
					att_grid2_.add_char('x', c);
					def_grid1_.ship(i) -> hit(c);
					def_grid1_.hit(c);
					if(def_grid1_.destroyed(i)){
                        titanic(pl, pos);
						def_grid1_.reload();
					}
					return;
				}
			}
		}
    	att_grid2_.add_char('O', c);
    }
}

void Replay::titanic(int pl, int pos){
    if(pl == 1){
		for(int i = 0; i<def_grid2_.ship(pos)->dim(); i++){
			att_grid1_.add_char('X', def_grid2_.ship(pos)->coord().at(i));
		}
		def_grid2_.remove_ship(pos);
		return;
	}else{
		for(int i = 0; i<def_grid1_.ship(pos)->dim(); i++){
			att_grid2_.add_char('X', def_grid1_.ship(pos)->coord().at(i));
		}
		def_grid1_.remove_ship(pos);
		return;
	}
}

void Replay::heal(int pl, int pos, Coord& c){
    std::vector<Coord> coord_heal;
	for(int i = 0; i<3; i++){
		try{
			Coord cord{c.X()-1, c.Y()-1+i};
			coord_heal.push_back(cord);
		}catch(std::invalid_argument& e){}
	}
	for(int i = 0; i<3; i++){
		try{
			Coord cord{c.X(), c.Y()-1+i};
			coord_heal.push_back(cord);
		}catch(std::invalid_argument& e){}
	}
	for(int i = 0; i<3; i++){
		try{
			Coord cord{c.X()+1, c.Y()-1+i};
			coord_heal.push_back(cord);
		}catch(std::invalid_argument& e){}
	}
	if(pl == 1){
		std::vector<Coord> coord = def_grid1_.ship(pos) -> coord();
		bool heal = true;
		for(int i = 0; i<coord_heal.size(); i++){
			for(int j = 0; j<coord.size(); j++){
				if(coord_heal.at(i) == coord.at(j)){
					heal = false;
				}
			}
			if(heal){
                try{
                    int p = def_grid1_.find_ship(coord_heal.at(i));
				    if(!def_grid1_.ship(p) -> healed()){
					    def_grid1_.ship(p) -> heal();
				    }
                }catch(std::invalid_argument& e){}
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
                try{
                    int p = def_grid2_.find_ship(coord_heal.at(i));
				    if(!def_grid2_.ship(p) -> healed()){
					    def_grid2_.ship(p) -> heal();
				    }
                }catch(std::invalid_argument& e){}
			}
            heal = true;
		}
		def_grid2_.reload();
	}
}

void Replay::move_help(int pl, int pos, Coord& b){
    if(pl == 1){
        std::vector<Coord> c;
        if(def_grid1_.ship(pos) -> orizzontal()){
            Coord cord{b.X(), b.Y()-1};
            c.push_back(cord);
            cord = b;
            c.push_back(cord);
            cord = Coord{b.X(), b.Y()+1};
            c.push_back(cord);
        }else{
            Coord cord{b.X()-1, b.Y()};
            c.push_back(cord);
            cord = b;
            c.push_back(cord);
            cord = Coord{b.X()+1, b.Y()};
            c.push_back(cord);
        }
        if(def_grid1_.check_position(c)){
            HelpShip* ship = dynamic_cast<HelpShip*>(def_grid1_.ship(pos));
            ship -> move(b);
            def_grid1_.reload();
        }else{
            throw std::runtime_error("File di log errato");
        }
    }else{
        std::vector<Coord> c;
        if(def_grid2_.ship(pos) -> orizzontal()){
            Coord cord{b.X(), b.Y()-1};
            c.push_back(cord);
            cord = b;
            c.push_back(cord);
            cord = Coord{b.X(), b.Y()+1};
            c.push_back(cord);
        }else{
            Coord cord{b.X()-1, b.Y()};
            c.push_back(cord);
            cord = b;
            c.push_back(cord);
            cord = Coord{b.X()+1, b.Y()};
            c.push_back(cord);
        }
        if(def_grid2_.check_position(c)){
            HelpShip* ship = dynamic_cast<HelpShip*>(def_grid2_.ship(pos));
            ship -> move(b);
            def_grid2_.reload();
        }else{
            throw std::runtime_error("File di log errato");
        }
    }
}

void Replay::move_sub(int pl, int pos, Coord& b){
    if(pl == 1){
        if(def_grid1_.check_position(b)){
            ExplorationSubmarine* ship = dynamic_cast<ExplorationSubmarine*>(def_grid1_.ship(pos));
            ship -> move(b);
            def_grid1_.reload();
        }else{
            throw std::runtime_error("File di log errato");
        }
    }else{
        if(def_grid2_.check_position(b)){
            ExplorationSubmarine* ship = dynamic_cast<ExplorationSubmarine*>(def_grid2_.ship(pos));
            ship -> move(b);
            def_grid2_.reload();
        }else{
            throw std::runtime_error("File di log errato");
        }
    }
}

void Replay::search(int pl, int pos, Coord& b){
    if(pl == 1){
		std::vector<Coord> coord;
		for(int i = 0; i<5; i++){
			try{
				Coord temp{b.X()-2, b.Y()-2+i};
				coord.push_back(temp);
			}catch(std::invalid_argument& e){}
		}
		for(int i = 0; i<5; i++){
			try{
				Coord temp{b.X()-1, b.Y()-2+i};
				coord.push_back(temp);
			}catch(std::invalid_argument& e){}
		}
		for(int i = 0; i<5; i++){
			try{
				Coord temp{b.X(), b.Y()-2+i};
				coord.push_back(temp);
			}catch(std::invalid_argument& e){}
		}
		for(int i = 0; i<5; i++){
			try{
				Coord temp{b.X()+1, b.Y()-2+i};
				coord.push_back(temp);
			}catch(std::invalid_argument& e){}
		}
		for(int i = 0; i<5; i++){
			try{
				Coord temp{b.X()+2, b.Y()-2+i};
				coord.push_back(temp);
			}catch(std::invalid_argument& e){}
		}

		for(int i = 0; i<coord.size(); i++){
			try{
				for(int j = 0; j < def_grid2_.number_ship(); j++){
					for(int k = 0; k < def_grid2_.ship(j)->coord().size(); k++){
						if(coord.at(i) == def_grid2_.ship(j) -> coord().at(k)){
							att_grid1_.add_char('Y', coord.at(i));
						}
					}
				}
			}catch(std::invalid_argument& e){}
		}
	}else{
		std::vector<Coord> coord;
		for(int i = 0; i<5; i++){
			try{
				Coord temp{b.X()-2, b.Y()-2+i};
				coord.push_back(temp);
			}catch(std::invalid_argument& e){}
		}
		for(int i = 0; i<5; i++){
			try{
				Coord temp{b.X()-1, b.Y()-2+i};
				coord.push_back(temp);
			}catch(std::invalid_argument& e){}
		}
		for(int i = 0; i<5; i++){
			try{
				Coord temp{b.X(), b.Y()-2+i};
				coord.push_back(temp);
			}catch(std::invalid_argument& e){}
		}
		for(int i = 0; i<5; i++){
			try{
				Coord temp{b.X()+1, b.Y()-2+i};
				coord.push_back(temp);
			}catch(std::invalid_argument& e){}
		}
		for(int i = 0; i<5; i++){
			try{
				Coord temp{b.X()+2, b.Y()-2+i};
				coord.push_back(temp);
			}catch(std::invalid_argument& e){}
		}

		for(int i = 0; i<coord.size(); i++){
			try{
				for(int j = 0; j < def_grid1_.number_ship(); j++){
					for(int k = 0; k < def_grid1_.ship(j)->coord().size(); k++){
						if(coord.at(i) == def_grid1_.ship(j) -> coord().at(k)){
							att_grid2_.add_char('Y', coord.at(i));
						}
					}
				}
			}catch(std::invalid_argument& e){}
		}
	}
}   