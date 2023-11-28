#ifndef PLANNER_H
#define PLANNER_H
#include <cstring>

struct Station {
  // define suitable fields here
  char* name;
  float starttime_to_reach_here,reaching_time,startingtimefornexttrain;
  Station(){
    name= new char[32];
    starttime_to_reach_here = 0;
    reaching_time = 0;
    startingtimefornexttrain = 0;
  }
  

};

struct Journey {
  // define suitable fields here
  Station S1,S2;
  float stime,ftime;
};

struct Query{
  // define suitable fields here
  
};

class Planner {
  // define suitable fields here
  public :
    Journey * J = new Journey[64];
    int j = 0;
    Station* get_trains(char * startstation){
      Station * S = new Station[64];
      int k = 0;
      for(int i=0;i<j;i++){
        if(strcmp(J[i].S1.name,startstation) == 0){
          S[k].name = J[i].S2.name;
          S[k].starttime_to_reach_here = J[i].stime;
          S[k].reaching_time = J[i].ftime;
          k++;
        }
      }
      S[k].starttime_to_reach_here = -1;
      if(k == 0){return NULL;}
      return S;
    }
};

#endif