// Autore: Gaia Soso
#ifndef Ship_h
#define Ship_h
#include <vector>
#include "Coord.h"
class Ship
{
    public:
        //distruttore virtual
        virtual ~Ship(){};

        //metodi getter
        bool healed(void) const { return healed_; }
        Coord center(void) const{ return center_; }
        bool orizzontal(void) const { return orizzontal_; }  
        std::vector<Coord>& coord(void){ return coord_; }
        std::vector<int>& coord_hit(void){ return coord_hit_;}
        Coord const coord(int a) const {return coord_.at(a);}
        int dim(void) const { return dim_; }
        int armor(void) const { return armor_; }
        Coord front(void) const { return front_;}
        Coord back(void) const{ return back_; }


        //metodi setter 
        void set_coord(std::vector<Coord>& coordinates);
        void set_coord_center(Coord cord);
        void set_armor(int a);
       
       //metodi ausiliari
        void dec_armor();
        void heal(void);
        void hit(Coord c);

    protected:
        //costruttore protected (accessibile solo da classi derivate)
        Ship(Coord front, Coord back);

         
        //metodi setter costruttore
        void set_direction(void);
        void set_center(void);
        void set_coord_center(void);

        //variabili protected per classi derivate
        int dim_;
        int armor_;
        bool healed_;
        int distance_;
        std::vector<Coord> coord_;
        Coord center_;

    private:
        //variabili private
        std::vector<int> coord_hit_;
        Coord front_;
        Coord back_;
        bool orizzontal_;
};
#endif /* Ship_h */
