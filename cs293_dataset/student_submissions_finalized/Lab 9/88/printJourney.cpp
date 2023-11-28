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

  // insert your code here
  
  cout << "Copyright Dhanajay Raman, Regd. 2022" << endl;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  for(int i=0; i<20; i++){
    cout<<"Hello Mr. "<<i<<endl;
  }

  int count=0;
  while(true){
    cout<<"Help me"<<endl;
    count++;
    if(count==20) break;
  }
  return;
}

#endif
