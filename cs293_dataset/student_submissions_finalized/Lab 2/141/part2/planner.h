#ifndef PLANNER_H
#define PLANNER_H

struct Station {
  // define suitable fields here
  char station[32];
};

struct Journey {
  // define suitable fields here
  char station1[32];
  char station2[32];
  double start;
  double end;
  int index;
  bool EMPTY; 
  bool TOMBSTONE;
};

struct Query{
  // define suitable fields here
  Station station;
  double start;
};

class Planner {
  // define suitable fields here
  Query query;
  Journey journey1;
  Journey journey2;
};

#endif