// Autore: Andrea Mutti

#include "../include/Replay.h"
#include "../include/Coord.h"
#include "../include/Ship.h"
#include "../include/Battleship.h"
#include "../include/HelpShip.h"
#include "../include/Explorationsubmarine.h"
#include <iostream>
#include <stdlib.h>

Replay::Replay(std::string file_log)
    : log{file_log}, def_grid_{DefenceGrid{}, DefenceGrid{}}, att_grid_{AttackGrid{}, AttackGrid{}}
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
    output << "Inizia il player " << first << "." << std::endl;
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
    def_grid_.first.ships().at(s).set_coord_center(UCoord::from_string_to_coord(tail));
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
    def_grid_.second.ships().at(s).set_coord_center(UCoord::from_string_to_coord(tail));
}

void Replay::take_ships(int player){
    if (player == 1){
            for(int i = 0; i<3; i++){
            std::string punta;
            std::string coda;
            log >> punta >> coda;
            def_grid_.first.add_ship(Battleship{UCoord::from_string_to_coord(punta), UCoord::from_string_to_coord(coda)});
        }
        for(int i = 0; i<3; i++){
            std::string punta;
            std::string coda;
            log >> punta >> coda;
            def_grid_.first.add_ship(HelpShip{UCoord::from_string_to_coord(punta), UCoord::from_string_to_coord(coda)});
        }
        for(int i = 0; i<2; i++){
            std::string punta;
            std::string coda;
            log >> punta >> coda;
            def_grid_.first.add_ship(ExplorationSubmarine{UCoord::from_string_to_coord(punta), UCoord::from_string_to_coord(coda)});
        }
    }else{
        for(int i = 0; i<3; i++){
            std::string punta;
            std::string coda;
            log >> punta >> coda;
            def_grid_.second.add_ship(Battleship{UCoord::from_string_to_coord(punta), UCoord::from_string_to_coord(coda)});
        }
        for(int i = 0; i<3; i++){
            std::string punta;
            std::string coda;
            log >> punta >> coda;
            def_grid_.second.add_ship(HelpShip{UCoord::from_string_to_coord(punta), UCoord::from_string_to_coord(coda)});
        }
        for(int i = 0; i<2; i++){
            std::string punta;
            std::string coda;
            log >> punta >> coda;
            def_grid_.second.add_ship(ExplorationSubmarine{UCoord::from_string_to_coord(punta), UCoord::from_string_to_coord(coda)});
        }
    }
}