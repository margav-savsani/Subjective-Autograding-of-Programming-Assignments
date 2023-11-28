#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

bool isTravelable(StationAdjacencyList* adjacency,int startstnindex,int laststnindex, int jcode) {
  if(startstnindex == laststnindex) return true;
  listOfObjects<StationConnectionInfo*>* toStations = adjacency[startstnindex].toStations;
  listOfObjects<TrainInfoPerStation*>* trains;

  while (toStations != nullptr) {
    trains = toStations->object->trains;
    while(trains != nullptr) {
      if (trains->object->journeyCode == jcode) {
        return isTravelable(adjacency,toStations->object->adjacentStnIndex,laststnindex, jcode);
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
  int stn_index1 = index1->value;

  Entry<int> *index2 = stnNameToIndex.get(destStnName);
  int stn_index2 = index2->value;

  bool istravelable = false;
  listOfObjects<StationConnectionInfo*>* toStations = adjacency[stn_index1].toStations;
  listOfObjects<TrainInfoPerStation*>* trains;

  while (toStations != nullptr) {
    trains = toStations->object->trains;
    while(trains != nullptr) {
      if (isTravelable(adjacency,toStations->object->adjacentStnIndex,stn_index2,trains->object->journeyCode)) {
        istravelable = true;
        printStationInfo(trains);
        break;
      }
      trains = trains->next;
    }
    toStations = toStations->next;
  }

  if (istravelable == false) cout<<"No direct journeys available"<<endl;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
