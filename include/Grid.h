// Autore:
#ifndef Grid_h
#define Grid_h
#include "Ship.h"
using namespace std;
class Grid
{
protected: char coord[13][13];
    vector<Ship> ships;

public:
    Grid();
    void show_grid();
    virtual void set_grid()=0;
};
#endif /* Grid_h */
