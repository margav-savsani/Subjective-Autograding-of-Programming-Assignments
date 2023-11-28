#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

bool connected(string stnname1, string stnname2)
{
  if()
  {
    int jc1 = stnname1.get();
    int jc2 = stnname2.get();
    
  }
  return true;
}

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  
  cout << "This function is to be implemented by you." << endl;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp

  listOfObjects<TrainInfoPerStation *> *jrnylist;
  if(!connected(srcStnName, destStnName))
  {
    cout << "No direct journeys available" << endl;
  }
  else
  {
    
  }
  
  return;
}

#endif
