//  Autore: Matteo Meneghin

#ifndef ExplorationSubmarine_h
#define ExplorationSubmarine_h

#include "Ship.h"
#include "AttackGrid.h"
#include "DefenceGrid.h"
#include "Coord.h"

class ExplorationSubmarine: public Ship {
    public:
        ExplorationSubmarine(Coord front, Coord back);
        void move(DefenceGrid& myGrid, Coord c);
        // se trova celle colpite (char minuscoli) stampa 'X', 
        // se trova celle non danneggiate (char maiuscoli) stampa 'Y'
        void search(DefenceGrid& enemyGrid, AttackGrid& myGrid, Coord c);
};
#endif /* ExplorationSubmarine_h */
