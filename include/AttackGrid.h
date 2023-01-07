// Autore:

#ifndef AttackGrid_h
#define AttackGrid_h

#include "Grid.h"

class AttackGrid : public Grid {
    public:
        void removeDetections(void);    //rimuove le Y
        void removeHit(void);           //rimuove le X
        void removeWater(void);         //rimuove le O
};
#endif /* AttackGrid_h */