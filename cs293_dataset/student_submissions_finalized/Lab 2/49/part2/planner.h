#ifndef PLANNER_H
#define PLANNER_H
#include <string.h>
#include <iostream>
using namespace std;

struct Station {
  // define suitable fields here
  string name;  
};

struct Journey {
  // define suitable fields here
   Station start,end;
   float t1,t2 ;
   Journey(){
    t1=0;
    t2=0;
  }
};

struct Query{
  // define suitable fields here
};

class Planner {
  // define suitable fields here
  int N;
  Journey *A;

  public:
  Planner();
  bool add(Station s1, float t1, Station s2, float t2);
  void query_station(Station s, float t);
  void query_journey(Station s1,float t, Station s2);
};

#endif