#include "dictionary.cpp"
#include<vector>

#ifndef PLANNER_H
#define PLANNER_H

struct ThreeTuple
{
  float n1;
  char string[32];
  float n2;
};

class Planner {
  // define suitable fields here
  Dictionary stations;
  public:
    void ADD(Query query);

    std::vector<Journey> QUERY_STATION(Query query);

    ThreeTuple QUERY_JOURNEY(Query query);
    
    
};

#endif