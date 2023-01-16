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
   if(argc==2){
       if(argv[1] == "pc"){
           GamePlayer game{};
           game.start();
       }
       else if(argv[1] == "cc"){
           GamePc game{};
           game.start();
       }
       else{
           std::cout<<"Invalid argument"<<std::endl;
       }
   }
   else if(argc==1)
       std::cout<<"Command line argument required.\nwrite cc - game computer v computer\nor pc - game player v computer"<<std::endl;

   else
       std::cout<<"Too many command line arguments.\nwrite cc - game computer v computer\nor pc - game player v computer"<<std::endl;
    
   return 0;
}
