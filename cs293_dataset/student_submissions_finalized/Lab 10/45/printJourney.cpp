#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  
  cout << "This function is to be implemented by you." << endl;

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp
  int srcindex = stnNameToIndex.get(srcStnName)->value;
  int destindex = stnNameToIndex.get(destStnName)->value;

  StationAdjacencyList srcadj = adjacency[srcindex];
  listOfObjects<StationConnectionInfo *> *srcadjlist =  srcadj.toStations;
  
  StationAdjacencyList destadj = adjacency[destindex];
  listOfObjects<StationConnectionInfo *> *destadjlist = destadj.fromStations;

  // creating an array of trains going from src station
  TrainInfoPerStation **srcarray;
  srcarray = new TrainInfoPerStation *[100];
  int srccount=0;
  int destcount=0;
  int i=0;
  while(srcadjlist!=nullptr){ // iterating through stations
    listOfObjects<TrainInfoPerStation *> *srctrainslst = srcadjlist->object->trains;
    while(srctrainslst!=nullptr){ //expanding linked list
      srcarray[i]=srctrainslst->object;
      srccount++; // increasing no.of trains in array till now 
      i++;
      srctrainslst=srctrainslst->next;
    }
    srcadjlist=srcadjlist->next;
  }  
  
  return;
}

#endif
