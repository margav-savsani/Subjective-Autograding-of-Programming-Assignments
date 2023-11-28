#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  
  int dest_index = stnNameToIndex.get(destStnName)->value;

  listOfObjects<TrainInfoPerStation *> *destjrny = NULL;

  queue<QEle> queue_BFS;

  int index = stnNameToIndex.get(srcStnName)->value;

  // The adjacencylist of the currStation.
  StationAdjacencyList *currStation ;
  currStation =  adjacency;

  listOfObjects<StationConnectionInfo *> *adj_stn_list = currStation[index].toStations;

  while (adj_stn_list != NULL)
  {

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
