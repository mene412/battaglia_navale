//  Autore: Matteo Meneghin

#ifndef ExplorationSubmarine_h
#define ExplorationSubmarine_h

#include "Ship.h"

class ExplorationSubmarine: public Ship {
    public:
        // Costruttore
        ExplorationSubmarine(Coord& front);

        // Metodi setter
        void set_coord(std::vector<Coord>& coordinates) override;
        void set_coord_from_center(Coord& cord) override;
        
        // Muove il sottomarino in posizone c
        void move(Coord& c);
        
};
#endif /* ExplorationSubmarine_h */