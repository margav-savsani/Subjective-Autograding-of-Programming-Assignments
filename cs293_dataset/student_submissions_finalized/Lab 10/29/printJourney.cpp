#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{



  bool AtLeastOneFound = false;
  // source and destination index
  int srcStnIndex = stnNameToIndex.get(srcStnName)->value;
  int destStnIndex = stnNameToIndex.get(destStnName)->value;

  // result list will store all journey
  listOfObjects<TrainInfoPerStation *>* Result = nullptr;
  listOfObjects<TrainInfoPerStation *>* LastNoderResult = nullptr;



  // heap
  // this will store the adjacent station list
  listOfObjects<int>* List = new  listOfObjects<int>(srcStnIndex);
  // end point of the node
  listOfObjects<int>* LastNodeList = List;


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
