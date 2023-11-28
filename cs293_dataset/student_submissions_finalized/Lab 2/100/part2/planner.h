#include<iostream>
#include<string.h>
using namespace std;
#ifndef PLANNER_H
#define PLANNER_H

struct Station {
  string name;
  float time;
};

struct Journey {
  Station from;
  Station to;
};

/*struct Query{
  // define suitable fields here
};*/

class Planner {
  Journey* journey;
  int N;
public:
  Planner();

  int hashValue(string key);

  int findFreeIndex(string key);

  bool addJourney(Journey newJourney);

  void printList(Station station);

  float foundJourney(string station1,string station2);

  void findJourney(Station station1 , string station2);

};


#endif