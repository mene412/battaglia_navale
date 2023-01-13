// Autore: Matteo Meneghin

#ifndef AttackGrid_h
#define AttackGrid_h

#include "Grid.h"

class AttackGrid : public Grid{
    public:
        AttackGrid(void);
        void remove_char(char c);
        void remove_detections(void);    //rimuove le Y
        void remove_hit(void);           //rimuove le X
        void remove_water(void);         //rimuove le O
        void add_char(char ch, Coord coord);
};

std::ostream& operator<<(std::ostream& os, AttackGrid a);
#endif /* AttackGrid_h */