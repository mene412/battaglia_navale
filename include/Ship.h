// Autore:
#ifndef Ship_h
#define Ship_h
#include <vector>
class Ship
{
    public:
    Ship(void);
    char GetType(void);
    void SetCoord(void);
    int const GetCoord(int n1, int n2);
    int const GetDim(void);
    int GetArmor(void);
    int GetX(void);
    int GetY(void);
    void SetHealed(bool a);
    bool Healed(void);
    void IncArmor(void);
    void DecArmor(void);

    protected:
    std::vector<std::vector<int>> coord_;
    int dim_;
    int armor_;
    int num_;
    int x_;
    int y_;
    char type_;
    bool healed_;
    void SetY(int y1, int y2);
    void SetX(int x1, int x2);
};
namespace conversion{
    char NumToLett(int t);  //convete da int a char (es 1='a')
    int CharToInt(char t);
}
#endif /* Ship_h */
