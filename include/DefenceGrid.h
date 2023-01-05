// Autore:

#ifndef DefenceGrid_h
#define DefenceGrid_h

#include "Grid.h"

class DefenceGrid : public Grid {
public:
    bool CheckShip(Ship n); //controlla che le celle non siano già occupate da altre navi
    void PositionShip(Ship n);
};
#endif /* DefenceGrid_h */
