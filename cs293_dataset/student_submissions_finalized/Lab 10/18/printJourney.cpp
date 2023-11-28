#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  listOfObjects<TrainInfoPerStation *> *final = new listOfObjects<TrainInfoPerStation *>(nullptr);
  int src = stnNameToIndex.get(srcStnName)->value;
  int dest = stnNameToIndex.get(destStnName)->value;
  StationConnectionInfo *src_info = new StationConnectionInfo(src);
  StationConnectionInfo *dest_info = new StationConnectionInfo(dest);
  StationAdjacencyList src_adj = adjacency[src];
  //StationAdjacencyList dest_adj = adjacency[dest];
  listOfObjects<StationConnectionInfo *> *src_to = src_adj.toStations;
  listOfObjects<TrainInfoPerStation *> *src_trains = src_info->trains;
  listOfObjects<TrainInfoPerStation *> *queue = new listOfObjects<TrainInfoPerStation *>(nullptr);

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp
  if(final!=nullptr){
    printStationInfo(final);
  }
  else{
    cout<<"No journeys available"<<endl;
  }
  return;
}

#endif
