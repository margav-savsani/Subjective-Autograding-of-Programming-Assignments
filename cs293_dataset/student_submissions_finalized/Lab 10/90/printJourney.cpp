#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

// Created a new struct, Trainlist
// As an alternate to queue, as we weren't
// allowed to use STL queue/vectors
// In this we shall store trains
// and do BFS on them, instead of stations
struct TrainList{
public:
  int index, jCode; //index to store the source_index of the train, jCode for its journey Code
  TrainList *next; //pointer to the next element in this linked list
  
  // Constructor
  TrainList(int index, int jCode)  {
    this->index = index;
    this->jCode = jCode;
    next = nullptr;
  }
};

//Returns common trains in lists list1 and list2
//O(mn) where m is number of trains in list1
// and n is number of trains in list2
listOfObjects<TrainInfoPerStation *> *intersections(listOfObjects<TrainInfoPerStation *> *list1,listOfObjects<TrainInfoPerStation *> *list2){
  listOfObjects<TrainInfoPerStation *> *final_list = nullptr; //final list which has all the intersected/common trains
  listOfObjects<TrainInfoPerStation *> *curr; // pointer variable to iterate over list1
  while(list1 != nullptr){
    listOfObjects<TrainInfoPerStation *> *dummy = list2; //pointer variable to iterate over list2
    while(dummy != nullptr){
      if(list1->object->journeyCode == dummy->object->journeyCode){
        if(final_list != nullptr){
          curr->next = new listOfObjects<TrainInfoPerStation *>(list1->object);
          curr=curr->next;
        }
        else{
          final_list = new listOfObjects<TrainInfoPerStation *>(list1->object);
          curr = final_list;
        }
      }
      dummy = dummy->next;
    }
    list1 = list1->next;
  }
  return final_list;
}

// Adds a TrainInfoPerStation* object into the list
void add(listOfObjects<TrainInfoPerStation *> *list, TrainInfoPerStation* object){
    listOfObjects<TrainInfoPerStation *> *last = list;
    while (last->next != nullptr)//Iterate over the list to find the last element
      last = last->next;
    //Insert new element at the next position to the last element
    last->next = new listOfObjects<TrainInfoPerStation *>(object);
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime){

  int src_index = stnNameToIndex.get(srcStnName)->value;
  int dest_index = stnNameToIndex.get(destStnName)->value;
  listOfObjects<StationConnectionInfo *> *to_station = adjacency[src_index].toStations;
  listOfObjects<TrainInfoPerStation *> *final_list = nullptr;
  
  if(maxStopOvers < 0 || maxTransitTime < 0) return;
  else if(maxStopOvers == 0){
    listOfObjects<StationConnectionInfo *> *curr = to_station;
    while(curr != nullptr){
      if(curr->object->adjacentStnIndex == dest_index){
        if(final_list == nullptr){
          add(final_list,curr->object->trains);
        }
      }
      curr = curr->next;
    }
    printStationInfo(final_list);
  }
  else{
    listOfObjects<StationConnectionInfo *> *curr = to_station;
    while(curr != nullptr){
      if(curr->object->adjacentStnIndex == dest_index){
        listOfObjects<TrainInfoPerStation *>*train = curr->object->trains;
        while(train!=nullptr){
          if(train->)
        }
        printPlanJourneys(newsrc, destStnName, maxStopOvers-1, maxTransitTime - arrtime - depttime);
      }
      train = train->next;
    }
  }
}