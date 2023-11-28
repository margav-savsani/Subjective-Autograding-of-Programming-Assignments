#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  Entry<int> *p = stnNameToIndex.get(srcStnName);
  
  listOfObjects<TrainInfoPerStation *> *final = nullptr;
  
  int f = 1;
  listOfObjects<StationConnectionInfo *> * m1 = adjacency[p->value].toStations;
  while(m1 != nullptr){
      int adin = m1->object->adjacentStnIndex;
      string st = stnNameToIndex.getKeyAtIndex(adin);
      listOfObjects<TrainInfoPerStation *> *trains2 = m1->object->trains;
  // insert your code here
  
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
