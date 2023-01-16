// Autore: Gaia Soso
#ifndef Ship_h
#define Ship_h
#include <vector>
#include "Coord.h"
#include <iostream>
class Ship
{
    public:
        //distruttore virtual
        virtual ~Ship(){};

        //metodi getter
        bool healed(void) const { return healed_; }
        Coord& center(void) { return center_; }
        bool orizzontal(void) const { return orizzontal_; }  
        std::vector<Coord>& coord(void){ return coord_; }
        std::vector<int>& coord_hit(void){ return coord_hit_;}
        Coord& coord(int a)  {return coord_.at(a);}
        int dim(void) const { return dim_; }
        int armor(void) const { return armor_; }
        Coord& front(void) { return front_;}
        Coord& back(void) { return back_; }
        int x(void){ return x_;}
        int y(void){ return y_;}

        //metodi setter 
        virtual void set_coord(std::vector<Coord>& coordinates);
        virtual void set_coord_from_center(Coord& cord);
        virtual void set_armor(int a);
        void set_healed(bool heal);
       
       //metodi ausiliari
        void dec_armor();
        void heal(void);
        void hit(Coord& c);

    protected:
        //costruttore protected (accessibile solo da classi derivate)
        Ship(Coord& front, Coord& back);
         
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
        int x_;
        int y_;
        bool orizzontal_;
        Coord front_;
        Coord back_;

    private:
        //variabili private
        std::vector<int> coord_hit_;
};
#endif /* Ship_h */
