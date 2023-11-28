#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include "dictionary.h"
#include "planner.h"
using namespace std;

struct JourneyStationPair{
    int stationId;
    listOfObjects<TrainInfoPerStation *> *trainInfo; // The info at the source station
    listOfObjects<TrainInfoPerStation *> *lastTrainInfo; // The info at the source station
    int stopsMade = 0;

    JourneyStationPair(){
        stationId = -1;
        trainInfo = nullptr;
        lastTrainInfo = nullptr;
    }

    JourneyStationPair(int stationId){
        this->stationId = stationId;
        trainInfo = nullptr;
        lastTrainInfo = nullptr;
    }

    JourneyStationPair(int stationId, TrainInfoPerStation *trainInfo){
        this->stationId = stationId;
        this->trainInfo = new listOfObjects<TrainInfoPerStation*>(trainInfo);
        lastTrainInfo = trainInfo;
    }
};
bool transitTime(TrainInfoPerStation *train1, TrainInfoPerStation *train2, int maxTransitTime){
    int day1 = -1, day2 = -1;
    for(int i = 0; i < 7; i++){
        if(train1->daysOfWeek[i]){
            day1 = i;
        } 
        if(train2->daysOfWeek[i]){
            day2 = i;
        } 
    }
    if (day1 == day2){
        return (train2->depTime - train1->arrTime) < maxTransitTime && (train2->depTime - train1->arrTime) > 0;
    }
    else return false;

}
  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  
  cout << "This function is to be implemented by you." << endl;

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  
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
                TrainInfoPerStation *presentTrainsInfo = presentStation->object.lastTrainInfo->object;
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
                    if(trains->object->journeyCode == presentStation->object.lastTrainInfo->journeyCode){
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
