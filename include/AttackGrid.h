// Autore: Matteo Meneghin

#ifndef AttackGrid_h
#define AttackGrid_h

#include "Grid.h"

class AttackGrid : public Grid{
    public:
        // Costruttore
        AttackGrid(void);

        // Rimuove uno specifico char
        void remove_char(char c);

        // Rimuove le Y
        void remove_detections(void); 

        // Rimuove le X
        void remove_hit(void);    

        // Rimuove le O       
        void remove_water(void); 

        // Aggiunge un char in una specifica posizione   
        void add_char(char ch, Coord& coord);
};

std::ostream& operator<<(std::ostream& os, AttackGrid& a);

#endif /* AttackGrid_h */