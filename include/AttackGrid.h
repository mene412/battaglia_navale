// Autore: Matteo Meneghin

#ifndef AttackGrid_h
#define AttackGrid_h

#include "Grid.h"

class AttackGrid : public Grid {
    public:
        void removeChar(char c);
        void removeDetections(void);    //rimuove le Y
        void removeHit(void);           //rimuove le X
        void removeWater(void);         //rimuove le O
};

std::ostream& operator<<(std::ostream& os, AttackGrid a);
#endif /* AttackGrid_h */