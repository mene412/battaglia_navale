// Autore:
#ifndef Ship_h
#define Ship_h
#include <vector>
class Ship
{
    protected:
    std::vector<std::vector<int>> coord;
    int dim;
    int armor;
    int num;
    int x;
    int y;
    char type;

public:
    Ship();
    char get_type();
    void set_coord();
    int get_coord(int n1, int n2);
    int get_dim();
    int get_armor();
};

#endif /* Ship_h */
