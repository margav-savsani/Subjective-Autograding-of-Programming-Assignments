#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  listOfObjects<TrainInfoPerStation *> *directJourneys = nullptr;
  Entry<int> *srcstn = stnNameToIndex.get(srcStnName);
  int srcstnIndex = srcstn->value;
  //cout<<srcstnIndex<<endl;

  Entry<int> *deststn = stnNameToIndex.get(destStnName);
  int deststnIndex = deststn->value;
  int stopCount = 0;
  int transitTime = 0;
  
  listOfObjects<StationConnectionInfo *> *adj_stns = adjacency[srcstnIndex].toStations;
    
  cout << "This function is to be implemented by you." << endl;
  //maxStopOvers 
  
  
  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  
  return;
}

#endif