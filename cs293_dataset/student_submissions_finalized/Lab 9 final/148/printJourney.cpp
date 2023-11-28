#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

struct JourneyStationPair{
    int stationId;
    TrainInfoPerStation *trainInfo; // The info at the source station

    JourneyStationPair(){
        stationId = -1;
        trainInfo = nullptr;
    }

    JourneyStationPair(int stationId){
        this->stationId = stationId;
        trainInfo = nullptr;
    }

    JourneyStationPair(int stationId, TrainInfoPerStation *trainInfo){
        this->stationId = stationId;
        this->trainInfo = trainInfo;
    }
};
void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  int startIndex = stnNameToIndex.get(srcStnName)->value, endIndex = stnNameToIndex.get(destStnName)->value;
 listOfObjects<JourneyStationPair> *presentStation = nullptr;// A linked list to all the stations which will be traversed, in this order
 listOfObjects<JourneyStationPair> *endOfList = presentStation; // Pointer to the last element
  listOfObjects<StationConnectionInfo *> *toStations = adjacency[startIndex].toStations;
  while(toStations != nullptr){
    listOfObjects<TrainInfoPerStation *> *trains = toStations->object->trains;
    while(trains != nullptr){
            if(endOfList == nullptr){
                    endOfList = new listOfObjects<JourneyStationPair>(JourneyStationPair(startIndex, trains->object ));
                    presentStation = endOfList;
            }
            else{
                endOfList->next =new listOfObjects<JourneyStationPair>(JourneyStationPair(startIndex, trains->object )); 
                endOfList = endOfList->next;
            }
            trains = trains->next;
    }
    toStations = toStations->next;
  }
 listOfObjects<TrainInfoPerStation *> *journeys = nullptr; // The answer
 listOfObjects<TrainInfoPerStation *> *lastjourney= nullptr; // The answer
 while(presentStation != nullptr){
         if(presentStation->object.stationId == endIndex){
                TrainInfoPerStation *presentTrainsInfo = presentStation->object.trainInfo;
                if(journeys == nullptr){
                    // First journey
                    journeys = new listOfObjects<TrainInfoPerStation *> (presentTrainsInfo); // Need to have the TrainInfoPerStation from the original station
                    lastjourney = journeys;
                }
                else{
                    lastjourney-> next = new listOfObjects<TrainInfoPerStation *> (presentTrainsInfo);
                    lastjourney = lastjourney->next;
                }
         }

         else{
            // See the adjacency list to see the to stations from presentStation and add them to the end of presentStation linked list
           listOfObjects<StationConnectionInfo *> *toStations = adjacency[presentStation->object.stationId].toStations; 
           while(toStations != nullptr){

                listOfObjects<TrainInfoPerStation *> *trains = toStations->object->trains;
                while(trains != nullptr){
                    if(trains->object->journeyCode == presentStation->object.trainInfo->journeyCode){
                        endOfList->next = new listOfObjects<JourneyStationPair>(JourneyStationPair(toStations->object->adjacentStnIndex, presentStation->object.trainInfo ));
                        endOfList = endOfList->next;
                    }
                    listOfObjects<TrainInfoPerStation *> *prevTrain = trains;
                    trains = trains->next;
                    /* delete prevTrain; */
                }
                listOfObjects<StationConnectionInfo *> *prevStation;
                toStations = toStations->next;
                /* delete prevStation; */
           }
         }
         presentStation = presentStation->next;
 }
 if(journeys == nullptr){
    cout <<"No direct journeys available"   << endl;
 }
 else{
         printStationInfo(journeys);
 }
 
  
  return;
}

#endif
