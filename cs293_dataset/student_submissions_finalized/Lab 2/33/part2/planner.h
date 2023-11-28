#include<iostream>
#include<string.h>

#ifndef PLANNER_H
#define PLANNER_H

struct Station {
  char* Name ;       // define suitable fields here
  Station(){
    Name = new char[32];
  }
};

struct Journey {
  struct Station starting ;
  struct Station stopping ;
  float starting_time ;
  float stopping_time ;
  Journey(){
    starting_time = 0;
    stopping_time = 0;
  }
};

class Planner {
  private:
  int M ;
  struct Journey *B ;

  public :
  Planner(){
    M = 100;
    B = new Journey[100] ;
  }

  int hashValue(char key[]);
  int findFreeIndex(char key[]);
  bool add_journey(Journey k);
  bool check_Station(float time,char key[]);
  bool check_Journey(char key_1[],char key_2[],float time);
  
};

#endif