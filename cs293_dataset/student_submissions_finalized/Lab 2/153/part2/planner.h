#ifndef PLANNER_H
#define PLANNER_H

#include<stdlib.h>
#include "dictionary.h"
#include "structures.h"

const int ADD_JOURNEY = 1;
const int Q_STATION = 2;
const int Q_JOURNEY = 3;
const int EXIT = 4;

// struct Station {
//   // define suitable fields here
//   char* name = (char*) malloc(MAX_STATION_NAME_LEN);
// };

// struct Journey {
//   // define suitable fields here
//   Station origin;
//   Station destination;
//   float start_time, end_time;
// };

struct Query{
  // define suitable fields here
  int type = EXIT;
  Station s1,s2;
  float t1,t2;
};

class Planner {
  // define suitable fields here
  private:
    Dictionary journey_dict;
    
  public:
    void run(bool automatic);
    void handleQuery(Query q);

    void addJourney(Query q);
    void queryJourney(Query q);
    void queryStation(Query q);
};

#endif