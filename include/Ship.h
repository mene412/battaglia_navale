// Autore: Gaia Soso
#ifndef Ship_h
#define Ship_h
#include <vector>
#include "Coord.h"
class Ship
{
    public:
        Ship(Coord front, Coord back);
        char type(void) { return type_; }
        void Ship::set_coord_center(int x, int y);
        void set_center(void);
        void set_direction(void);
        std::vector<std::pair<int,int>> const coord(void) { return coord_; }
        std::pair<int,int> coord(int a){return coord_[a];}
        int const dim(void) { return dim_; }
        int armor(void) { return armor_; }
        int x(void) { return x_; }
        int y(void) { return y_; }
        void set_healed(bool a);
        bool healed(void) { return healed_; }
        bool ifSameCoord(int x, int y);
        void incArmor(void);
        void decArmor(void);
        Coord center(void){ return center_; }
        bool left(void) { return left_; }
        bool orizzontal(void) { return orizzontal; }
    protected:
        std::vector<std::pair<int,int>> coord_;
        int dim_;
        int armor_;
        int num_;
        int x_;     // numero riga (vedi pg. 3 progetto Tonin)
        int y_;     // numero colonna
        char type_;
        bool healed_;
        int distance_;
    private:
        Coord front_;
        Coord back_;
        Coord center_;
        bool left_;
        bool orizzontal_;
};
namespace conversion{
    char NumToLett(int t);  //convete da int a char (es 1='a')
    int CharToInt(char t);
}
#endif /* Ship_h */
