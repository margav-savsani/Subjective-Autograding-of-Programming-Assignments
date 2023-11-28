#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  
  int src_index = stnNameToIndex.get(srcStnName)->value;
  int dest_index = stnNameToIndex.get(destStnName)->value;

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  TrainInfoPerStation * t = new TrainInfoPerStation(0, 0, 0, 0);
  listOfObjects<TrainInfoPerStation *> *req = new listOfObjects<TrainInfoPerStation *> (t);
  listOfObjects<StationConnectionInfo *> *src_to = adjacency[src_index].toStations;
  listOfObjects<StationConnectionInfo *> *dest_from = adjacency[dest_index].fromStations;

  int a = 0;
  int b = 0;

  listOfObjects<StationConnectionInfo *> *s = src_to;
  while(s != nullptr){
    if(s->object->adjacentStnIndex == dest_index){
      listOfObjects<TrainInfoPerStation *> * j = req;
      while(true){
        if(j->next == nullptr) {
          j->next = s->object->trains;
          j->next->prev = j;
          b++;
          break;
        }
        j = j->next;
      }
    }
    s = s->next;
  }
  printStationInfo(req->next);
  
}

#endif
