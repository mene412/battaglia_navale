// Autore: Andrea Mutti

#ifndef Replay_h
#define Replay_h

#include <fstream>
#include "DefenceGrid.h"
#include "AttackGrid.h"

class Replay{
    public:
        Replay(std::string file_log);
        void start(void);
        void start(std::string file_output);
        ~Replay(){log_.close();}

    private:
        void take_ships(int player);
        void move_first(void);
        void move_second(void);
        void attack_first(Coord& a, Coord& b);
        void attack_second(Coord& a, Coord& b);
        void attack(int pl, int pos, Coord& c);
        void heal(int pl, int pos, Coord& c);
        void move_help(int pl, int pos, Coord& c);
        void move_sub(int pl, int pos, Coord& c);
        void search(int pl, int pos, Coord& c);
        void titanic(int pl, int pos);
        void increment_turn(){turn_++;};

        std::ifstream log_;
        DefenceGrid def_grid1_;
        DefenceGrid def_grid2_;
        AttackGrid att_grid1_;
        AttackGrid att_grid2_;
        int turn_;
};

#endif