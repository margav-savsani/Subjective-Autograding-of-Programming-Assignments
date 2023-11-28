#include<bits/stdc++.h>
#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

class Station{
  int index;
  int next_index;
  listOfObjects<TrainInfoPerStation *> *train1;
  listOfObjects<TrainInfoPerStation *> *train2;

  Station(int index, int next_index, listOfObjects<TrainInfoPerStation *> *train1, listOfObjects<TrainInfoPerStation *> *train2){
    this->index = index;
    this->next_index = next_index;
    this->train1 = train1;
    this->train2 = train2;
  }
};
  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  listOfObjects<TrainInfoPerStation *> *desired_journey; //final list of all available desired journeys 

  int srcStn_index = stnNameToIndex.get(srcStnName)->value;  //index of source station
  int idx = srcStn_index;
  int destStn_index = stnNameToIndex.get(destStnName)->value; //index of destination station
  bool present = false;

  vector<bool> visited;
  visited.resize(DICT_SIZE, false);

  listOfObjects<StationConnectionInfo *> *current_stn = adjacency[srcStn_index].toStations;

  listOfObjects<StationConnectionInfo *> *queue;
  queue = new listOfObjects<StationConnectionInfo *>(current_stn->object);
  
  while(current_stn != nullptr){
    if(visited[current_stn->object->adjacentStnIndex] != true){
      visited[current_stn->object->adjacentStnIndex] = true;
      int next_stn = current_stn->object->adjacentStnIndex;
      listOfObjects<TrainInfoPerStation*> *trains1 = current_stn->object->trains;
      while(trains1 != nullptr){
        
      }

      if(next_stn == destStn_index){
        next_stn = false;

      }
    }
  }

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  
  return;
}

#endif
