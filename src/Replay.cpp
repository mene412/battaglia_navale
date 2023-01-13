// Autore: Andrea Mutti

#include "../include/Replay.h"

Replay::Replay(std::string file_log)
    : log{file_log}, def_grid_{DefenceGrid{}, DefenceGrid{}}, att_grid_{AttackGrid{}, AttackGrid{}}, turn_{0}
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
    _sleep(1);
    std::cout << "Inizia il player " << first << "." << std::endl;
    _sleep(1);
    if(first == 1){
        take_ships(first);
        std::cout << def_grid_.first;
        _sleep(1);
        take_ships(second);
        std::cout << def_grid_.second;
        _sleep(1);
    }else{
        take_ships(first);
        std::cout << def_grid_.second;
        _sleep(1);
        take_ships(second);
        std::cout << def_grid_.first;
        _sleep(1);
    }

    while(!log.eof()){
        turn_++;
        if(first==1){
            move_first();
            std::cout << def_grid_.first;
            std::cout << att_grid_.first;
            _sleep(1);
            move_second();
            std::cout << def_grid_.second;
            std::cout << att_grid_.second;
            _sleep(1);
        }else{
            move_second();
            std::cout << def_grid_.first;
            std::cout << att_grid_.first;
            _sleep(1);
            move_first();
            std::cout << def_grid_.second;
            std::cout << att_grid_.second;
            _sleep(1);
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
        output << def_grid_.first;
        take_ships(second);
        output << def_grid_.second;
    }else{
        take_ships(first);
        output << def_grid_.second;
        take_ships(second);
        output << def_grid_.first;
    }
    while(!log.eof()){
        turn_++;
        output << "Turno " << turn_  << std::endl;
        if(first==1){
            move_first();
            output << def_grid_.first;
            output << att_grid_.first;
            move_second();
            output << def_grid_.second;
            output << att_grid_.second;
        }else{
            move_second();
            output << def_grid_.first;
            output << att_grid_.first;
            move_first();
            output << def_grid_.second;
            output << att_grid_.second;
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
    int s = def_grid_.first.find_ship(UCoord::from_string_to_coord(head));
    if(s==-1){
        throw std::invalid_argument("Errore");
    }
    def_grid_.first.ships().at(s)->set_coord_center(UCoord::from_string_to_coord(tail));
    attack_first(UCoord::from_string_to_coord(head), UCoord::from_string_to_coord(tail));
}

void Replay::move_second(void){
    if(log.eof()){
        return;
    }
    std::string head, tail;
    log >> head >> tail;
    int s = def_grid_.second.find_ship(UCoord::from_string_to_coord(head));
    if(s==-1){
        throw std::invalid_argument("Errore");
    }
    def_grid_.second.ships().at(s)->set_coord_center(UCoord::from_string_to_coord(tail));
    attack_second(UCoord::from_string_to_coord(head), UCoord::from_string_to_coord(tail));
}

void Replay::take_ships(int player){
    if (player == 1){
            for(int i = 0; i<3; i++){
            std::string punta;
            std::string coda;
            log >> punta >> coda;
            Battleship ship{Battleship{UCoord::from_string_to_coord(punta), UCoord::from_string_to_coord(coda)}};
            def_grid_.first.add_ship(ship);
        }
        for(int i = 0; i<3; i++){
            std::string punta;
            std::string coda;
            log >> punta >> coda;
            HelpShip ship{UCoord::from_string_to_coord(punta), UCoord::from_string_to_coord(coda)};
            def_grid_.first.add_ship(ship);
        }
        for(int i = 0; i<2; i++){
            std::string punta;
            std::string coda;
            log >> punta >> coda;
            ExplorationSubmarine ship{UCoord::from_string_to_coord(punta), UCoord::from_string_to_coord(coda)};
            def_grid_.first.add_ship(ship);
        }
    }else{
        for(int i = 0; i<3; i++){
            std::string punta;
            std::string coda;
            log >> punta >> coda;
            Battleship ship{Battleship{UCoord::from_string_to_coord(punta), UCoord::from_string_to_coord(coda)}};
            def_grid_.second.add_ship(ship);
        }
        for(int i = 0; i<3; i++){
            std::string punta;
            std::string coda;
            log >> punta >> coda;
            HelpShip ship{UCoord::from_string_to_coord(punta), UCoord::from_string_to_coord(coda)};
            def_grid_.second.add_ship(ship);
        }
        for(int i = 0; i<2; i++){
            std::string punta;
            std::string coda;
            log >> punta >> coda;
            ExplorationSubmarine ship{UCoord::from_string_to_coord(punta), UCoord::from_string_to_coord(coda)};
            def_grid_.second.add_ship(ship);
        }
    }
}

void Replay::attack_first(Coord a, Coord b){
    int pos = position(def_grid_.first, a);
    if(def_grid_.first.type_ship(pos) == 1){
        attack(1, pos, b);
    }else if(def_grid_.first.type_ship(pos) == 2){
        move_help(1, pos, b);
        heal(1, pos, b);
    }else if(def_grid_.first.type_ship(pos) == 3){
        move_sub(1, pos, b);
        exploration(1, pos, b);
    }
}



void Replay::attack_second(Coord a, Coord b){
    int pos = position(def_grid_.second, a);
    if(def_grid_.first.type_ship(pos) == 1){
        attack(1, pos, b);
    }else if(def_grid_.second.type_ship(pos) == 2){
        move_help(1, pos, b);
        heal(1, pos, b);
    }else if(def_grid_.second.type_ship(pos) == 3){
        move_sub(1, pos, b);
        exploration(1, pos, b);
    }
}

int Replay::position(DefenceGrid& def_grid, Coord c){
    for(int i = 0; i<def_grid.number_ship(); i++){
        if(def_grid.ships().at(i)->center()==c){
            return i;
        }
    }
    throw std::invalid_argument("Errore");
}
