#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

class QueueEntry{
  listOfObjects<TrainInfoPerStation>* journey_infos;
  Entry<int> station;
}

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  StationAdjacencyList src = adjacency[stnNameToIndex.get(srcStnName)];
  StationAdjacencyList dest = adjacency[stnNameToIndex.get(destStnName)];
  listOfObjects<QueueEntry>* queue;
  //listOfObjects<QueueEntry>* start = queue;
  //listOfObjects<QueueEntry>* end = queue;
}

#endif
