#ifndef PLANNER_H
#define PLANNER_H

#include"dictionary.h"
struct Journey{
  Entry startst;
  Entry endst;
  float startti;
  float endti;
  // define suitable fields here
};

struct Query{
  Entry start_st;
  float start_ti;
  Entry end_st;
  // define suitable fields here
};

class Planner {
  public:
    
    Dictionary jo;
    Journey add_journey(char[],int,char[],int);
    void station_query(char[],int);
    void journey_query(char[],int,char[]);

  // define suitable fields here
};

#endif