#include <iostream>
#include<string.h>
#include<cmath>
using namespace std;

#ifndef PLANNER_H
#define PLANNER_H


struct Station {
   char stn[32]; 	
};

struct Journey {
   Station s1;
   Station s2;
   float t1;
   float t2;
   int stat=0;
};

struct Query{
 
};

class Planner {

private:
  Journey* J;
  int N;
  
public:

  Planner();

  int hashValue(char key[]);

 int findFreeIndex(char key[]);
  
 bool add(struct Journey e);
    
void stnlist(char key[],float t);

void soonest(char key1[],float time,char key2[]);
      
};

#endif
