#ifndef PLANNER_H
#define PLANNER_H
#include<string.h>

struct Station {
  // define suitable fields here
  char s[20];
};

struct Journey {
  // define suitable fields here
  int value;
  float st;
  float et;
  Station s1;
  Station s2;
  
  Journey();
};

struct Query{
  // define suitable fields here
};

class Planner {
  // define suitable fields here
  int N; // size of array A
  struct Journey *A; // Array of dictionary entries
  
  public:
  
  float duration(struct Journey j);
  
  Planner();
  
  int hashValue(char key[]);
  
  int findFreeIndex(char key[]);
  
  bool put(struct Journey j);
  
  struct Journey *get(char key[], float t);
  
  void soonest(char station1[],float k,char station2[]);
};

#endif
