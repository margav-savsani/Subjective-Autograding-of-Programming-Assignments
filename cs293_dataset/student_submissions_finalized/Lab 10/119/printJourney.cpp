#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime){
  int source = stnNameToIndex.get(srcStnName)->value;
  int destination = stnNameToIndex.get(destStnName)->value;

  listOfObjects<TrainInfoPerStation *> *finalTrains = NULL;

  listOfObjects<int> *currentOutTrains = NULL;
  listOfObjects<int>* x = NULL;
  listOfObjects<StationConnectionInfo*>* y = adjacency[source].toStations;
  while (y != NULL) {
      listOfObjects<TrainInfoPerStation*>* z = y->object->trains;
      while (z != NULL) {
          if (currentOutTrains == NULL) {
              currentOutTrains = x = new listOfObjects<int>(z->object->journeyCode);
          }
          else {
              x->next = new listOfObjects<int>(z->object->journeyCode);
              x = x->next;
          }
          z = z->next;
      }
      y = y->next;
  }

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp
  
  return;
}

#endif
