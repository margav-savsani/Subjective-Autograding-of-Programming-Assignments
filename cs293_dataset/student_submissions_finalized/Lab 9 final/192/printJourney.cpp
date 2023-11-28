#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;


//Implementation for a node of the Queue
template<class T>
struct ListNode{
  
  T object;
  ListNode<T> * next;
  ListNode<T> * prev;
  int prevJrnyCode;

  
  //Constructor for a queue
  ListNode(){
    this->next = this->prev = nullptr;

  }
  //Constructor for a queue
  ListNode(T obj, int jrnyCode){
    prevJrnyCode = jrnyCode;
    this->object = obj;
    this->next = this->prev = nullptr;
  }

};

template<class T>
//Implementation of a queue.
class Queue{
  
  
  public:
    int size; //size of the queue
    ListNode<T> * head; //head of the queue.
    ListNode<T> * tail; //tail of the queue.

    //Constructor
    Queue(){
      this->size = 0;
      this->head = this->tail = nullptr;

    }

    //Adding an element to the queue
    void push(T obj, int JrnyCode){
      ListNode<T>* newNode = new ListNode<T>(obj, JrnyCode);

      if(tail == nullptr){
         head = tail =  newNode;

      } else {
        tail->next = newNode;
        newNode->prev = tail;
        
        tail = tail->next;
      }

      this->size++;

    }
    //Deleting the element of the queue
    ListNode<T>* pop(){

      if (head == nullptr) {
        return NULL;
      } else if (this->size == 1){
        ListNode<T>* toDelete = head;
        size--;
        head = tail = nullptr;
        return toDelete;
      } else {

        ListNode<T>* toDelete = head;
        head = head->next;
        head->prev = nullptr;
        this->size--;
        return toDelete;
      }
    }

    
};

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  //List to store all the journeys.
  listOfObjects<TrainInfoPerStation *>* journeys = nullptr;
  
  

  //Hash values of the source and destination station.
  int srcHash = stnNameToIndex.hashValue(srcStnName);
  int destHash = stnNameToIndex.hashValue(destStnName);


  
  //currptr of the adjacency list.
  listOfObjects<StationConnectionInfo *> *  currptr = adjacency[srcHash].toStations;

  Queue<StationConnectionInfo*>* bfsList = new Queue<StationConnectionInfo*>();
  
  //Add all the journeys from the source into the queue.
  while (currptr) {
    //for each station in adjacency list.
    listOfObjects<TrainInfoPerStation *> * currInfo = currptr->object->trains;
    while (currInfo != nullptr){
      //add each journey to each adjacent station.
      bfsList->push(currptr->object, currInfo->object->journeyCode);
      currInfo = currInfo->next;
    }
    currptr = currptr->next;
  }
  //Process all the elements of the queue.
  while(bfsList->size != 0){
    //if adjacent station is the destination, print the journey corresponding with the source.
    if (bfsList->head->object->adjacentStnIndex == destHash){
      listOfObjects<TrainInfoPerStation *> * currInfo = bfsList->head->object->trains;
      while(currInfo != nullptr){
        if (currInfo->object->journeyCode == bfsList->head->prevJrnyCode){
          //add journeys into the listOfObjects.
          if (!journeys){
            //if list of Objects is empty then define a new one.
            journeys = new listOfObjects<TrainInfoPerStation *>(currInfo->object);

          } else {
            //add the elements in the list of Journeys.
            listOfObjects<TrainInfoPerStation*>* newNode = new listOfObjects<TrainInfoPerStation*>(currInfo->object);
            newNode->next = journeys->prev;
            journeys->prev = newNode;

            journeys = newNode;
            
          }
        }
        currInfo = currInfo->next;
      }
      //pop the first element.
      bfsList->pop();


    } else {
      //if the destination doesnt match, advance to the next node corresponding to the journey which took you to the currentNode.
      listOfObjects<StationConnectionInfo*>* currptr = adjacency[bfsList->head->object->adjacentStnIndex].toStations;
      //find all the matching stations.
      while(currptr){
        listOfObjects<TrainInfoPerStation *> * currInfo = currptr->object->trains;
        while (currInfo){
          if (currInfo->object->journeyCode == bfsList->head->prevJrnyCode){
            bfsList->push(currptr->object, bfsList->head->prevJrnyCode);
          }
          currInfo = currInfo->next;
        }
        currptr = currptr->next;
      }
      //pop the first elemnt of the queue.
      bfsList->pop();


    }
    //print all the journeys.
    if (journeys)
      printStationInfo(journeys);
    else 
      cout << "No direct journeys available." << endl;
  }

  

  

  
  return;
}






#endif
