#include<iostream>
#include<string.h>

#ifndef PLANNER_H
#define PLANNER_H


struct Station {
  char stn[32];// define suitable fields here
};

struct Journey {
  Station stn1;
  Station stn2;
  float tm1;
  float tm2;// define suitable fields here
  int stat=0;
};


class Planner {
private:
  int N;
  struct Journey *J; // define suitable fields here
public:
  Planner();
  float duration(struct Journey g);
  bool put(struct Journey l);
  int hashValue(char stn[]);
   void get(char stn[],float k);
  int findFreeIndex(char stn[]);
 void soonest(char s1[],float k,char s2[]);
};

#endif
