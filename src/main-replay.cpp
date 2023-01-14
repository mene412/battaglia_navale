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
    Replay replay{"log.txt"};
    replay.start();
    return 0;
}