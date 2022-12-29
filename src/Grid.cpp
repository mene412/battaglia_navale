#include <iostream>
#include <vector>
#include "Functions.h"
#include "Grid.h"
using namespace std;

Grid::Grid()            //costruttore default, inizializza la griglia a "tutto mare"
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
void Grid::show_grid()
    {
        for(int i=0; i<=12; i++)        //Devo ancora sistemare il problema dei                                   caratteri 10,11 e 12
        {
            for(int j=0; j<=12; j++)
            {
                cout<<coord[i][j]<<"   ";
            }

            cout<<endl;
        }
    }
