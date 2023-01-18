// Autore: Andrea Mutti

#ifndef REPLAY_H
#define REPLAY_H

#include <fstream>        // libreria fstream per gestire input di file log ed eventuale output
#include "DefenceGrid.h"
#include "AttackGrid.h"

class Replay{
    public:
        // Costruttore che accetta come parametro il file di log
        Replay(std::string file_log);   

        // Funzioni start per gestire tutto il replay
        void start(void);
        void start(std::string file_output);    // questa serve a salvare il replay in un file di output
        
        // Distruttore - chiude il file di log aperto
        ~Replay(){log_.close();}

    private:
        // Funzioni membro private
        void take_ships(int player);            // setta le navi iniziali
        
        // Controlla la validità della mossa
        void move_first(void);  
        void move_second(void);

        // Mossa del player
        void attack_first(Coord& a, Coord& b);
        void attack_second(Coord& a, Coord& b);

        // Mosse delle navi (molto simili alle funzioni in Game)
        void attack(int pl, int pos, Coord& c);
        void heal(int pl, int pos, Coord& c);
        void move_help(int pl, int pos, Coord& c);
        void move_sub(int pl, int pos, Coord& c);
        void search(int pl, int pos, Coord& c);
        void titanic(int pl, int pos);

        // Verificano la fine del file e indica chi ha vinto
        inline void increment_turn(){turn_++;}; // incrementa il turno
        bool end(void);
        bool end_file(std::ofstream& file);     // scrive su file chi ha vinto

        std::ifstream log_;                     // oggetto ifstream per la lettura di file di log
        DefenceGrid def_grid1_;
        DefenceGrid def_grid2_;                 // griglie di attacco e difesa
        AttackGrid att_grid1_;
        AttackGrid att_grid2_;
        int turn_;                              // turno
        int const MAX_TURNS = 2000;             // numero massimo turni
};

#endif