#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include "planner.h"
using namespace std;

listOfObjects<TrainInfoPerStation *>* expand(listOfObjects<TrainInfoPerStation *>* list){

  listOfObjects<TrainInfoPerStation *>* expanded = nullptr;
  while(list != nullptr){
    for(int i = 0; i < 7; i++){
      if(list->object->daysOfWeek[i]){
        TrainInfoPerStation temp(list->object->journeyCode, list->object->stopSeq, list->object->arrTime, list->object->depTime);
        temp.setDayOfWeek(i);
        if(expanded == nullptr){
          expanded = new listOfObjects<TrainInfoPerStation *>(&temp);
        }
        else{
          listOfObjects<TrainInfoPerStation *>* iter = expanded;
          while(iter->next != nullptr){iter = iter->next;}
          iter->next = new listOfObjects<TrainInfoPerStation *>(&temp);
        }
      }
    }
    list = list->next;
  }
  return expanded;
}

bool isPresent(int JrnyCode, listOfObjects<TrainInfoPerStation *> *list){
  while(list != nullptr){
    if(list->object->journeyCode == JrnyCode)return true;
    list = list->next;
  }
  return false;
}

void update_list(TrainInfoPerStation *train, listOfObjects<TrainInfoPerStation *> *list, listOfObjects<TrainInfoPerStation *> *append){
  while(list->next != nullptr){
    list = list->next;
  }
  if(train != nullptr){
    list->next = new listOfObjects<TrainInfoPerStation*>(train);
    list->next->prev = list;
  }
  else{
    list->next = append;
  }
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  
  cout << "This function is to be implemented by you." << endl;

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  // Take a jrnycode see all the next station of it.
  // Consider all jrnycode of the next station amd go to next station recursively.
  // Update maxStopOvers and maxTransitionTime each time.
  static int recursionlvl = 0;
  static listOfObjects<listOfObjects<TrainInfoPerStation *> *> final_list = nullptr;
  static listOfObjects<TrainInfoPerStation *> *append = nullptr;
  static int src_hash = stnNameToIndex.get(srcStnName)->value;
  static int dest_hash = stnNameToIndex.get(destStnName)->value;
  int temp_hash = src_hash;
  listOfObjects<TrainInfoPerStation *> *JrnyCode = expand(stationInfo[src_hash]);

  if(src_hash == dest_hash){
    // print the journey code directly but one by one.
  }
  while(JrnyCode != nullptr){
    if(recursionlvl == 0){
      if(append == nullptr){
        append = new listOfObjects<TrainInfoPerStation *>(JrnyCode->object);
      }
      else{
        update_list(JrnyCode->object, append, nullptr);
      }
      listOfObjects<StationConnectionInfo *> *toStn = adjacency[src_hash].toStations;
      while(toStn != nullptr){
        if(isPresent(JrnyCode->object->journeyCode, toStn->object->trains)){
          src_hash = toStn->object->adjacentStnIndex;
          recursionlvl++;
          printPlanJourneys(srcStnName, destStnName, maxStopOvers, maxTransitTime);
        }
      }
      JrnyCode = JrnyCode->next;
    }
    else{
      
    }

  }
    recursionlvl--;
    return;
}

#endif
