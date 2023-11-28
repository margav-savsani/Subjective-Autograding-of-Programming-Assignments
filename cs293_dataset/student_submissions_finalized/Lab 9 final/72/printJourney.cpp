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

  // Indices of source and destination stations
  int srcStnIdx = stnNameToIndex.get(srcStnName)->value;
  int destStnIdx = stnNameToIndex.get(destStnName)->value;
  // List to store direct journeys(initialized with a dummy element at first poosition)
  listOfObjects<TrainInfoPerStation *> *myTrainList = new listOfObjects<TrainInfoPerStation *>(new TrainInfoPerStation(0,0,0,0));
  listOfObjects<TrainInfoPerStation *> *myTail = myTrainList;

  listOfObjects<StationConnectionInfo *> * adjToList = adjacency[srcStnIdx].toStations;
  //Iterating through all stations
  while(adjToList != nullptr){
    if(adjToList->object == nullptr)break;
    listOfObjects<TrainInfoPerStation *> *ltrai = adjToList->object->trains;
    //Iterating through all trains available
    while(ltrai != nullptr){
      int idx = adjToList->object->adjacentStnIndex;
      bool destfound = false;
      while(true){
        // Checking whether a train with specific journey code reahces destination
        if(idx == destStnIdx){
          destfound = true;
          break;
        }
        bool Jcodefound = false;
        listOfObjects<StationConnectionInfo *> *myvar2 = adjacency[idx].toStations;
        while(myvar2 != nullptr){
          if(myvar2->object == nullptr)break;
          listOfObjects<TrainInfoPerStation *> *myvar3 = myvar2->object->trains;
          while(myvar3 != nullptr){
            if(myvar3->object->journeyCode == ltrai->object->journeyCode){
              // If destination is reahced
              idx = myvar2->object->adjacentStnIndex;
              Jcodefound = true;
              break;
            }
            myvar3 = myvar3->next;
          }
          if(Jcodefound)break;
          myvar2 = myvar2->next;
        }
        if(!Jcodefound)break;
      }
      if(destfound){
        // Adding the journey to our list
        myTail->next = new listOfObjects<TrainInfoPerStation *>(ltrai->object);
        myTail = myTail->next;
      }
      ltrai = ltrai->next;
    }
    adjToList = adjToList->next;
  }
  // Printing the Direct Journeys
  if(myTrainList->next == nullptr){
    cout << "No direct journeys available\n";
  }else printStationInfo(myTrainList->next);
  
  
  

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
