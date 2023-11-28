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
  int src_index = stnNameToIndex.hashValue(srcStnName);
  int dest_index = stnNameToIndex.hashValue(destStnName);

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  bool mark[DICT_SIZE];
  mark[src_index] = true;
  vector<int> Q;
  Q.pushback(src_index);
  while(Q.size() != 0){
    int a = Q.pop();
    listOfObjects<StationConnectionInfo *> *src_to = adjacency[a].toStations;
    while(src_to != nullptr){
      listOfObjects<TrainInfoPerStation *> *trains = src_to->object->trains;
      Q.push_back();
    }
  }
  return;
}

#endif
