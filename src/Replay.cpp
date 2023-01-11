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
    take_ships(first);
    take_ships(second);
    _sleep(1);
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
    take_ships(first);
    if(first == 1){
        take_ships(first);
        output << def_grid_.first;
    }else{
        take_ships(first);
    }
    
    take_ships(second);
}

void Replay::take_ships(int player){
    if (player == 1){
            for(int i = 0; i<3; i++){
            std::string punta;
            std::string coda;
            log >> punta >> coda;
            def_grid_.first.addShip(Battleship{UCoord::from_string_to_coord(punta), UCoord::from_string_to_coord(coda)});
        }

        for(int i = 0; i<3; i++){
            std::string punta;
            std::string coda;
            log >> punta >> coda;
            def_grid_.first.addShip(HelpShip{UCoord::from_string_to_coord(punta), UCoord::from_string_to_coord(coda)});
        }

        for(int i = 0; i<2; i++){
            std::string punta;
            std::string coda;
            log >> punta >> coda;
            def_grid_.first.addShip(ExplorationSubmarine{UCoord::from_string_to_coord(punta), UCoord::from_string_to_coord(coda)});
        }
    }else{
        for(int i = 0; i<3; i++){
            std::string punta;
            std::string coda;
            log >> punta >> coda;
            def_grid_.second.addShip(Battleship{UCoord::from_string_to_coord(punta), UCoord::from_string_to_coord(coda)});
        }

        for(int i = 0; i<3; i++){
            std::string punta;
            std::string coda;
            log >> punta >> coda;
            def_grid_.second.addShip(HelpShip{UCoord::from_string_to_coord(punta), UCoord::from_string_to_coord(coda)});
        }

        for(int i = 0; i<2; i++){
            std::string punta;
            std::string coda;
            log >> punta >> coda;
            def_grid_.second.addShip(ExplorationSubmarine{UCoord::from_string_to_coord(punta), UCoord::from_string_to_coord(coda)});
        }
    }
    
}