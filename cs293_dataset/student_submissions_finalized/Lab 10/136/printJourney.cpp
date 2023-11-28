#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
  
void depth_first_search(int v){
  listOfObjects<StationConnectionInfo *> * curr=adjacency[v].toStation;
  while(){
    int curr_index=curr->object->index;
    depth_first_search(curr_index);
    curr=curr->next;
  }
}

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
  int srcIndex=stnNameToIndex(srcStnName);
  int destIndex=stnNameToIndex(destStnName);
  //depth-first-search
    
  return;
}

#endif
