#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include <vector>
using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  listOfObjects<TrainInfoPerStation *> * stations;
  listOfObjects<StationConnectionInfo *> * start_station;
  start_station = adjacency->toStations;
  while((start_station!=NULL)&&(stnNameToIndex.getKeyAtIndex(start_station->object->adjacentStnIndex)!=srcStnName)){
    start_station = start_station->next;
  }
  listOfObjects<TrainInfoPerStation *> * trains = start_station->object->trains;
  vector<int> jcodes;
  while(trains!=NULL){
    jcodes.push_back(trains->object->journeyCode);
    trains = trains->next;
  }
  
  //cout << "This function is to be implemented by you." << endl;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
