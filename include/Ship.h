// Autore:
#ifndef Ship_h
#define Ship_h
#include <iostream>
#include <vector>
#include <exception>
#include "Functions.h"
using namespace std;
class Ship
{
    protected:
    vector<vector<int>> coord;
    int dim;
    int armor;
    int num;
    int x;
    int y;
    char type;
    
public:
    Ship()
    {
        coord={{0,0},{0,0},{0,0},{0,0},{0,0}};
    }
    char get_type()
    {
        return type;
    }
    void set_coord()
    {
        cout<<"Inserisci le coordinate di prua e di poppa"<<endl;
        int y1,y2;
        char p1,p2;
        cin>>p1;
        cin>>y1;
        cin>>p2;
        cin>>y2;
        int x1=char_to_int(p1);
        int x2=char_to_int(p2);
        
            if(x1==x2 && max(y1,y2)-min(y1,y2)+1==dim)
            {
                for(int i=0; i<dim; i++)
                {
                            coord[i][0]=x1;
                            coord[i][1]=min(y1,y2)+i;
                }
            }
            else if(y1==y2 && max(x1,x2)-min(x1,x2)+1==dim)
            {
                for(int i=0; i<dim; i++)
                {
                            coord[i][0]=min(x1,x2)+i;;
                            coord[i][1]=y1;
                }
            }
            else
            {
                throw out_of_range("NO");
            }
    }
    int get_coord(int n1, int n2)
    {
        return coord[n1][n2];
    }
    int get_dim()
    {
        return dim;
    }
    int get_armor()
    {
        return armor;
    }
};

class Corazzata: public Ship
{
public:
    Corazzata()
    {
        type='C';
        dim=5;
        armor=5;
        set_coord();
    }
};
class Submarine: public Ship
{
public:
    Submarine()
    {
        type='E';
        dim=1;
        armor=1;
        set_coord();
    }
};
class Support_Ship: public Ship
{
public:
    Support_Ship()
    {
        type='S';
        dim=3;
        armor=3;
        set_coord();
    }
};
#endif /* Ship_h */
