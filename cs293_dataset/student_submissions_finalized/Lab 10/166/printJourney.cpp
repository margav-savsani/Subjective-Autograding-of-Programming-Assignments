#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

bool possible(StationAdjacencyList* adj,int startin,int lastin, int deptime){
  if(startin==lastin) return true;
  listOfObjects<StationConnectionInfo*>* toSt = adjacency[startin].toStations;
  listOfObjects<TrainInfoPerStation*>* rail;

  while(toSt!=nullptr){
    rail=toSt->object->trains;
    while(rail!=nullptr){
      if((rail->object->depTime)-(rail->prev->object->arrTime)>0030){
        return possible(adj,toSt->object->adjacentStnIndex,lastin,deptime);
      }
      rail->next
    }
    toSt=toSt->next;
  }
  return false;
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{


  cout << "This function is to be implemented by you." << endl;

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  
  return;
}

#endif
