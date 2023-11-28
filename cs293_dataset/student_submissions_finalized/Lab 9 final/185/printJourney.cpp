#include<bits/stdc++.h>
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
  
  cout << "This function is to be implemented by you." << endl;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  listOfObjects<TrainInfoPerStation *> *direct_journey;
  int adj;
  
  vector<bool> visited; //make a boolean vector to keep track of visited stations
  visited.resize(numStations, false);  //initialise the elements of vector // to false

  int source_index = stnNameToIndex.get(srcStnName)->value; //get the index where the source station is stored in dictionary
  int idx = source_index;
  int dest_index = stnNameToIndex.get(destStnName)->value; //get index of destination station

  if(adjacency[source_index].toStations == nullptr){ //if there is no connected stations from source station, then print no journey found
    cout << "No direct journeys available" << endl;
  }

  listOfObjects<StationConnectionInfo *> *toStns  = adjacency[idx].toStations;

  listOfObjects<StationConnectionInfo *> *queue; //make a queue to perform BFS
  queue = new listOfObjects<StationConnectionInfo *>(toStns->object);

  while(queue != nullptr){  //visit every station in the between source and destination

    listOfObjects<TrainInfoPerStation *> *trainn = toStns->object->trains;
    while(toStns != nullptr){
      adj = toStns->object->adjacentStnIndex;
      if(visited[adj] == false){ //if the station is not visited, mark it as visited
        visited[adj] = true;
      
        if(adj == dest_index){ //if the current station's index is equal to the destination's station index
        
      }
    }
    }
    

    }
  

  return;
}

#endif
