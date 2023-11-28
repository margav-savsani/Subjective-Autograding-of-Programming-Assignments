#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  
  // cout << "This function is to be implemented by you." << endl;
  
  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp
  int srcindex = stnNameToIndex.get(srcStnName)->value;   //index of given source station
  int destindex = stnNameToIndex.get(destStnName)->value; //index of given destination station
  listOfObjects<StationConnectionInfo*> * srcConnected = adjacency[srcindex].toStations;  //stations info connected to source
  if(srcConnected == nullptr) {
    cout<<"No journeys between the given stations exist"<<endl;
  }
  listOfObjects<StationConnectionInfo*> * currentCon = srcConnected;    //directly connected station that we are currently searching a path from
  if(srcConnected==nullptr) {
    cout<<"No direct journeys available"<<endl;
    return;
  }
  //we need a queue for bfs, can be done using a linked list
  listOfObjects<StationConnectionInfo*> * queue = nullptr;  
  queue = new listOfObjects<StationConnectionInfo*> (currentCon->object); //adding first neighboring station to queue
  listOfObjects<StationConnectionInfo*> *tailqueue = queue;   //rest will be added in the next while loop
  //employing dfs
  listOfObjects<int> * visited= new listOfObjects<int> (srcindex);
  listOfObjects<int> * JCvia = nullptr;
  while(queue!=nullptr){
    if(queue->object->adjacentStnIndex == destindex){
      JCvia->next= new listOfObjects<int> (queue->object->trains->object->journeyCode);
      JCvia = JCvia->next;

    }
    else{
      printPlanJourneys(stnNameToIndex.getKeyAtIndex(queue->object->adjacentStnIndex), destStnName, maxStopOvers-1, maxTransitTime);
    }
    queue = queue->next;
  }
  printStationInfo(srcConnected->object->trains);
  return ;
}

#endif
