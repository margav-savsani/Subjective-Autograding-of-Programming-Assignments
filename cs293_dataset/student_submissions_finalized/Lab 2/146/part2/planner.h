#ifndef PLANNER_H
#define PLANNER_H

const int JOURNEYS_SIZE = 64;

struct Journey {
  // define suitable fields here
  char start[32],end[32];
  float starttime,endtime;
  void print(){
    std::cout<<starttime<<" "<<end<<std::endl; //outputs
  }
};

struct Station {
  // define suitable fields here
  int n; //number of journeys starting here
  Journey journeys[JOURNEYS_SIZE]; //list of all journeys starting here 
};

//A structure to accomodate two train journeys
struct LongJourney{
  bool indirect; //true if journey is not direct
  Journey J1; //First journey
  Journey J2; //Second journey in case it is an indirect train
  void print(){
    if(indirect) std::cout<<J1.starttime<<" "<<J1.end<<" "<<J2.starttime<<std::endl; //output format of two train journey
    else std::cout<<J1.starttime<<std::endl; //usual output
  }
};
#endif