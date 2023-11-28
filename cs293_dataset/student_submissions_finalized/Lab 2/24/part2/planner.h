#include <iostream>
#include "string.h"
#ifndef PLANNER_H
#define PLANNER_H

struct Station {
  // define suitable fields here
  
};

struct Journey {
  
  char station_one[32];
  char station_two[32];
  float start_time;
  float end_time;
  int value=0;
  // define suitable fields here
};

struct Query{
  // define suitable fields here
};

class Planner {
  private:
  int N; // size of array A
  struct Journey *A; // Array of dictionary entries

 public:

   
  int hashValue(char station_one[]);

  
  int findFreeIndex(char station_one[]);
  
  Planner(); 
  bool put(struct Journey e);
  void func(struct Journey d);
  void que(struct Journey d);
};

#endif
