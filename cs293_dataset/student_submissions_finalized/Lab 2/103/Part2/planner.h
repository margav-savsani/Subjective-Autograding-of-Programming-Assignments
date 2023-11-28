#include <iostream>
#include <string.h>
#include <vector>

#include "queue.h"
#include "dictionary.h"

using namespace std;

#ifndef PLANNER_H
#define PLANNER_H

struct Journey {
  // define suitable fields here
  char startStation[32];
  char endStation[32];
  float startTime;
  float endTime;
};

struct Query{
  // define suitable fields here
  char type;
  char startStation[32];
  char endStation[32];
  float startTime;
};

class Planner {
  // define suitable fields here
private:
  Dictionary< vector<Journey> > stationDetails; // dictionary mappin station names to journeys from given station

public:

  // start the query loop
  void startQueryLoop();

  // add newJourney to the stationDetails dictionary
  void addJourney(Journey newJourney);

  // process queries
  void processQuery(Query query);
};

#endif