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

  
  listOfObjects<TrainInfoPerStation *> *journey_list = nullptr;

  // Process to extract index value of dictionary from string
  int start_key = stnNameToIndex.get(srcStnName)->value;
  int dest_key = stnNameToIndex.get(destStnName)->value;
  BFS_Queue BQ;

  journey_list = start_journey(start_key, dest_key, journey_list, BQ, adjacency);
  while(BQ.N != 0)
  {
    bool present = continue_search(dest_key, BQ, adjacency);
    if(present)
      journey_list = add_journey(start_key, journey_list, BQ, adjacency);
    BQ.Dequeue();
  }
  printStationInfo(journey_list);

  return;



  
  return;
}

#endif
