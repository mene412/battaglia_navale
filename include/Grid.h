// Autore: Matteo
#ifndef Grid_h
#define Grid_h

#include "Ship.h"
#include "vector"

class Grid {
    public:
        Grid(void);
        void set_grid(void);
        char** grid(void) { return grid_; }
        std::vector<Ship> ships(void) { return ships_; }
    protected:
        std::vector<Ship> ships_;
        char** grid_;
};
#endif /* Grid_h */
