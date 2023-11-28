#ifndef PLANNER_H
#define PLANNER_H

#include <iostream>
#include <string.h>
#include <cmath>
#include "dictionary.cpp"

struct Station {
  // define suitable fields here
  char station[32];
  float time;
};


struct Query{
  // define suitable fields here
  char St1[32];
  float time;
  char St2[32];
};

class Planner {
  // define suitable fields here
  private:
  int VAL;
  Dictionary d;
  public:
  Planner();
  bool add_route(struct Path p);
  bool queryStation(struct Station s);
  bool queryJourney(struct Query q);
};

#endif