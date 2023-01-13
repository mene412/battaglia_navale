<<<<<<< HEAD
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
        void set_coord_center(Coord cord);
        void set_center(void);
        void set_direction(void);
        std::vector<Coord> const coord(void) { return coord_; }
        int const dim(void) { return dim_; }
        int armor(void) { return armor_; }
        int x(void) { return x_; }
        int y(void) { return y_; }
        void set_healed(bool a);
        void set_coord(std::vector<Coord>& coord);
        bool healed(void) { return healed_; }
        void inc_armor(void);
        void dec_armor(void);
        void heal(void);
        Coord center(void){ return center_; }
        bool left(void) { return left_; }
        bool orizzontal(void) { return orizzontal_; }
        void hit(Coord c);
        void set_armor(int a);
        virtual ~Ship() {};
    protected:
        std::vector<Coord> coord_;
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
#endif /* Ship_h */
=======
// Autore: Gaia Soso
#ifndef Ship_h
#define Ship_h
#include <vector>
#include "Coord.h"
class Ship
{
    public:
        void set_direction(void);
        void set_center(void);
        void set_coord_center(Coord cord);
        void set_coord(std::vector<Coord>& coordinates);
        std::vector<Coord>& coord(void){ return coord_; }
        std::vector<int>& coord_hit(void){ return coord_hit_;}
        Coord const coord(int a){return coord_[a];}
        int const dim(void) { return dim_; }
        int armor(void) { return armor_; }
        void set_healed(bool a);
        bool healed(void) { return healed_; }
        Coord center(void){ return center_; }
        bool left(void) { return left_; }
        void dec_armor();
        bool orizzontal(void) { return orizzontal_; }
        void set_armor(int a);
        virtual ~Ship(){};
        void heal(void);
        void hit(Coord c);

    protected:
        Ship(Coord front, Coord back);
        std::vector<Coord> coord_;
        std::vector<int> coord_hit_;
        int dim_;
        int armor_;
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
>>>>>>> 8895afeb16dd38a71cd3988363b79df6abbbafbc
