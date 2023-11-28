#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

list of list of journeys PlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime){

  
  ans;
  l=neighbours of src station
  if(src=dest|| l==NULL)
  for neighbour in l:
  if not visited{
    visited=visited+neighbour
    s=from list of neighbour and srcstn
    possible jrneys for neighbour=PlanJourneys(neighbourname,destStnName,maxStopOvers,maxtransit)
    for a in s{
      for b in (jrnys for neighbour){
        if(b[0]->arrival-a->arrival<maxTransitTime){
          for k in (to list of src station and neighbour){
            if(k.code=a.code){
              ans=ans+k
            }
        }
      }
    } 
    
    }
  }
}
  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  list of list of jrnys=PlanJourneys
  
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
