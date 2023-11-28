#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

bool possible(StationAdjacencyList* adj,int startindex,int lastindex, int jcode){
  if(startindex==lastindex)return true;
  else return false;
}

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{ Entry<int> *ind1 = stnNameToIndex.get(srcStnName);
  int stind1 = ind1->value;

  Entry<int> *ind2 = stnNameToIndex.get(destStnName);
  int stind2 = ind2->value;
  
  listOfObjects<StationConnectionInfo*>* toStations = adjacency[stind1].toStations;
  if(!possible(adjacency,toStations->object->adjacentStnIndex,stind2,toStations->object->trains->object->journeyCode)){
    cout << "No direct journeys available" << endl;
  }
  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
