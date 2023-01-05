  //Autore:
  #include <iostream>
  #include "../include/Grid.h"
  #include "../include/DefenceGrid.h"
  #include "../include/Ship.h"
  #include "../include/Battleship.h"
  #include "../include/HelpShip.h"
  #include "../include/ExplorationSubmarine.h"
  bool DefenceGrid::CheckShip(Ship n){
      for(int i=0; i<ships_.size(); i++){
          std::cout<<ships_.size()<<std::endl;
          if(n == ships_[i])                     //Operator overloading;
              return false;
  }
      return true;
  }

  void DefenceGrid::PositionShip(Ship n){
      for(int i=0; i<n.GetDim(); i++){
      coord_[n.GetCoord(i, 0)][n.GetCoord(i, 1)]=n.GetType();
      }
      ships_.push_back(n);
  }

  void DefenceGrid::SetGrid(void){
      for(int i=0; i<3; i++){
          std::cout<<"Corazzata"<<std::endl;
          Battleship c;
          if(CheckShip(c)){
              PositionShip(c);
              std::cout<<"OK"<<std::endl;           //"Ok" messo solo per controllo codice
          }
          else i--;
      }
      for(int i=0; i<3; i++){
          std::cout<<"Nave Supporto"<<std::endl;
          HelpShip s;
          if(CheckShip(s)){
              PositionShip(s);
              std::cout<<"OK"<<std::endl;           //"Ok" messo solo per controllo codice
          }
          else i--;
      }
      for(int i=0; i<2; i++){
          std::cout<<"Sottomarino"<<std::endl;
          ExplorationSubmarine d;
          if(CheckShip(d)){
              PositionShip(d);
              std::cout<<"OK"<<std::endl;           //"Ok" messo solo per controllo codice
          }
          else i--;
      }
      return;
  }
