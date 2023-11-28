#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

struct queueNode{
  //node for the queue to be used for implementing BFS
  int val;
  int stop;
  listOfObjects<TrainInfoPerStation *>* journeys;
  TrainInfoPerStation * jrny;
  queueNode *next;
  queueNode *prev;
  queueNode(int val, TrainInfoPerStation* jrny){
    stop = 0;
    this->val = val;
    this->jrny = jrny;
    next = prev = NULL;
    journeys = new listOfObjects<TrainInfoPerStation *>(jrny);
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

  void insert(int x, TrainInfoPerStation * jrny, int change){
    //Insert an element in the queue
    if(isEmpty){
      head = tail = new queueNode(x, jrny);
      isEmpty = false;
      return;
    }
    queueNode *new_node = new queueNode(*this->head);
    new_node->journeys->next = new listOfObjects<TrainInfoPerStation *>(jrny);
    new_node->journeys = new_node->journeys->next;
    new_node->stop = change;
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

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  int start_index = stnNameToIndex.get(srcStnName)->value;
  listOfObjects<listOfObjects<TrainInfoPerStation *> *> *journeys = NULL;
  listOfObjects<StationConnectionInfo *> *next_stations = adjacency[start_index].toStations;
  queue q;

  while(next_stations!=NULL){
    //adding all the initial journeys from the source
    listOfObjects<TrainInfoPerStation* >* trains = next_stations->object->trains;
    while(trains!=NULL){
      q.insert(next_stations->object->adjacentStnIndex,trains->object,0);
      trains = trains->next;
    }
    next_stations = next_stations->next;
  }

  while(!q.isEmpty){
    listOfObjects<StationConnectionInfo* > *next_station = adjacency[q.head->val].toStations;

    if(stnNameToIndex.getKeyAtIndex(q.head->val)==destStnName){
      //adding the journey if it ends at the destination and continuing
      if(journeys==NULL) journeys = new listOfObjects<listOfObjects<TrainInfoPerStation *> *> (q.head->journeys);
      else{
        journeys->next = new listOfObjects<listOfObjects<TrainInfoPerStation *> *> (q.head->journeys);
        journeys->next->prev = journeys;
        journeys = journeys->next;
      }
      q.pop();
      continue;
    }

    while(next_station!=NULL){
      listOfObjects<TrainInfoPerStation* >* trains = next_station->object->trains;
      while(trains!=NULL){
        //Not adding the journey if stop-over time more than maxTransitTime
        if(trains->object->depTime-q.head->jrny->arrTime>maxTransitTime){
          trains = trains->next;
          continue;
        }
        //Adding the journey if same journeyCode
        if(q.head->jrny->journeyCode==trains->object->journeyCode){
          q.insert(next_station->object->adjacentStnIndex,trains->object,q.head->stop);
        }
        //Adding the journey if number of stop overs doesn't exceed the limit
        else if(q.head->stop<maxStopOvers){
          q.insert(next_station->object->adjacentStnIndex,trains->object,q.head->stop+1);
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
  // listOfObjects<TrainInfoPerStation *> *final_journeys = NULL;
  // while(journeys!=NULL){
  //   listOfObjects<TrainInfoPerStation* >* jrnys = stationInfo[start_index];
  //   while(jrnys!=NULL){
  //     if(jrnys->object->journeyCode==journeys->object->object->journeyCode){
  //       if(final_journeys==NULL){
  //         final_journeys = new listOfObjects<TrainInfoPerStation *>(jrnys->object);
  //       }
  //       else{
  //         final_journeys->next = new listOfObjects<TrainInfoPerStation *>(jrnys->object);
  //         final_journeys->next->prev = final_journeys;
  //         final_journeys = final_journeys->next;
  //       }
  //     }
  //     jrnys = jrnys->next;
  //   }
  //   journeys = journeys->prev;
  // }
  // while(final_journeys->prev!=NULL){
  //   final_journeys = final_journeys->prev;
  // }
  while(journeys->prev!=NULL){
    journeys = journeys->prev;
  }
  while(journeys!=NULL){
    printStationInfo(journeys->object);
    journeys = journeys->next;
    cout << endl << "---------" << endl;
  }
  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  return;
}

#endif
