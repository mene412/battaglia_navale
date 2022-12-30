  //Autore:
#include <iostream>
#include "Grid.h"
#include "DefenceGrid.h"
#include "Ship.h"
#include "Battleship.h"
#include "Help_Ship.h"
#include "ExplorationSubmarine.h"
using namespace std;
bool Defence_Grid::check_ship(Ship n)   //controlla che le celle non siano                                          // occupate da altre navi. Per il momento                                   //ritorna un false, ma devo implementare                                    //le eccezioni
    {
      for(int i=0; i<n.get_dim(); i++)
      {
          if(coord[n.get_coord(i, 0)][n.get_coord(i, 1)]!='*')
              return false;
      }
      for(int i=0; i<n.get_dim(); i++)
      {
          coord[n.get_coord(i, 0)][n.get_coord(i, 1)]=n.get_type();
        }
  return true;
    }
void Defence_Grid::set_grid()          //posiziona le navi nella griglia
    {
        for(int i=0; i<3; i++)
        {
            cout<<"Corazzata"<<endl;
            Corazzata c;
            if(check_ship(c)) //se la nave non va ad occupare celle già occupate                    viene inserita nel vettore ships,
            {
                ships.push_back(c);
                cout<<"OK"<<endl; //La stampa di ok è solo per controllare che funzioni, nel codice finale non ci sarà
            }

        }
        for(int i=0; i<3; i++)
        {
            cout<<"Nave Supporto"<<endl;
            Support_Ship s;
            if(check_ship(s))   //se la nave non va ad occupare celle già occupate                    viene inserita nel vettore ships,
            {
                ships.push_back(s);
                cout<<"OK"<<endl;
            }
        }
        for(int i=0; i<2; i++)
        {
        cout<<"Sottomarino"<<endl;
        Submarine d;
        if(check_ship(d))           //se la nave non va ad occupare celle già occupate                    viene inserita nel vettore ships,
        {
            ships.push_back(d);
            cout<<"OK"<<endl;
        }
        }
    }
