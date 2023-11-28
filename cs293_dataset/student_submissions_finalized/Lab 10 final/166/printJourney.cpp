#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

bool possible(StationAdjacencyList* adjacency,int startin,int lastin, int jcode) {
  if(startin == lastin) return true;
  listOfObjects<StationConnectionInfo*>* toStations = adjacency[startin].toStations;
  listOfObjects<TrainInfoPerStation*>* trains;

  while (toStations != nullptr) {
    trains = toStations->object->trains;
    while(trains != nullptr) {
      if (trains->object->journeyCode == jcode) {
        return possible(adjacency,toStations->object->adjacentStnIndex,laststnindex, jcode);
      }
      trains = trains->next;
    }
    toStations = toStations->next;
  }

  return false;
}

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  Entry<int> *index1 = stnNameToIndex.get(srcStnName);
  int stind1 = index1->value;

  Entry<int> *index2 = stnNameToIndex.get(destStnName);
  int stind2 = index2->value;

  bool possible = false;
  listOfObjects<StationConnectionInfo*>* toStations = adjacency[stind1].toStations;
  listOfObjects<TrainInfoPerStation*>* trains;

  while (toStations != nullptr) {
    trains = toStations->object->trains;
    while(trains != nullptr) {
      if (possible(adjacency,toStations->object->adjacentStnIndex,stind2,trains->object->journeyCode)) {
        possible = true;
        printStationInfo(trains);
        break;
      }
      trains = trains->next;
    }
    toStations = toStations->next;
  }

  if (possible == false) cout<<"No direct journeys available"<<endl;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif