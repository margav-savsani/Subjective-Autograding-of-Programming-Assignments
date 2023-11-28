#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  
  // cout << "This function is to be implemented by you." << endl;

  // get indices
  int srcidx = stnNameToIndex.get(srcStnName)->value;
  int destidx = stnNameToIndex.get(destStnName)->value;

  //declarations
  //list needed to print direct journeys
  TrainInfoPerStation * d_train = new TrainInfoPerStation(0,0,0,0);
  //res points to the strat of the list 
  listOfObjects<TrainInfoPerStation *>* res = new listOfObjects<TrainInfoPerStation *> (d_train);
  //adjacency list of source
  listOfObjects<StationConnectionInfo *>* src_to = adjacency[srcidx].toStations;
  //dummy variable to traverse
  listOfObjects<StationConnectionInfo *>* d_src = src_to;


  //print
  if(!res->next)
  {
    //result is empty
    cout<<"No direct journeys available\n";
    return;
  }
  printStationInfo(res->next);

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  
  return;
}

#endif
