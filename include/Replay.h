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

    private:
        void take_ships(int player);
        void move_first(void);
        void move_second(void);

        std::ifstream log;
        std::pair<DefenceGrid, DefenceGrid> def_grid_;
        std::pair<AttackGrid, AttackGrid> att_grid_;
};

#endif