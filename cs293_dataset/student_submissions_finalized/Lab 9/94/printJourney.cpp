#ifndef PLANNER_H
#include "planner.h"
#endif

#ifnded STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  Entry *t = stnNameToIndex.get(srcStnName);
  int p = t->value;
  StationAdjacencyList r = adjacency[p];

  // cout << "This function is to be implemented by you." << endl;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  if ()
  {
    cout << "No direct journeys available\n";
  }

  return;
  
  cout << "This function is to be implemented by you." << endl;
  
  return;
}
