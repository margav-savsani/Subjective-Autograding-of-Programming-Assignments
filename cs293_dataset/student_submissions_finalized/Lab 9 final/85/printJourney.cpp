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
  int si= stnNameToIndex.get(srcStnName)->value;
  int di= stnNameToIndex.get(destStnName)->value;
  while(adjacency[si].toStations->object->trains->object != NULL){
    cout<<adjacency[si].toStations->object->trains->object<<endl;
  adjacency[si].toStations->object->trains->object=adjacency[si].toStations->object->trains->next->object;}
  
  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
