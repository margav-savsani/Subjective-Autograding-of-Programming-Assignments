#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  // insert your code here
  listOfObjects<TrainInfoPerStation *> *directJourneys;
  Entry<int> *srcstn = stnNameToIndex.get(srcStnName);
  int srcstnIndex = srcstn->value;
  Entry<int> *deststn = stnNameToIndex.get(destStnName);
  int deststnIndex = deststn->value;
  
  
  cout << "This function is to be implemented by you." << endl;
  
  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  return;
}
