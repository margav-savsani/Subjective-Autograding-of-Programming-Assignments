#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
  

bool BFS(int jcode, int srcidx, int destidx, StationAdjacencyList* adjacency){
  
  return false;
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime){
  // insert your code here

  int src_ind = stnNameToIndex.get(srcStnName)->value;
  int dest_ind = stnNameToIndex.get(destStnName)->value;
  TrainInfoPerStation * d_train = new TrainInfoPerStation(0,0,0,0);
  listOfObjects<TrainInfoPerStation *>* start = new listOfObjects<TrainInfoPerStation *> (d_train);
  listOfObjects<StationConnectionInfo *>* src_to = adjacency[src_ind].toStations;
  listOfObjects<StationConnectionInfo *>* d_src = src_to;
  while(d_src){
    listOfObjects<TrainInfoPerStation*>* from_src = d_src->object->trains;
    while(from_src){
      int j_code = from_src->object->journeyCode;
      int nxt_idx = d_src->object->adjacentStnIndex;
      if(BFS(j_code, nxt_idx, dest_ind, adjacency)){ 
        listOfObjects<TrainInfoPerStation*>* d_res = start;
        while(true){
          if(!d_res->next){
            listOfObjects<TrainInfoPerStation*>* temp = new listOfObjects<TrainInfoPerStation*>(from_src->object);
            d_res->next = temp;
            temp->prev = d_res;
            break;
          }
          d_res = d_res->next;
        }
      }
      from_src = from_src->next;
    }
    d_src = d_src->next;
  }
  if(!start->next){
    cout<<"No direct journeys available\n";
    return;
  }
  printStationInfo(start->next);

  //cout << "This function is to be implemented by you." << endl;
  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp
  return;
}

#endif
