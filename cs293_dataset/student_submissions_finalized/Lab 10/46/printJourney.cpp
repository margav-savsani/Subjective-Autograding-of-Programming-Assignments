#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
  
bool myfunc(StationAdjacencyList *adjacency, int jcode, int curridx, int destidx){
  if(curridx == destidx)return true;
  
  listOfObjects<StationConnectionInfo *> * adjToList = adjacency[curridx].toStations;
  while(adjToList != nullptr){
    listOfObjects<TrainInfoPerStation *> *ltrai = adjToList->object->trains;
    while(ltrai != nullptr){
      if(ltrai->object->journeyCode == jcode){
        
        return myfunc(adjacency,jcode,adjToList->object->adjacentStnIndex,destidx);
      }
      ltrai = ltrai->next;
    }
    adjToList = adjToList->next;
  }
  return false;
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here

  int srcStnIdx = stnNameToIndex.get(srcStnName)->value;
  int destStnIdx = stnNameToIndex.get(destStnName)->value;

  listOfObjects<int> *myIntList = new listOfObjects<int>(0);
  listOfObjects<int> *myTail = myIntList;

  
  listOfObjects<StationConnectionInfo *> * adjToList = adjacency[srcStnIdx].toStations;

  while(adjToList != nullptr){
    listOfObjects<TrainInfoPerStation *> *ltrai = adjToList->object->trains;
    while(ltrai != nullptr){
      int idx = adjToList->object->adjacentStnIndex;
      bool destFound = myfunc(adjacency, ltrai->object->journeyCode, idx, destStnIdx);

      if(destFound){
        myTail->next = new listOfObjects<int>(ltrai->object->journeyCode);
        myTail = myTail->next;
      }
      ltrai=ltrai->next;
    }
    adjToList = adjToList->next;
  }

  while(myIntList != nullptr){
      cout <<"----"<<endl;
      cout << myIntList->object << endl;
      myIntList = myIntList->next;
  }
  return;
  
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
