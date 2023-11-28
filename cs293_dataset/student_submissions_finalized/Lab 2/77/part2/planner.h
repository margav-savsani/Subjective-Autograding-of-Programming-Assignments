#include<iostream>
#include<string.h>
#ifndef PLANNER_H
#define PLANNER_H

struct Station {
  // define suitable fields here
  char station[32];
};

struct Journey {
  // define suitable fields here
  char key[32];
  double start_time;
  char station_two[32];
  double finish_time;
  int TOMBSTONE;
};

struct Query{
  // define suitable fields here
  char key[32];
  double time;
  char station_two[32];
};

class Planner {
 Query  query;
 

};


#endif