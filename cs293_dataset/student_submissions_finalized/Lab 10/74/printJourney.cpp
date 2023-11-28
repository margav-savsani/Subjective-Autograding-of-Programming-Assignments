#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  while(t != nullptr){
      listOfObjects<TrainInfoPerStation *> *l = (t->object)->trains;
      int a = 0;
      while(l != NULL){
        a++;
        l = l->next;
      }
      int at[a] ;
      l = (t->object)->trains;
      int b =0;
      while(l != NULL){
        at[b] = (l->object)->journeyCode;
        l = l->next;
        b++;
      }
  
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
