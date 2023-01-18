// Autore: Matteo Meneghin

#ifndef DefenceGrid_h
#define DefenceGrid_h

#include "Grid.h"

class DefenceGrid : public Grid {
    public: 
        // Costruttore 
        DefenceGrid(void);

        // Metodi getter
        std::vector<Ship*> ships(void) {return ships_;}
        Ship* ship(int pos){ return ships_.at(pos);}
        int number_ship(void){ return ships_.size(); }

        // Controlla che le celle non siano già occupate da altre navi
        // ritorna true se sono libere
        bool check_position(Coord& a, Coord& b, int dim, int pos);
        bool check_position(Coord& a);
        bool check_position(std::vector<Coord>& coordinates, int pos);

        // Inserisce la nave nel vettore ship_, e scrive i char corrispondenti nella griglia
        void add_ship(Coord& front, Coord& back, int type);

        // Date le coordinate centrali della nave, ritorna la posizione nell'array ships_,
        // se non la trova lancia un errore
        int find_ship(Coord& x);

        // Ritorna il tipo della nave
        // 1 = corazzata, 2 = nave di supporto, 3 = sottomarino di esplorazione 
        int type_ship(int pos);
        int type_ship(Ship* ship);

        // Controlla se una nave è stata distrutta
        bool destroyed(int pos);

        // Riscrive la griglia, con i char in posizione corretta
        void reload(void);

        // Rimuove la nave dal vettore
        void remove_ship(int pos);

        // Segna nella griglia che la nave è stata colpita
        void hit(Coord& c);

        // Ritorna il vettore di Coord, data la Coord centrale e 
        // la posizione della nave nel vettore ships_
        std::vector<Coord> get_ship_coord(Coord& c, int pos);

        ~DefenceGrid(void);

    protected:
        std::vector<Ship*> ships_;
};

std::ostream& operator<<(std::ostream& os, DefenceGrid& a);

#endif /* DefenceGrid_h */