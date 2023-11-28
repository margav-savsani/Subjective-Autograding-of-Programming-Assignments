#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

struct IndexJC{
  int stnIndex;
  int JrnyCode;
  IndexJC(int stnIndex, int JrnyCode){
    this->stnIndex = stnIndex;
    this->JrnyCode = JrnyCode;
  }
};


void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here

  int srcIndex = stnNameToIndex.get(srcStnName)->value;
  int destIndex = stnNameToIndex.get(destStnName)->value;
  
  listOfObjects<TrainInfoPerStation *> *result=nullptr;
  listOfObjects<IndexJC *> *Q=nullptr;

  listOfObjects<StationConnectionInfo *> *srcToStationsList = adjacency[srcIndex].toStations;
  
  while(srcToStationsList!=nullptr){
    int nextStnIndex = srcToStationsList->object->adjacentStnIndex;
    for(listOfObjects<TrainInfoPerStation*> *info = srcToStationsList->object->trains;info!=nullptr;info = info->next){
      IndexJC* entry = new IndexJC(nextStnIndex,info->object->journeyCode);
      if(Q==nullptr){
        Q = new listOfObjects<IndexJC*>(entry);
      }
      else{
        Q->next = new listOfObjects<IndexJC*>(entry);
        Q->next->prev = Q;
        Q = Q->next;
      }
    }
  }

  while(Q!=nullptr){
    
  }

  // cout << "This function is to be implemented by you." << endl;

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  
  return;
}

#endif
