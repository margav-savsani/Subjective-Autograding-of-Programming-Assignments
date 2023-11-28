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
  
  cout << "This function is to be implemented by you." << endl;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  listOfObjects<TrainInfoPerStation *>* x = stationInfo[stnNameToIndex.get(srcStnName)->value];
  listOfObjects<TrainInfoPerStation *>* y = stationInfo[stnNameToIndex.get(destStnName)->value];
  listOfObjects<TrainInfoPerStation *> * common = nullptr; //stores common entries of the 2 lists
  listOfObjects<TrainInfoPerStation *> * currx = x; //stores common entries of the 2 lists
  listOfObjects<TrainInfoPerStation *> * curry = y; //stores common entries of the 2 lists
  listOfObjects<TrainInfoPerStation *> * currcommon = common; //stores common entries of the 2 lists

  while(currx!=nullptr){
    curry =y;
    while(curry!=nullptr){
      if(currx->object->journeyCode == curry->object->journeyCode){
        if(common==nullptr){
          common = currx;
          common = common->next = nullptr;
          common = common->prev = nullptr;
          currcommon = common;
        }
        currcommon->next = currx;
        // currcommon = currcommon->next;
        currcommon->next->next = nullptr;
        currcommon->next->prev = currcommon;
      }
      curry = curry->next;
    }
    currx = currx->next;
  }
  return;
}

#endif
