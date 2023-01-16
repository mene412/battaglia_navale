// Autore:

#include "GamePc.cpp"
#include "GamePlayer.cpp"
#include "Coord.cpp"
#include "AttackGrid.cpp"
#include "Battleship.cpp"
#include "DefenceGrid.cpp"              //non dovrebbero essere .h gli include?
#include "ExplorationSubmarine.cpp"
#include "Game.cpp"
#include "Grid.cpp"
#include "HelpShip.cpp"
#include "Ship.cpp"

int main(int argc, char* argv[]) {
    std::srand(time(NULL));
    GamePlayer game{};
    game.start();
    return 0;
}
//MAIN CON COMMAND LINE ARGUMENTS

//int main(int argc, char* argv[]) {
//    std::srand(time(NULL));
//    if(argc==2){
//        if(!strcmp(argv[1], "pc")){
//            GamePlayer game{};
//            game.start();
//        }
//        else if(!strcmp(argv[1], "cc")){
 //           GamePc game{};
//            game.start();
//        }
//        else{
//            std::cout<<"Invalid argument"<<std::endl;
//        }
//    }
//    else if(argc==1)
//        std::cout<<"Command line argument required"<<std::endl;
//
//    else
//        std::cout<<"Too many command line arguments"<<std::endl;
    
//    return 0;
//}
