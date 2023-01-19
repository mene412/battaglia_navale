// Autore: Andrea Mutti

#ifndef REPLAY_H
#define REPLAY_H

#include <fstream>        // libreria fstream per gestire input di file log ed eventuale output
#include "DefenceGrid.h"
#include "AttackGrid.h"

// Classe per la gestione di un replay di una partita da un file di log
//  - Può mostrare il replay tramite video o tramite salvataggio su file di output
class Replay{
    public:
        // Costruttore che accetta come parametro il file di log
        Replay(std::string file_log);   

        // Funzione start per gestire tutto il replay
        void start(void);
        // Funzione start per gestire tutto il replay - salva in output su file
        void start(std::string file_output);   
        
        // Distruttore - chiude il file di log aperto
        ~Replay(){log_.close();}

    private:
        // Legge da file e setta le navi iniziali
        // Funzione membro private
        void take_ships(int player);            
        
        // Controlla la validità della mossa del player 1
        void move_first(void);  
        // Controlla la validità della mossa del player 2
        void move_second(void);

        // Mossa del player 1
        void attack_first(Coord& a, Coord& b);
        // Mossa del player 2
        void attack_second(Coord& a, Coord& b);


        // Mosse delle navi (molto simili alle funzioni in Game)

        // Funzione per fare fuoco sulla griglia nemica
        void attack(int pl, int pos, Coord& c);
        // Funzione di cura della navi (funziona in uno spazio 3x3)
        void heal(int pl, int pos, Coord& c);
        // Permette lo spostamento di una nave di supporto
        void move_help(int pl, int pos, Coord& c);
        // Permette lo spostamento di un sottomarino di esplorazione
        void move_sub(int pl, int pos, Coord& c);
        // Attiva l'avvistamento radar in un'area 5x5
        void search(int pl, int pos, Coord& c);
        // Rimuove una nave dalla griglia e individua i colpi sulla griglia di attacco
        void titanic(int pl, int pos);

        // Incrementa il turno
        inline void increment_turn(){turn_++;}; 
        // Verifica la fine del gioco e chi ha vinto
        bool end(void);
        // Verifica la fine del gioco escrive su file chi ha vinto
        bool end_file(std::ofstream& file);     

        // Variabili membro private -> protezione dati
        std::ifstream log_;                     // oggetto ifstream per la lettura di file di log
        DefenceGrid def_grid1_;                 // griglia di difesa del player 1
        DefenceGrid def_grid2_;                 // griglie di difesa del player 2
        AttackGrid att_grid1_;                  // griglia di attacco del player 1
        AttackGrid att_grid2_;                  // griglia di attacco del player 2
        int turn_;                              // turno attuale
        int const MAX_TURNS = 2000;             // numero massimo di turni per evitare stalli
};

#endif  // REPLAY_H