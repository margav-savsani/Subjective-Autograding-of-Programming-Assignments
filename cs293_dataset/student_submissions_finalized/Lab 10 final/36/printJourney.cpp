#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
class tostnandtrain{
public:
  int changes=0;
  TrainInfoPerStation* train;
  int index;

  tostnandtrain(TrainInfoPerStation* train, int index) {
    this->train=train;
    this->index=index;
  }
  void setchanges(int c){changes=c;}
};



void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  
  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp
  int srcStnindex=stnNameToIndex.get(srcStnName)->value, destStnindex=stnNameToIndex.get(destStnName)->value;

  static listOfObjects<TrainInfoPerStation *> *stack=nullptr;
  static listOfObjects<TrainInfoPerStation *> *start=nullptr;
  static int stopovers=0;
  listOfObjects<StationConnectionInfo *> *totrains=adjacency[srcStnindex].toStations;

  while(totrains!=nullptr ) {
    int adjindex=totrains->object->adjacentStnIndex;
    listOfObjects<TrainInfoPerStation *> *currtrain=totrains->object->trains;
    while (currtrain!=nullptr)
    {
      if (stack==nullptr){
        stack=new listOfObjects<TrainInfoPerStation *>(currtrain->object);
        start=stack;
      }
      else{
        if (stack->object->journeyCode!=currtrain->object->journeyCode) {
          stopovers++;
          if (stopovers>maxStopOvers) {
            stopovers--;
            currtrain=currtrain->next;
            continue;
          }
          // transit time check          
          // int oldjrncode=currtrain->object->journeyCode;
          // listOfObjects<StationConnectionInfo*> *fromstation =adjacency[adjindex].fromStations;
          
        }
        stack->next=new listOfObjects<TrainInfoPerStation *>(currtrain->object);
        stack->next->prev=stack;
        stack=stack->next;
      }

      if (adjindex==destStnindex){
        printStationInfo(start);
        if (stack->prev==nullptr) {
          stack=nullptr;
        }
        else{
          stack=stack->prev;
          stack->next=nullptr;
        }
        stopovers--;
        currtrain=currtrain->next;
        continue;
      }
      else {
        string newsrcstnname=stnNameToIndex.getKeyAtIndex(adjindex);
        if (stack->prev!=nullptr) {
          if (stack->prev->object->journeyCode==stack->object->journeyCode) {
            printPlanJourneys(newsrcstnname,destStnName,maxStopOvers,maxTransitTime);
          }
          else {
            printPlanJourneys(newsrcstnname,destStnName,maxStopOvers,maxTransitTime);
          }
        }
        else {
          printPlanJourneys(newsrcstnname,destStnName,maxStopOvers,maxTransitTime);
        }
        if (stack!=nullptr) {
          if (stack->prev==nullptr) {
            stack=nullptr;
          }
          else{
            stack=stack->prev;
            stack->next=nullptr;
          }
        }
      }
      stopovers--;

      currtrain=currtrain->next;
    }
    

    totrains=totrains->next;
  }
}

#endif
