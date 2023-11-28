#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <queue>

using namespace std;
  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  
  cout << "This function is to be implemented by you." << endl;

  listOfObjects<TrainInfoPerStation*> *finaltrains =nullptr;
  
  int scrindex = this->stnNameToIndex.get(srcStnName)->value;
  int destindex = this->stnNameToIndex.get(destStnName)->value;

  // dqueue of stations and train used to reach the station
  deque<int> q_stn;
  deque<TrainInfoPerStation *> q_train;
  deque<int> q_changed;
  q_stn.push_back(scrindex);
  q_train.push_back(nullptr);
  q_changed.push_back(0);

  while(q_stn.size() > 0){

    int recent_stn = q_stn.front();
    q_stn.pop_front();
    TrainInfoPerStation * recent_train = q_train.front();
    q_train.pop_front();
    int recent_changed = q_changed.front();
    q_changed.pop_front();

    listOfObjects<StationConnectionInfo *> *temp_stnptr =  this->adjacency[recent_stn].toStations; 
    while(temp_stnptr != nullptr){
      listOfObjects<TrainInfoPerStation*> *temp_trainptr = temp_stnptr->object->trains;
      while(temp_trainptr != nullptr){

        if (recent_train == nullptr){
          q_stn.push_back(temp_stnptr->object->adjacentStnIndex);
          q_train.push_back(temp_trainptr->object);
          q_changed.push_back(0);
        }
        else{
          if (temp_trainptr->object->journeyCode == recent_train->journeyCode){
            q_stn.push_back(temp_stnptr->object->adjacentStnIndex);
            q_train.push_back(temp_trainptr->object);
            q_changed.push_back(recent_changed);
          }
          else if (recent_changed <= maxStopOvers && recent_train->arrTime < temp_trainptr->object->depTime && temp_trainptr->object->depTime-recent_train->arrTime<=maxTransitTime){
            q_stn.push_back(temp_stnptr->object->adjacentStnIndex);
            q_train.push_back(temp_trainptr->object);
            q_changed.push_back(recent_changed+1);
          }
        }
        temp_trainptr = temp_trainptr->next;
      }
      temp_stnptr = temp_stnptr->next;
    }
    if(recent_stn == destindex){
      cout << recent_train->journeyCode
    }
  }

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  
  return;
}

#endif
