// Autore:

#ifndef DefenceGrid_h
#define DefenceGrid_h
class DefenceGrid : public Grid
{
public:
    bool CheckShip(Ship n); //controlla che le celle non siano già occupate da altre navi
    void PositionShip(Ship n);
    void SetGrid(void);
};
#endif /* DefenceGrid_h */
