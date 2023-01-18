// Autore: Gaia Soso
#ifndef Ship_H
#define Ship_H
#include <vector>
#include <iostream>
#include "Coord.h"
class Ship
{
    public:
        //distruttore virtuale
        virtual ~Ship(){};

        //metodi getter che restituiscono il valore delle variabili private e protette
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
        int distance(void) const { return distance_;}

        //metodi setter che modificano il valore delle variabili private e protette
        virtual void set_coord(std::vector<Coord>& coordinates); //imposta le coordinate della nave a partire da un vettore di coordinate
        virtual void set_coord_from_center(Coord& cord);  //imposta le coordinate della nave a partire da quella centrale
        virtual void set_armor(int a);  //imposta il valore dell'armatura
        void set_healed(bool heal); //cambia il valore di healed della nave
       
       //metodi ausiliari
        void dec_armor();  //decrementa di 1 l'armatura
        void heal(void);  //ripara  la nave
        void hit(Coord& c); //se una parte di nave è stata colpita, scrive nel vettore coord_hit_() la sua posizione

    protected:
        //dichiarazione costruttore protected, che inizializza le variabili (accessibile solo da classi derivate)
        Ship(Coord& front, Coord& back);
         
        //metodi setter costruttore navi
        void set_direction(void);//stabilisce se la nave è orizzonatale o verticale
        void set_center(void);  //imposta  il centro della nave a partire dalle coordinate front_ e back_
        void set_coord_center(void);  //imposta il vettore di coordinate appena la nave è costruita

        //variabili protected per classi derivate
        int dim_;                      //dimensione della nave
        int armor_;                    //armatura della nave (quante "parti" non sono state colpite)
        bool healed_;                 //ritorna true se la nave è stata curata, false altrimenti
        int distance_;               //distanza dal centro della nave e la sua prua/poppa
        std::vector<Coord> coord_;  //vettore che identifica le coordinate delle singole "parti" della nave
        Coord center_;               //coordinata che identifica il centro della nave
        bool orizzontal_;           //ritorna true se la nave è orizzontale, false se è verticale
        Coord front_;               //coordinata che identifica la prua della nave
        Coord back_;                //coordinata che identifica la poppa della nave

    private:
        //variabili private
        std::vector<int> coord_hit_; //vettore che contiene la posizione delle coordinate colpite
};
#endif /* Ship_H */
