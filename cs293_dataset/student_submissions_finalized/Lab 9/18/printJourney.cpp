#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  
  cout << "This function is to be implemented by you." << endl;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  listOfObjects<TrainInfoPerStation *> final = new listOfObjects<TrainInfoPerStation *>();
  Entry<int> *stnIndexEntry = stnNameToIndex.get(srcStnName);
  int src_index = stnIndexEntry->value;
  StationAdjacencyList *src_adj = *adjacency[src_index];
  // listOfObjects<TrainInfoPerStation *> *src_info = stationInfo[src_index];
  Entry<int> *stnIndexEntry = stnNameToIndex.get(destStnName);
  int dest_index = stnIndexEntry->value;
  StationAdjacencyList *dest_adj = *adjacency[dest_index];
  // listOfObjects<TrainInfoPerStation *> *dest_info = stationInfo[dest_index];
  listOfObjects<StationConnectionInfo *> *from = src_adj->fromStations;
  listOfObjects<StationConnectionInfo *> *to = dest_adj->toStations;
  
  printStationInfo();
  return;
}

#endif
