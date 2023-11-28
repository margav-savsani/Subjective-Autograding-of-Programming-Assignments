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
  //srcStnName = A
  /*
    1. go to stn A 
    2. store A in a queue, list stations adjacent to A and store them in the queue. 
    3. pop A, move to next element. store stations adjacent to next element in the queue.
    4. if B found, continue in the queue, don't list elements after the destination station. 
    5. 
  */

  
  int srcStnIndex=stnNameToIndex.get(srcStnName)->value; //index of srcStnName in dictionary
  int destStnIndex=stnNameToIndex.get(destStnName)->value;

  StationAdjacencyList *currStn = &adjacency[srcStnIndex]; //StationAdjacencyList Objects
  
  listOfObjects<StationAdjacencyList*> *iterator = new listOfObjects<StationAdjacencyList*>(currStn);
  listOfObjects<int> *pq = new listOfObjects<int>(-1); //priority queue for station index
  listOfObjects<int> *head_pq = new listOfObjects<int>(iterator->object->toStations->object->adjacentStnIndex);
  pq = head_pq;
  while(pq!=nullptr){ //moving on to next node
    
    listOfObjects<TrainInfoPerStation*> * journeys = new listOfObjects<TrainInfoPerStation*>(nullptr);
    journeys = iterator->object->toStations->object->trains;
    listOfObjects<TrainInfoPerStation*> * journey_list = journeys;
    while(iterator!=nullptr && iterator->object->toStations!=nullptr){ //traversing adjacent nodes of currNode
      pq->object = iterator->object->toStations->object->adjacentStnIndex;
      journey_list->next = iterator->object->toStations->object->trains;
      listOfObjects<int> *iterator_pq = head_pq;
      bool exist = false;
      while(iterator_pq!=nullptr){
        if(iterator_pq->object == pq->object){
          exist = true;
          break;
        }
        iterator_pq = iterator_pq->next;
      }
      if(exist==false) pq = pq->next;
      iterator->object->toStations = iterator->object->toStations->next;
      if(iterator->object->toStations->object->adjacentStnIndex == destStnIndex){printStationInfo(journeys); break; // found the destination at the adjacent node
    }
    //deleting first element from pq
    head_pq = head_pq->next;
    delete head_pq->prev;
    head_pq->prev = nullptr;
  }
  
  cout << "This function is to be implemented by you." << endl;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
