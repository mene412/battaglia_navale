
#ifndef ExplorationSubmarine_h
#define ExplorationSubmarine_h

#include "../include/Ship.h"
#include "../include/ExplorationSubmarine.h"
#include "../include/AttackGrid.h"

class ExplorationSubmarine: public Ship
{
    public:
    ExplorationSubmarine(void);
    void move(void);
    void search(DefenceGrid enemyGrid, AttackGrid myGrid, int x, int y);
};
#endif /* ExplorationSubmarine_h */
