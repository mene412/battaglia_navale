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
        void attack_first(Coord a, Coord b);
        void attack_second(Coord a, Coord b);
        int position(DefenceGrid& def_grid, Coord a);
        void attack(int pl, int pos, Coord b);
        void heal(int pl, int pos, Coord b);
        void move_help(int pl, int pos, Coord b);
        void move_sub(int pl, int pos, Coord b);
        void exploration(int pl, int pos, Coord b);

        std::ifstream log;
        std::pair<DefenceGrid, DefenceGrid> def_grid_;
        std::pair<AttackGrid, AttackGrid> att_grid_;
        int turn_;
};

#endif