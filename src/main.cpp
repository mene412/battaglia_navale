// Autore: Gaia Soso

#include "GamePc.h"
#include "GamePlayer.h"


int main(int argc, char* argv[]) {
    std::srand(time(NULL));
    if(argc==2){
        std::string arg = argv[1];
        if(arg == "pc"){
            GamePlayer game{};
            game.start();
        }
        else if(arg == "cc"){
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
