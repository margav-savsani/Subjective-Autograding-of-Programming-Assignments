#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  listOfObjects<TrainInfoPerStation *> *stninfo;
  if(stnNameToIndex.get(srcStnName)==nullptr||stnNameToIndex.get(destStnName)==nullptr) cout<< "invalid station name";
  // insert your code here
  Entry<int> *source = stnNameToIndex.get(srcStnName);
  int a=source->value;
  Entry<int> *dest = stnNameToIndex.get(destStnName);
  int b=source->value;
  listOfObjects<TrainInfoPerStation *> *sourceinfo=stationInfo[a];
  listOfObjects<TrainInfoPerStation *> *destinfo=stationInfo[b];

  
  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>  
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp  
}


#endif
