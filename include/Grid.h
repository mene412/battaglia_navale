// Autore:
#ifndef Grid_h
#define Grid_h
#include "Ship.h"
class Grid
{
    public:
    Grid(void);
    void ShowGrid(void);
    virtual void SetGrid(void)=0;
    char ReturnCharMatrix(int n1, int n2);
    protected:
    char coord_[13][13];
    std::vector<Ship> ships_;
};
bool operator== (Ship& Ship1, Ship& Ship2);
#endif /* Grid_h */
