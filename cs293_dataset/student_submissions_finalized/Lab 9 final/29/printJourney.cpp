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

  bool AtLeastOneFound = false;
  // source and destination index
  int srcStnIndex = stnNameToIndex.get(srcStnName)->value;
  int destStnIndex = stnNameToIndex.get(destStnName)->value;

  // result list will store all journey
  listOfObjects<TrainInfoPerStation *>* Result = nullptr;
  listOfObjects<TrainInfoPerStation *>* LastNoderResult = nullptr;



  // heap
  // this will store the adjacent station list
  listOfObjects<int>* List = new  listOfObjects<int>(srcStnIndex);
  // end point of the node
  listOfObjects<int>* LastNodeList = List;

  // Visited stations
  listOfObjects<int>* visitedStations = nullptr;
  // end point of the node
  listOfObjects<int>* lastVisitedStations = visitedStations;

  // go to every station
  listOfObjects<TrainInfoPerStation *>* add = nullptr;
  listOfObjects<TrainInfoPerStation *>* addlastnode = nullptr;


  while (List != nullptr) {
    // check if this station is visited or not
    bool isVisted = false;
    listOfObjects<int>* currStn = visitedStations;
    while (currStn != nullptr) {
      if (currStn->object == List->object) {
        isVisted = true;
        break;
      }
      currStn = currStn->next;
    }
    if (!isVisted) {
      if (List->object == destStnIndex) {
        Result = nullptr;
        LastNoderResult = nullptr;
        listOfObjects<TrainInfoPerStation *>* srcTrains = stationInfo[srcStnIndex];
        while (srcTrains != nullptr) {
          listOfObjects<TrainInfoPerStation *>* destTrains = stationInfo[destStnIndex];
          while (destTrains != nullptr) {
            if (destTrains->object->journeyCode == srcTrains->object->journeyCode) {
              if (Result == nullptr) {
                Result = new listOfObjects<TrainInfoPerStation *> (srcTrains->object);
                LastNoderResult = Result;
              }
              else {
                LastNoderResult->next = new listOfObjects<TrainInfoPerStation *> (srcTrains->object);
                LastNoderResult = LastNoderResult->next;
              }
            }
            destTrains = destTrains->next;
          }
          srcTrains = srcTrains->next;
        }
      }

      // add current station in the list
      if (visitedStations == nullptr) {
        visitedStations = new listOfObjects<int>(List->object);
        lastVisitedStations = visitedStations;
      }
      else {
        lastVisitedStations->next = new listOfObjects<int>(List->object);
        lastVisitedStations = lastVisitedStations->next;
      }


      // CHANGE HEAP
      listOfObjects<StationConnectionInfo*>* currStn = adjacency[List->object].toStations;
      while (currStn != nullptr) {
        LastNodeList->next = new listOfObjects<int> (currStn->object->adjacentStnIndex);
        LastNodeList = LastNodeList->next;
        currStn = currStn->next;
      }
    }

    // delete scourse
    listOfObjects<int> * temp = List;
    List = List->next;
    delete temp;
  }


  // if result is null
  if (Result == nullptr) {
    cout << "No direct journeys available" << endl;
  }
  else printStationInfo(Result);

  return;
}

#endif
