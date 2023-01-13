// Autore:
#include "Ship.h"
#include "Battleship.h"
#include "DefenceGrid.h"
#include "AttackGrid.h"
#include "Grid.h"
#include <vector>

Battleship::Battleship(Coord front, Coord back)
    : Ship{front, back}
{
    dim_= 5;
    armor_= 5;
    distance_ = 2;
}
