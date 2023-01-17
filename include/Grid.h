// Autore: Matteo Meneghin

#ifndef Grid_h
#define Grid_h

#include "Battleship.h"
#include "ExplorationSubmarine.h"
#include "HelpShip.h"

class Grid {
    public:
        // Costruttore
        Grid(void);

        // Metodi getter
        int dimension(void){ return sizeof(grid_);}
        char get_char(Coord& c);

        // Controlla se uno specifico char sia in una specifica posizione
        bool is_in_grid(char ch, Coord& c);

        // Inserisce un char in una specifica posizione
        void insert_char(char ch, Coord& c);

        // Stampa la griglia
        std::string print_grid(void);

        // Rimuove tutti i char dalla griglia
        void flush_grid(void);

        virtual ~Grid(void){};
        
    protected:    
        char grid_[12][12];
};

std::ostream& operator<<(std::ostream& os, Grid& a);

#endif /* Grid_h */