// Autore:
#ifndef Battleship_h
#define Battleship_h
class Battleship: public Ship
{
    public:
    Battleship(void);
    bool fire(AttackGrid& AttGrid, DefenceGrid& DefGrid, int x, int y);
};
#endif /* Battleship_h */
