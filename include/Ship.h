// Autore:
#ifndef Ship_h
#define Ship_h
#include <vector>
class Ship
{
    public:
        Ship(void);
        char type(void) { return type_; }
        void set_coord(void);
        std::vector<std::vector<int>> const coord(void) { return coord_; }
        int const dim(void) { return dim_; }
        int armor(void) { return armor_; }
        int x(void) { return x_; }
        int y(void) { return y_; }
        void set_healed(bool a);
        bool healed(void) { return healed_; }
        void incArmor(void);
        void decArmor(void);

    protected:
        std::vector<std::vector<int>> coord_;
        int dim_;
        int armor_;
        int num_;
        int x_;     // numero riga (vedi pg. 3 progetto Tonin)
        int y_;     // numero colonna
        char type_;
        bool healed_;
        void set_y(int y1, int y2);
        void set_x(int x1, int x2);
};
namespace conversion{
    char NumToLett(int t);  //convete da int a char (es 1='a')
    int CharToInt(char t);
}
#endif /* Ship_h */
