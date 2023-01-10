// Autore:

#ifndef DefenceGrid_h
#define DefenceGrid_h

#include "Grid.h"

class DefenceGrid : public Grid {
    public: 
        //controlla che le celle non siano già occupate da altre navi
        // controlla da prua e poppa, bow=prua, stern=poppa
    bool checkPosition(std::vector<std::pair<int,int>> coordinates);   
        // inserisce la nave nella griglia    
        void addShip(Ship newShip);
};
#endif /* DefenceGrid_h */
