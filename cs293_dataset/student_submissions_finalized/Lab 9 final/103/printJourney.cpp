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
  
  // cout << "This function is to be implemented by you." << endl;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp

  // Storing the result in a queue
  listOfObjects<TrainInfoPerStation *> *resultHead = nullptr; // Head of result queue
  listOfObjects<TrainInfoPerStation *> *resultTail = nullptr; // Tail of result queue

  int srcStnIndex = stnNameToIndex.get(srcStnName)->value; // Index of source station
  int destStnIndex = stnNameToIndex.get(destStnName)->value; // Index of destination station

  StationAdjacencyList srcStnAdjacency = adjacency[srcStnIndex]; // Adjacency list of source station
  listOfObjects<StationConnectionInfo*> *toStationsFromSrcStnNode = srcStnAdjacency.toStations; // toStations from source station
  while(toStationsFromSrcStnNode != nullptr){ // Traverse toStations
    listOfObjects<TrainInfoPerStation*> *trainNode = toStationsFromSrcStnNode->object->trains; // trains from stations
    int connectedStnIndex = toStationsFromSrcStnNode->object->adjacentStnIndex; // Index of station
    while(trainNode != nullptr){ // Traverse trains
      int TrainJourneyCode = trainNode->object->journeyCode; // journeyCode of train

      // Perform BFS from here
      listOfObjects<int>* stationQueueFront = nullptr; // Front of the station queue
      listOfObjects<int>* stationQueueRear = nullptr; // Rear of the station queue

      stationQueueFront = new listOfObjects<int>(connectedStnIndex); // Initialising the queue
      stationQueueRear = stationQueueFront;

      while(stationQueueFront != nullptr){
        // Dequeue
        int newStnIndex = stationQueueFront->object;
        stationQueueFront = stationQueueFront->next;
        if(stationQueueFront == nullptr)
          stationQueueRear = nullptr;

        if(newStnIndex == destStnIndex){
          // Done
          if(resultHead == nullptr){
            resultHead = new listOfObjects<TrainInfoPerStation*>(trainNode->object);
            resultTail = resultHead;
          } else{
            resultTail->next = new listOfObjects<TrainInfoPerStation*>(trainNode->object);
            resultTail = resultTail->next;
          }

          // Exit out of here
          break;
        }

        listOfObjects<StationConnectionInfo*> *toStationsFromNewStnNode = adjacency[newStnIndex].toStations; // toStations from station
        while(toStationsFromNewStnNode != nullptr){ // Traverse toStations
          if(toStationsFromNewStnNode->object != nullptr){
            listOfObjects<TrainInfoPerStation*> *trainNodeNew = toStationsFromNewStnNode->object->trains; // trains from station
            int connectedStnIndexNew = toStationsFromNewStnNode->object->adjacentStnIndex; // Index of station
            while(trainNodeNew != nullptr){ // Traverse trains
              int TrainJourneyCodeNew = trainNodeNew->object->journeyCode; // journeyCode of train

              if(TrainJourneyCodeNew == TrainJourneyCode){ // If journeyCodes match
                // Enqueue
                if(stationQueueFront == nullptr){
                  stationQueueFront = new listOfObjects<int>(connectedStnIndexNew);
                  stationQueueRear = stationQueueFront;
                } else{
                  stationQueueRear->next = new listOfObjects<int>(connectedStnIndexNew);
                  stationQueueRear = stationQueueRear->next;
                }
              }

              trainNodeNew = trainNodeNew->next;
            }
          }

          toStationsFromNewStnNode = toStationsFromNewStnNode->next;
        }
      }


      trainNode = trainNode->next;
    }   

    toStationsFromSrcStnNode = toStationsFromSrcStnNode->next;
  }

  if(resultHead == nullptr) // If no journeys found
    cout << "No direct journeys available" << endl;
  else
    printStationInfo(resultHead); // Print the journeys
  
  
  return;
}

#endif
