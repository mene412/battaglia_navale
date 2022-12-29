// Autore: 
#ifndef Grid_h
#define Grid_h
#include <iostream>
#include <vector>
#include "Functions.h"
using namespace std;
class Grid
{
protected: char coord[13][13];
    vector<Ship> ships;
    
public:
    Grid()
    {
        ships[0];
        for(int i=1; i<=12; i++)
        {
            for(int j=1; j<=12; j++)
            {
                    coord[0][j]=j+'0';
                    coord[i][j]='*';
            }
            coord[i][0]=num_to_lett(i);
        }
        coord[0][0]=' ';
    }
    void show_grid()
    {
        for(int i=0; i<=12; i++)
        {
            for(int j=0; j<=12; j++)
            {
                cout<<coord[i][j]<<"   ";
            }
            
            cout<<endl;
        }
    }
    virtual void set_grid()=0;
};

class Defence_Grid : public Grid
{
public:
    bool check_ship(Ship n)
    {
            for(int i=0; i<n.get_dim(); i++)
            {
                if(coord[n.get_coord(i, 0)][n.get_coord(i, 1)]!='*')
                    return false;
                else
                    coord[n.get_coord(i, 0)][n.get_coord(i, 1)]=n.get_type();
            }
        return true;
    }
    void set_grid()
    {
        for(int i=0; i<3; i++)
        {
            cout<<"Corazzata"<<endl;
            Corazzata c;
            if(check_ship(c))
            {
                ships.push_back(c);
                cout<<"OK"<<endl;
            }
            
        }
        for(int i=0; i<3; i++)
        {
            cout<<"Nave Supporto"<<endl;
            Support_Ship s;
            if(check_ship(s))
            {
                ships.push_back(s);
                cout<<"OK"<<endl;
            }
        }
        for(int i=0; i<2; i++)
        {
        cout<<"Sottomarino"<<endl;
        Submarine d;
        if(check_ship(d))
        {
            ships.push_back(d);
            cout<<"OK"<<endl;
        }
        }
    }
};
class Attack_Grid : public Grid
{
    void set_grid()
    {
        
    }
};

#endif /* Grid_h */
