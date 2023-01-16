//  Autore: Matteo Meneghin

#ifndef ExplorationSubmarine_h
#define ExplorationSubmarine_h

#include "Ship.h"

class ExplorationSubmarine: public Ship {
    public:
        ExplorationSubmarine(Coord& front);
        // controlla se le celle sono vuote, se true allora
        // cancella quelle vecchie, scrive quelle nuove e modifica i membri della ship
        void move(Coord& c);
        void set_coord(std::vector<Coord>& coordinates) override;
        void set_coord_from_center(Coord& cord) override;
    
    protected:
        // se trova celle colpite (char minuscoli) stampa 'X', 
        // se trova celle non danneggiate (char maiuscoli) stampa 'Y'
};
#endif /* ExplorationSubmarine_h */
