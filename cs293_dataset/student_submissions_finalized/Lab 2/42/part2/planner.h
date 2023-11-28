#ifndef PLANNER_H
#define PLANNER_H

#include "dict_plan.cpp"

class Planner {
  // define suitable fields here
  Dictionary dict;

  public:

    bool add(char st1[], double start, char st2[], double end);

    returnDetails query_station(char st1[], double start);

    Info query_journey(char st1[], double start, char st2[]);

};

#endif