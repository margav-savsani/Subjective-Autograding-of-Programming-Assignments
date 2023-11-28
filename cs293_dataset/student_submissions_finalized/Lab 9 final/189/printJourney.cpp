#ifndef PLANNER_H
#include "planner.h"
#endif

#ifnded STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  
  //cout << "This function is to be implemented by you." << endl;
  int sourceIndex=stnNameToIndex.get(srcStnName)->value;
  int destinationIndex=stnNameToIndex.get(destStnName)->value;
  StationAdjacencyList sourceStation;
  StationAdjacencyList destinationStation;
  sourceStation=adjacency[sourceIndex];//obtain the source station 
  destinationStation=adjacency[destinationIndex];//obtain the destination station
  listOfObjects<StationConnectionInfo *> *start;//Creating a list that acts as a queue
  start->prev=nullptr;
  start->object->adjacentStnIndex=-1;
  start->object->trains=nullptr;
  listOfObjects<StationConnectionInfo *> *end;
  end->prev=start;
  end->next=nullptr;
  end->object->adjacentStnIndex=-1;
  end->object->trains=nullptr;
  listOfObjects<StationConnectionInfo *> *temp;
  temp=sourceStation.toStations;
  listOfObjects<StationConnectionInfo *> *checkedStart;
  listOfObjects<StationConnectionInfo *> *checkedEnd;
  checkedStart->prev=nullptr;
  checkedStart->next=checkedEnd->prev;
  checkedEnd->next=nullptr;
  while(temp!=nullptr){
      listOfObjects<StationConnectionInfo *> *temp1;
      temp1=temp;
      end->prev->next=temp1;
      temp1->prev=end->prev;
      end->prev=temp1;
      temp1->next=end;
      temp=temp->next;
    }
  while(start->next!=end){
    listOfObjects<StationConnectionInfo *> *head;
    head=start->next;
    listOfObjects<StationConnectionInfo *> *temp2;
    temp2=adjacency[head->object->adjacentStnIndex]
  }
  return;
}
