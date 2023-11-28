#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <queue>

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  int srcStn = stnNameToIndex.get(srcStnName)->value;
  int destStn = stnNameToIndex.get(destStnName)->value;

  queue<int> bfs;
  bfs.push(srcStn);
  listOfObjects<TrainInfoPerStation*>* direct;
  while(!bfs.empty()){
    listOfObjects<StationConnectionInfo *> * nextStations = adjacency[srcStn].toStations;
    while(nextStations != nullptr){
      if(nextStations->object->adjacentStnIndex != destStn){
        bfs.push(nextStations->object->adjacentStnIndex);
      }
      else{
        direct = nextStations->object->trains;
      }
      nextStations = nextStations->next;
    }
    srcStn = bfs.front();
    bfs.pop();
  }
  printStationInfo(direct);

  // cout << "This function is to be implemented by you." << endl;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
