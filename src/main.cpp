// Autore:
#include "GamePlayer.cpp"
#include "GamePc.cpp"
#include "Coord.cpp"
#include "AttackGrid.cpp"
#include "Battleship.cpp"
#include "DefenceGrid.cpp"
#include "ExplorationSubmarine.cpp"
#include "Game.cpp"
#include "Grid.cpp"
#include "HelpShip.cpp"
#include "Ship.cpp"

int main(int argc, char* argv[]) {
    std::cout << "OK" << std::endl;
    GamePc game{};
    game.start();
    return 0;
}