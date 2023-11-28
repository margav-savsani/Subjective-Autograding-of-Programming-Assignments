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

  listOfObjects<TrainInfoPerStation *> *train1s=stationInfo[stnNameToIndex.get(srcStnName)->value];
  listOfObjects<TrainInfoPerStation *> *train2s=stationInfo[stnNameToIndex.get(destStnName)->value];
  listOfObjects<TrainInfoPerStation *> *other=nullptr,*curr;
  while(train1s!=nullptr){
    while(train2s!=nullptr){
      if(train1s->object->journeyCode==train2s->object->journeyCode && train1s->object->arrTime < train2s->object->arrTime){
        if(other==nullptr)other=new listOfObjects<TrainInfoPerStation *>(train1s->object);
        curr=other;
      }
      else{
        curr->next=new listOfObjects<TrainInfoPerStation *>(train1s->object);
        curr=curr->next;
      } 
      train2s=train2s->next;
    }
    train1s=train1s->next;
  }

  printStationInfo(other);

  // insert your code here
  
  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
