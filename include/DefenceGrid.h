// Autore:
#ifndef DefenceGrid_h
#define DefenceGrid_h
class Defence_Grid : public Grid
{
public:
    bool check_ship(Ship n);
    void set_grid();
};
#endif /* DefenceGrid_h */
