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
        ~Replay(){log.close();}

    private:
        void take_ships(int player);
        void move_first(void);
        void move_second(void);
        void attack_first(Coord& a, Coord& b);
        void attack_second(Coord& a, Coord& b);
        int position(DefenceGrid& def_grid, Coord& a);
        void attack(int pl, int pos, Coord& c);
        void heal(int pl, int pos, Coord& c);
        void move_help(int pl, int pos, Coord& c);
        void move_sub(int pl, int pos, Coord& c);
        void exploration(int pl, int pos, Coord& c);

        std::ifstream log;
        DefenceGrid def_grid1_;
        DefenceGrid def_grid2_;
        AttackGrid att_grid1_;
        AttackGrid att_grid2_;
        int turn_;
};

#endif