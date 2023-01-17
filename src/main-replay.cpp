// Autore: Andrea Mutti

#include "../include/Replay.h"
#include "Replay.cpp"
#include "Coord.cpp"
#include "AttackGrid.cpp"
#include "Battleship.cpp"
#include "DefenceGrid.cpp"
#include "ExplorationSubmarine.cpp"
#include "Game.cpp"
#include "Grid.cpp"
#include "HelpShip.cpp"
#include "Ship.cpp"

int main(int argc, char* argv[]){
    try{
        if(argc == 3){
            std::string vof = argv[1];
            std::string arg = argv[2];
            if(vof == "v"){
                Replay replay{arg};
                replay.start();
            }
            else if(vof == "f"){
                std::cout << "Argomenti da linea di comando insufficienti --> main-replay f [nome_file_log] [nome_file_output_replay]\n" << std::endl;
            }
            else{
                std::cout << "Argomenti errati. La sintassi corretta puo' essere di due tipi.\n1 --> main-replay v [nome_file_log]   ->   replay del file di log indicato a schermo\n2 --> main-replay f [nome_file_log] [nome_file_output_replay]   ->   replay del file di log indicato su file\n" << std::endl; 
            }
        }else if(argc == 4){
            std::string vof = argv[1];
            std::string arg = argv[2];
            std::string file = argv[3];
            if(vof == "f"){
                Replay replay{arg};
                replay.start(file);
            }
            else if(vof == "v"){
                std::cout << "Argomenti da linea di comando non esatti --> main-replay v [nome_file_log]\n" << std::endl;
            }
            else{
                std::cout << "Argomenti errati. La sintassi corretta puo' essere di due tipi.\n1 --> main-replay v [nome_file_log]   ->   replay del file di log indicato a schermo\n2 --> main-replay f [nome_file_log] [nome_file_output_replay]   ->   replay del file di log indicato su file\n" << std::endl; 
            }
        }else if(argc > 4){
            std::cout << "Argomenti errati. La sintassi corretta puo' essere di due tipi.\n1 --> main-replay v [nome_file_log]   ->   replay del file di log indicato a schermo\n2 --> main-replay f [nome_file_log] [nome_file_output_replay]   ->   replay del file di log indicato su file\n" << std::endl; 
        }else if(argc == 2){
            std::string arg = argv[1];
            if(arg == "h"){
                std::cout << "Programma per la visualizzazione di un replay di una partita di Battaglia navale. La sintassi corretta puo' essere di due tipi.\n1 --> main-replay v [nome_file_log]   ->   replay del file di log indicato a schermo\n2 --> main-replay f [nome_file_log] [nome_file_output_replay]   ->   replay del file di log indicato su file\n" << std::endl; 
            }else{
                std::cout << "Argomenti errati. La sintassi corretta puo' essere di due tipi.\n1 --> main-replay v [nome_file_log]   ->   replay del file di log indicato a schermo\n2 --> main-replay f [nome_file_log] [nome_file_output_replay]   ->   replay del file di log indicato su file\n" << std::endl; 
            }
        }else if(argc < 2){
            std::cout << "Argomenti errati. La sintassi corretta puo' essere di due tipi.\n1 --> main-replay v [nome_file_log]   ->   replay del file di log indicato a schermo\n2 --> main-replay f [nome_file_log] [nome_file_output_replay]   ->   replay del file di log indicato su file\n" << std::endl; 
        }  
    }catch(std::invalid_argument& e){
        std::cerr << "File di log non valido.\n" << std::endl;
        return 1;
    }catch(std::fstream::failure& e){
        std::cerr << "File di input o output non valido.\n" << std::endl;
        return 1;
    }catch(std::runtime_error& e){
        std::cerr << "File di log errato.\n" << std::endl;
        return 1;
    }
    return 0;
}