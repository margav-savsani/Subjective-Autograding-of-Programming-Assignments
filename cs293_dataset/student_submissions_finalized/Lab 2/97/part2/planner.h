#ifndef PLANNER_H
#define PLANNER_H
#include"dictionary.cpp"


struct Station {
  // define suitable fields here
  Dictionary start;
  Dictionary end;
};

struct Journey {
  // define suitable fields here
  float stime = -1;
  char inter_stn[32];
  float inter_time = -1;
  void add(const char* inter_stn, float stime, float inter_time);
};

struct Query{
  // define suitable fields here
};

class Planner {
  // define suitable fields here
  Station station;
  public:
  Planner();
  void add(char start[], float stime, char end[], float etime);
  void query_station(char start[], float stime);
  void query_journey(char start[], float stime, char end[]);
};

#endif