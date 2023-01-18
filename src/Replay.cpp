// Autore: Andrea Mutti

#include "Replay.h"
#include <chrono>
#include <thread>

// Costruttore per il replay 
Replay::Replay(std::string file_log)    // riceve in ingresso un file di log
    : log_{file_log}, def_grid1_{}, def_grid2_{}, att_grid1_{}, att_grid2_{}, turn_{0}
{
    std::cout << "   Replay del file di log -> " << file_log << std::endl;
}

// Funzione start per replay a video
void Replay::start(void){   
    int first, second;
    log_ >> first;                              
    if(first==1){
        second = 2;             // legge il player iniziale
    }else if(first==2){
        second = 1;
    }else{
        throw std::runtime_error("File di log errato");
    }
    std::cout << "   Inizia il player " << first << "." << std::endl; 
    std::cout << "\n   Posizionamento iniziale\n" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(800));	// attesa di 800 millisecondi prima di procedere
    if(first == 1){
        take_ships(first);                                          // posiziona le navi e stampa le griglie di difesa iniziali
        def_grid1_.reload();
        std::cout << "  Player " << first << "\n" << def_grid1_;
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
        take_ships(second);
        def_grid2_.reload();
        std::cout << "  Player " << second << "\n" << def_grid2_;
    }else{
        take_ships(first);
        def_grid2_.reload();
        std::cout << "  Player " << first << "\n" << def_grid2_;
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        take_ships(second);
        def_grid1_.reload();
        std::cout << "  Player " << second << "\n" << def_grid1_;
    }

    while(!log_.eof()){         // fino a fine file
        increment_turn();       // incrementa e stampa il turno
        std::cout << "\n  Turno " << turn_  << std::endl;
        if(first==1){              // esegue la mossa, poi stampa la griglia di attacco e difesa, dopo aver aggiornato quella di difesa
            std::this_thread::sleep_for(std::chrono::milliseconds(800));
            move_first();
            def_grid1_.reload();
            std::cout << "  Player " << first << "\n" << def_grid1_;
            std::cout << att_grid1_;
            if(end()){           // se un player vince, termina l'esecuzione
                std::cout << "   Replay terminato." << std::endl;
                return;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(800));   
            move_second();
            def_grid2_.reload();
            std::cout << "  Player " << second << "\n" << def_grid2_;
            std::cout << att_grid2_;  
            if(end()){
                std::cout << "   Replay terminato." << std::endl;
                return;
            }          
        }else{
            std::this_thread::sleep_for(std::chrono::milliseconds(800));   
            move_second();
            def_grid2_.reload();
            std::cout << "  Player " << first << "\n" << def_grid2_;
            std::cout << att_grid2_;
            if(end()){
                std::cout << "   Replay terminato." << std::endl;
                return;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(800));   
            move_first();
            def_grid1_.reload();
            std::cout << "  Player " << second << "\n" << def_grid1_;
            std::cout << att_grid1_;
            if(end()){
                std::cout << "   Replay terminato." << std::endl;
                return;
            }
        }
    }
    turn_++;
    if(turn_ == MAX_TURNS){                         // caso pareggio
        std::cout << "\n|-----------|\n";
        std::cout << "| Pareggio! |";
        std::cout << "\n|-----------|\n" << std::endl;
        std::cout << "   Replay terminato." << std::endl;
    }else{
        throw std::runtime_error("File fi log errato");
    }
    
}

// Funzione start su file
void Replay::start(std::string file_output){    // riceve come parametro d'ingresso il file di output dove 
    std::ofstream output(file_output);          // oggetto ofstream per l'output
    int first, second;
    log_ >> first;
    if(first==1){                               // lettura di starter
        second = 2;
    }else if(first==2){
        second = 1;
    }else{
        throw std::runtime_error("File di log errato");
    }
    output << "   Inizia il player " << first << ".\n" << std::endl;
    if(first == 1){
        take_ships(first);              // posiziona le navi e stampa la griglia orrispondente dopo averla aggiornata
        def_grid1_.reload();
        output << "  Player " << first << "\n" << def_grid1_;

        take_ships(second);
        def_grid2_.reload();
        output << "  Player "<< second << "\n" << def_grid2_;
    }else{
        take_ships(first);
        def_grid2_.reload();
        output << "  Player " << first << "\n" << def_grid2_;

        take_ships(second);
        def_grid1_.reload();
        output << "  Player " << second << "\n" << def_grid1_;
    }
    while(!log_.eof()){
        increment_turn();                           // fino a fine file incrementa il turno ed esegue le mosse
        output << "Turno " << turn_  << std::endl;
        if(first==1){
            move_first();
            def_grid1_.reload();
            output << "  Player " << first << "\n" << def_grid1_;
            output << att_grid1_;
            if(end_file(output)){
                std::cout << "   Replay completato e salvato su file." << std::endl;
                output.close();
                return;
            }
            move_second();
            def_grid2_.reload();
            output << "  Player " << second << "\n" << def_grid2_;
            output << att_grid2_;
            if(end_file(output)){
                std::cout << "   Replay completato e salvato su file." << std::endl;
                output.close();
                return;
            }
        }else{
            move_second();
            def_grid2_.reload();
            output << "  Player " << first << "\n" << def_grid2_;
            output << att_grid2_;
            if(end_file(output)){
                std::cout << "   Replay completato e salvato su file." << std::endl;
                output.close();
                return;
            }
            move_first();
            def_grid1_.reload();
            output << "  Player " << second << "\n" << def_grid1_;
            output << att_grid1_;
            if(end_file(output)){
                std::cout << "   Replay completato e salvato su file." << std::endl;
                output.close();
                return;
            }
        }
    }
    turn_++;                            // caso pareggio
    if(turn_ == MAX_TURNS){
        output << "\n|-----------|\n";
        output << "| Pareggio! |";
        output << "\n|-----------|\n" << std::endl;
        std::cout << "   Replay completato e salvato su file." << std::endl;
        output.close();
    }else{
        output.close();
        throw std::runtime_error("File di log errato");
    }

}

// Posizionamento iniziale
void Replay::take_ships(int player){
    if(player == 1){
        int type;                   // tipo della nave
        for(int i = 0; i<3; i++){
            type = 1;
            std::string punta;
            std::string coda;       // 3 navi corazzata
            log_ >> punta >> coda;
            Coord p{UCoord::from_string_to_coord(punta)};
            Coord c{UCoord::from_string_to_coord(coda)};
            if(type == 1 && def_grid1_.check_position(p, c, 5, -1)){    // check_position, altrimenti file di log errato
                def_grid1_.add_ship(p, c, 1);
            }else{
                throw std::runtime_error("File di log errato");
            }
        }

        for(int i = 0; i<3; i++){
            type = 2;
            std::string punta;      // 3 navi di supporto
            std::string coda;
            log_ >> punta >> coda;
            Coord p{UCoord::from_string_to_coord(punta)};
            Coord c{UCoord::from_string_to_coord(coda)};
            if(type == 2 && def_grid1_.check_position(p, c, 3, -1)){
                def_grid1_.add_ship(p, c, 2);
            }else{
                throw std::runtime_error("File di log errato");
            }
        }
      
        for(int i = 0; i<2; i++){
            type = 3;
            std::string punta;
            std::string coda;
            log_ >> punta >> coda;      // due sottomarini
            if(punta != coda){          // se le due posizioni sono errate, errore
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
        for(int i = 0; i<3; i++){           // player due
            type = 1;
            std::string punta;
            std::string coda;
            log_ >> punta >> coda;
            Coord p{UCoord::from_string_to_coord(punta)};
            Coord c{UCoord::from_string_to_coord(coda)};
            if(type == 1 && def_grid2_.check_position(p, c, 5, -1)){
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
            if(type == 2 && def_grid2_.check_position(p, c, 3, -1)){
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

// Controllo mossa player 1
void Replay::move_first(void){
    if(log_.eof()){             // controlla che non sia finito il file 
        return;
    }
    std::string head, tail;     // riceve in ingresso le coordinate
    log_ >> head >> tail;
    Coord h{UCoord::from_string_to_coord(head)};
    Coord t{UCoord::from_string_to_coord(tail)};    // ecceziona invalid_argument lanciata se coordinate errate
    attack_first(h, t);         // attacco
}

// Controllo mossa player 2
void Replay::move_second(void){
    if(log_.eof()){             // controlla che non sia finito il file 
        return;
    }
    std::string head, tail;     // riceve in ingresso le coordinate
    log_ >> head >> tail;
    Coord h{UCoord::from_string_to_coord(head)};
    Coord t{UCoord::from_string_to_coord(tail)};    // ecceziona invalid_argument lanciata se coordinate errate
    attack_second(h, t);        // attacco
}

// Mossa player 1
void Replay::attack_first(Coord& a, Coord& b){  
    int pos = def_grid1_.find_ship(a);              // posizione della nave
    if(def_grid1_.type_ship(pos) == 1){             // controlla il tipo di nave
        attack(1, pos, b);
    }else if(def_grid1_.type_ship(pos) == 2){
        move_help(1, pos, b);
        heal(1, pos, b);
    }else if(def_grid1_.type_ship(pos) == 3){
        move_sub(1, pos, b);
        search(1, pos, b);
    }
}

// Mossa player 2
void Replay::attack_second(Coord& a, Coord& b){
    int pos = def_grid2_.find_ship(a);              // posizione della nave
    if(def_grid2_.type_ship(pos) == 1){             // controlla il tipo di nave
        attack(2, pos, b);
    }else if(def_grid2_.type_ship(pos) == 2){
        move_help(2, pos, b);
        heal(2, pos, b);
    }else if(def_grid2_.type_ship(pos) == 3){
        move_sub(2, pos, b);
        search(2, pos, b);
    }
}

// Equivalente di fire() in Game - attacca
void Replay::attack(int pl, int pos, Coord& c){
    if(pl == 1){
		for(int i = 0; i<def_grid2_.number_ship(); i++){        // scoore le navi
			for(int j = 0; j<def_grid2_.ship(i)->dim(); j++){   // scorre le coordinate
				if(def_grid2_.ship(i)->coord().at(j) == c){     // se una coordinata corrisponde
					att_grid1_.add_char('x', c);                // x nella griglia di attacco
					def_grid2_.ship(i) -> hit(c);               // funzione hit della nave
					def_grid2_.hit(c);                          // hit nella griglia
					if(def_grid2_.destroyed(i)){                // se distrutta
                        titanic(pl, i);                         // nave abbattuta
						def_grid2_.reload();                    // ricarica la griglia e return
					}
					return;
				}
			}
		}
    	att_grid1_.add_char('O', c);                            // se non è colpita, acqua (O)
	}else{
		for(int i = 0; i<def_grid1_.number_ship(); i++){
			for(int j = 0; j<def_grid1_.ship(i)->dim(); j++){
				if(def_grid1_.ship(i)->coord().at(j) == c){         // player 2
					att_grid2_.add_char('x', c);
					def_grid1_.ship(i) -> hit(c);
					def_grid1_.hit(c);
					if(def_grid1_.destroyed(i)){
                        titanic(pl, i);
						def_grid1_.reload();
					}
					return;
				}
			}
		}
    	att_grid2_.add_char('O', c);
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
		for(int i = 0; i<coord_heal.size(); i++){
			for(int k = 0; k<def_grid1_.number_ship(); k++){
				if(k!=pos){
					for(int j = 0; j<def_grid1_.ship(k)->coord().size(); j++){
						if(!def_grid1_.ship(k)->healed()){
							if(def_grid1_.ship(k)->coord().at(j) == coord_heal.at(i)){
								def_grid1_.ship(k) -> heal();
							}
						}
					}
				}
			}
		}
		def_grid1_.reload();
	}else{
		for(int i = 0; i<coord_heal.size(); i++){
			for(int k = 0; k<def_grid2_.number_ship(); k++){
				if(k!=pos){
					for(int j = 0; j<def_grid2_.ship(k)->coord().size(); j++){
						if(!def_grid2_.ship(k)->healed()){
							if(def_grid2_.ship(k)->coord().at(j) == coord_heal.at(i)){
								def_grid2_.ship(k) -> heal();
							}
						}
					}
				}
			}
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
        if(def_grid1_.check_position(c, pos)){
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
        if(def_grid2_.check_position(c, pos)){
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


// Nave affondata
void Replay::titanic(int pl, int pos){
    if(pl == 1){
		for(int i = 0; i<def_grid2_.ship(pos)->dim(); i++){                 // scorre le coordinate della nave
			att_grid1_.add_char('X', def_grid2_.ship(pos)->coord().at(i));  // aggiunge i colpi sulla griglia
		}
		def_grid2_.remove_ship(pos);                                        // rimuove la nave
		return;
	}else{
		for(int i = 0; i<def_grid1_.ship(pos)->dim(); i++){                 // player 2
			att_grid2_.add_char('X', def_grid1_.ship(pos)->coord().at(i));
		}
		def_grid1_.remove_ship(pos);
		return;
	}
}

// Verifica fine replay video
bool Replay::end(void){
    if(def_grid1_.number_ship() == 0){                          // verifica e scrive quale player ha vinto
        std::cout << "\n|--------------------|\n";
        std::cout << "| Player 2 ha vinto! |";
        std::cout << "\n|--------------------|\n" << std::endl;
        return true;
    }
    if(def_grid2_.number_ship() == 0){
        std::cout << "\n|--------------------|\n";
        std::cout << "| Player 1 ha vinto! |";
        std::cout << "\n|--------------------|\n" << std::endl;
        return true;
    }
    return false;
}

// Verifica fine replay file                
bool Replay::end_file(std::ofstream& file){                      // verifica e scrive quale player ha vinto
    if(def_grid1_.number_ship() == 0){
        file << "\n|--------------------|\n";
        file << "| Player 2 ha vinto! |";
        file << "\n|--------------------|\n" << std::endl;
        return true;
    }
    if(def_grid2_.number_ship() == 0){
        file << "\n|--------------------|\n";
        file << "| Player 1 ha vinto! |";
        file << "\n|--------------------|\n" << std::endl;
        return true;
    }
    return false;
}
