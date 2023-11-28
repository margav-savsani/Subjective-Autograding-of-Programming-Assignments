#include <iostream>
#include <string.h>
#ifndef PLANNER_H
#define PLANNER_H
using namespace std;

struct Station {
  // define suitable fields here
  char station_name;
  int time;
};

struct Journey {
  // define suitable fields here
  Station start;
  Station destination;
};

struct Query{
  // define suitable fields here
};

class Planner {
  // define suitable fields here
};

#endif