// Autore: Gaia Soso
#ifndef Ship_h
#define Ship_h
#include <vector>
class Ship
{
    public:
        Ship(void);
        char type(void) { return type_; }
        void setInitialCoord(int x1, int x2, int y1, int y2);
        void setCoord(int x, int y);
        std::vector<std::pair<int,int>> const coord(void) { return coord_; }
        std::pair<int,int> coord(int a){return coord_[a];}
        int const dim(void) { return dim_; }
        int armor(void) { return armor_; }
        int x(void) { return x_; }
        int y(void) { return y_; }
        void setHealed(bool a);
        bool healed(void) { return healed_; }
        bool ifSameCoord(int x, int y);
        void incArmor(void);
        void decArmor(void);

    protected:
        std::vector<std::pair<int,int>> coord_;
        int dim_;
        int armor_;
        int num_;
        int x_;     // numero riga (vedi pg. 3 progetto Tonin)
        int y_;     // numero colonna
        char type_;
        bool healed_;
};
namespace conversion{
    char NumToLett(int t);  //convete da int a char (es 1='a')
    int CharToInt(char t);
}
#endif /* Ship_h */
