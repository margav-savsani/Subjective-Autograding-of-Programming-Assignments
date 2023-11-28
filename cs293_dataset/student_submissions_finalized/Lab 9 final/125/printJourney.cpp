#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
struct queueNode{
  //node for the queue to be used for implementing BFS
  int val;
  TrainInfoPerStation * jrny;
  queueNode *next;
  queueNode *prev;
  queueNode(int val, TrainInfoPerStation * jrny){
    this->val = val;
    this->jrny = jrny;
    next = prev = NULL;
  }
};
struct queue{
  //queue to be used for implementing BFS
  queueNode* head;
  queueNode* tail;
  bool isEmpty;

  queue(){
    //default constructor
    head = tail = NULL;
    isEmpty = true;
  }

  void insert(int x, TrainInfoPerStation * jrny){
    //Insert an element in the queue
    queueNode *new_node = new queueNode(x, jrny);
    if(isEmpty){
      head = tail = new_node;
      isEmpty = false;
      return;
    }
    tail->next = new_node;
    tail = tail->next;
  }

  void pop(){
    //delete an element from the queue
    if(isEmpty) return;
    if(head->next==NULL){
      head = tail = NULL;
      isEmpty = true;
      return;
    }
    head = head->next;
  }
};
void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  int start_index = stnNameToIndex.get(srcStnName)->value;
  listOfObjects<TrainInfoPerStation *> *journeys = NULL;
  listOfObjects<StationConnectionInfo* > *next_stations = adjacency[start_index].toStations;
  queue q;

  while(next_stations!=NULL){
    //adding all the initial journeys from the source
    listOfObjects<TrainInfoPerStation* >* trains = next_stations->object->trains;
    while(trains!=NULL){
      q.insert(next_stations->object->adjacentStnIndex,trains->object);
      trains = trains->next;
    }
    next_stations = next_stations->next;
  }

  while(!q.isEmpty){
    listOfObjects<StationConnectionInfo* > *next_station = adjacency[q.head->val].toStations;

    if(stnNameToIndex.getKeyAtIndex(q.head->val)==destStnName){
      //adding the journey if it ends at the destination and continuing
      if(journeys==NULL) journeys = new listOfObjects<TrainInfoPerStation *>(q.head->jrny);
      else{
        journeys->next = new listOfObjects<TrainInfoPerStation *>(q.head->jrny);
        journeys->next->prev = journeys;
        journeys = journeys->next;
      }
      q.pop();
      continue;
    }

    while(next_station!=NULL){
      //adding all the journeys which have the same journey code as the head of the queue 
      //and start from the station which is at the head of queue
      listOfObjects<TrainInfoPerStation* >* trains = next_station->object->trains;
      while(trains!=NULL){
        if(q.head->jrny->journeyCode==trains->object->journeyCode){
          q.insert(next_station->object->adjacentStnIndex,trains->object);
        }
        trains = trains->next;
      }
      next_station = next_station->next;
    }

    q.pop();
  }

  //printing the journeys:
  if(journeys==NULL){
    cout << "No direct journeys available" << endl;
    return;
  }
  listOfObjects<TrainInfoPerStation *> *final_journeys = NULL;
  while(journeys!=NULL){
    listOfObjects<TrainInfoPerStation* >* jrnys = stationInfo[start_index];
    while(jrnys!=NULL){
      if(jrnys->object->journeyCode==journeys->object->journeyCode){
        if(final_journeys==NULL){
          final_journeys = new listOfObjects<TrainInfoPerStation *>(jrnys->object);
        }
        else{
          final_journeys->next = new listOfObjects<TrainInfoPerStation *>(jrnys->object);
          final_journeys->next->prev = final_journeys;
          final_journeys = final_journeys->next;
        }
      }
      jrnys = jrnys->next;
    }
    journeys = journeys->prev;
  }
  while(final_journeys->prev!=NULL){
    final_journeys = final_journeys->prev;
  }
  printStationInfo(final_journeys);
  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
