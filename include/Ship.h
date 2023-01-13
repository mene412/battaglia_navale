// Autore: Gaia Soso
#ifndef Ship_h
#define Ship_h
#include <vector>
#include "Coord.h"
class Ship
{
    public:
        char type(void) { return type_; }
        void set_direction(void);
        void set_center(void);
        void set_coord_center(Coord cord);
        void set_coord(std::vector<Coord>& coordinates);
        std::vector<Coord>& const coord(void){ return coord_; }
        Coord const coord(int a){return coord_[a];}
        int const dim(void) { return dim_; }
        int armor(void) { return armor_; }
        void set_healed(bool a);
        bool healed(void) { return healed_; }
        Coord center(void){ return center_; }
        bool left(void) { return left_; }
        void dec_armor() { armor_=armor_-1;}
        bool orizzontal(void) { return orizzontal_; }
        void set_armor(int a);
        virtual ~Ship(){};

    protected:
        Ship(Coord front, Coord back);
        std::vector<Coord> coord_;
        int dim_;
        int armor_;
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
#endif /* Ship_h */
