// Autore: Matteo Meneghin

#ifndef DefenceGrid_h
#define DefenceGrid_h

#include "Grid.h"

class DefenceGrid : public Grid {
    public: 
        DefenceGrid(void);
        //getter
        std::vector<Ship*>& ships(void){return ships_;}
        int number_ship(void){ return ships_.size(); }
        std::vector<Battleship*>& battle_ship(void);
        std::vector<HelpShip*>& help_ship(void);
        std::vector<ExplorationSubmarine*>& sub_ship(void);
        //controlla che le celle non siano già occupate da altre navi
        // ritorna true se sono libere
        bool check_position(std::vector<Coord> coordinates);   
        // inserisce la nave nel vettore di ship, e scrive i char corrispondenti nella griglia
        void add_ship(Ship* newShip);
        // date le coordinate centrali della nave, ritorna la posizione nell'array ships_,
        // se non la trova lancia un errore
        int find_ship(Coord x);
        // ritorna il tipo della nave
        // 1 = , 2= , 3 = 
        int type_ship(int pos);
        bool destroyed(int pos);
        void remove_ship(int pos);
        void reload(void);
        void hit(Coord c);

        ~DefenceGrid(void);

        // ritorna il vettore di Coord, data la Coord centrale e 
        // la posizione della nave nel vettore ships_
        std::vector<Coord> get_ship_coord(Coord c, int pos);

    protected:
        std::vector<Ship*> ships_;
};

std::ostream& operator<<(std::ostream& os, DefenceGrid a);

#endif /* DefenceGrid_h */
