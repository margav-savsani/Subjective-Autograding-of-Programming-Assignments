#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

// Created a new class for the Queue in BFS
// Stores the Station indexes 
// and journey codes of individual train journeys
// Has a default constructor and a parametrized constructor
////////////////////////////////////////////////////////////
class stnNodes{
  public:
    int index;
    int jCode;
    int prevJrnyTime;
    int stopNo;
    // will have to add member variables for prevJrnyTime and stopNo
    stnNodes(){;}
    stnNodes(int idx, int code){
      this->index = idx;
      this->jCode = code;
    }
};

// Removes the first element in the queue
// Takes the head of the queue as input and returns the modified head with the deleted first element
/////////////////////////////////////////////////////////////////
listOfObjects<stnNodes> * Dequeue(listOfObjects<stnNodes> * head){
  // will have to change Deque implementation so as to not entirely remove the
  // vertex, but rather only move the head, and keep a processed pointer at the start
  if(head == nullptr || head->next == nullptr)
    return nullptr;
  listOfObjects<stnNodes> *previous = head;
  head = head->next;
  delete previous;
  head->prev = nullptr;
  return head;
}

//
// Create a new function called inQueue, which will check if the current station has already been processed or not
// bool inQueue(listOfObjects<stnNodes> * start, int code){
//   while(start != nullpr){
//     if(code == start->object->jCode)
//       return true;
//     start = start->next;
//   }
//   return false;
// }

// Adds new elements to the queue
// Takes in the tail of the queue, and the object to be inserted
// Returns the modified tail with the added Entry
/////////////////////////////////////////////////////////////////////////////
listOfObjects<stnNodes>* Enque(listOfObjects<stnNodes> * tail, stnNodes obj){
  if(tail == nullptr)
    tail = new listOfObjects<stnNodes>(obj);
  else{
    tail->next =  new listOfObjects<stnNodes>(obj);
    listOfObjects<stnNodes> *previous = tail;
    tail = tail->next;
    tail->prev = previous;
  }
  return tail;
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  int src = stnNameToIndex.hashValue(srcStnName), dest = stnNameToIndex.hashValue(destStnName);
  listOfObjects<TrainInfoPerStation *> *stnInfoList = nullptr, *ptr = nullptr;
  listOfObjects<stnNodes> *head = nullptr, *tail = nullptr, *start = nullptr;
  listOfObjects<int> *jCodes = nullptr;
  stnNodes sourceInfo(src, -1);
  head = Enque(head, sourceInfo);
  tail = head;
  start = head;

  while(head != nullptr){
    listOfObjects<StationConnectionInfo *> *curr = adjacency[head->object.index].toStations;
    while(curr != nullptr){
      if(curr->object->adjacentStnIndex == dest){
          listOfObjects<TrainInfoPerStation *>* temp = curr->object->trains;
          while(temp != nullptr){
            // change first if condition in the if statement below, to 
            // include checks for maxTransitionTime
            if(temp->object->journeyCode == head->object.jCode || head->object.jCode == -1 ){
              if(jCodes == nullptr)
                jCodes = new listOfObjects<int>(temp->object->journeyCode);
              else{
                listOfObjects<int> *codes = jCodes;
                while(codes->next != nullptr){
                  codes = codes->next;
                }
                codes->next = new listOfObjects<int>(temp->object->journeyCode);
              }
            }
            temp = temp->next;
          }
      }
      else{
        listOfObjects<TrainInfoPerStation *>* temp = curr->object->trains;
        while(temp != nullptr){
          // Remove the journey code condition and add conditions to check for transitTime and stopOvers
          //Also check whether this station has been traversed before or not, if yes, then don't enque
          if(temp->object->journeyCode == head->object.jCode || head->object.jCode == -1){
            stnNodes middle(curr->object->adjacentStnIndex, temp->object->journeyCode);
            tail = Enque(tail, middle);
          }
          temp = temp->next;
        }
      }
      curr = curr->next;
    }
    head = Dequeue(head);
  }

  listOfObjects<int>* j_codes = jCodes;

  while(j_codes != nullptr){
    listOfObjects<TrainInfoPerStation *> *stnInfo = stationInfo[src];
    while(stnInfo != nullptr){
      if(stnInfo->object->journeyCode == j_codes->object){
        if(stnInfoList == nullptr){
          stnInfoList = new listOfObjects<TrainInfoPerStation *>(stnInfo->object);
          ptr = stnInfoList;
        }
        else{
          ptr->next = new listOfObjects<TrainInfoPerStation *>(stnInfo->object);
          ptr = ptr->next;
        }
      }
      
      stnInfo = stnInfo->next;
    }
    j_codes = j_codes->next;
  }

  if(stnInfoList == nullptr)
    cout << "No direct journeys available" << endl;
  else
    printStationInfo(stnInfoList);

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  
  return;
}

#endif
