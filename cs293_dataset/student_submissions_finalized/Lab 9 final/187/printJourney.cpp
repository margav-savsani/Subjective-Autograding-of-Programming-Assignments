#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include<queue>
using namespace std;
void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  int srcInd = stnNameToIndex.get(srcStnName)->value;
  int destInd = stnNameToIndex.get(destStnName)->value;
   StationAdjacencyList list = adjacency[srcInd];
  // listOfObjects<TrainInfoPerStation *> *list1 = stationInfo[srcInd];
  // listOfObjects<TrainInfoPerStation *> *list2 = stationInfo[destInd];
  listOfObjects<StationConnectionInfo *> *starlist = list.toStations;
  while(starlist != nullptr){
    queue<int> v;
    v.push(starlist->object->adjacentStnIndex);
    while(!v.empty()){
      v.pop();
      
    }

  }
  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp

#endif
