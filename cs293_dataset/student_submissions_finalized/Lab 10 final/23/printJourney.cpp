#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
//i thought of storing the path from source to destination
//then i will check all the trains which satisfies the below conditions
//if the conditions are satisfied i will print the info of the respective trains.
using namespace std;
void path(int start,int dest,listOfObjects<StationConnectionInfo*>* adjlist){
  //this function calculates the path
  //this return the array of diff possibilities inked lists indices of the adjoint station
  listOfObjects<StationConnectionInfo*>* nextstation = adjlist;
  listOfObjects<int>* pathindices;
  while(nextstation != NULL){
    nextstation = nextstation->next;
    pathindices->next = nextstation->object->adjacentStnIndex;
  }
}
void trains(int start,int dest){
  //this gives the trains between the 2 respective stations.
}
void check(int maxTransitTime,listOfObjects<TrainInfoPerStation*>* trains)
{
  //this functions checks the condition of time between 2 stations of a linked list
}
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  int start = stnNameToIndex.get(srcStnName)->value;
  int end = stnNameToIndex.get(destStnName)->value;
  listOfObjects<StationConnectionInfo*>* adjlist = adjacency[start].toStations;
  

  // cout << "This function is to be implemented by you." << endl;

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  
}

#endif