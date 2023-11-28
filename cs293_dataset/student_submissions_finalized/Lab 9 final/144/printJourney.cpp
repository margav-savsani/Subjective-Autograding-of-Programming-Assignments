#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include<queue>

using namespace std;

struct TrainEntryQueue{
  int StationIndex;
  int journeyCode;

  TrainEntryQueue(){}

  TrainEntryQueue(int index, int code){
    StationIndex = index;
    journeyCode = code;
  }
};

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  //Linked list of all possible journeys, each of which stores 
  
  listOfObjects<TrainInfoPerStation*> *toPrint = nullptr;
  //Get the Start and End Index of Journey
  int startIndex, endIndex;
  startIndex = stnNameToIndex.get(srcStnName)->value;
  endIndex = stnNameToIndex.get(destStnName)->value;
  listOfObjects<TrainInfoPerStation*> *allTrains = stationInfo[startIndex];

  //Access Adjaceny List for source
  StationAdjacencyList *startNode = adjacency + startIndex;

  //Iterate through all stations in toStations
  listOfObjects<StationConnectionInfo *> *toStartNode = startNode->toStations;

  //Basic Implementation of Queue
  TrainEntryQueue Q[DICT_SIZE];
  int QueueStart = 0;
  int QueueEnd = 0;
  //Iterate through all stations in toStations
  while(toStartNode != nullptr){
    int index = toStartNode->object->adjacentStnIndex;
    //Iterate through all trains going to adjacent trains
    listOfObjects<TrainInfoPerStation *> *trainNode = toStartNode->object->trains;
    while(trainNode != nullptr){
      //If end found, add journey to linked list toPrint
      if(endIndex == index){
        //cout << "Journey Code Found: " << trainNode->object->journeyCode << endl;
        listOfObjects<TrainInfoPerStation*> *temp = allTrains;

        TrainInfoPerStation* tobeAdded = nullptr;

        while(temp != nullptr){
          if(temp->object->journeyCode == trainNode->object->journeyCode){
            tobeAdded = temp->object;
            break;
          }
          temp = temp->next;
        }
        
        if(toPrint == nullptr){
          toPrint = new listOfObjects<TrainInfoPerStation*>(tobeAdded);
        }

        else{
          temp = toPrint;
          while(temp->next != nullptr){
            temp = temp->next;
          }

          temp->next = new listOfObjects<TrainInfoPerStation*>(tobeAdded);
          temp->next->prev = temp;
        }
      }
      //Else add the station and train in queue
      else{
        Q[QueueEnd] = TrainEntryQueue(index, trainNode->object->journeyCode);
        QueueEnd++;
      }
      trainNode = trainNode->next;
    }
    toStartNode = toStartNode->next;
  }

  //While Queue is not empty
  while(QueueEnd > QueueStart){
    //Pop first element from array
    TrainEntryQueue currEntryQueue = Q[QueueStart];
    QueueStart++;

    //Adjaceny list of current station
    StationAdjacencyList *currentAdjList = adjacency + currEntryQueue.StationIndex;
    int currJourneyCode = currEntryQueue.journeyCode;

    //Iterate through all adjacent stations
    listOfObjects<StationConnectionInfo *> *toCurrNode = currentAdjList->toStations;  

    while(toCurrNode != nullptr){
      int index = toCurrNode->object->adjacentStnIndex;
      listOfObjects<TrainInfoPerStation *> *currTrainNode = toCurrNode->object->trains;
      //Iterate through all trains going to adjacent station
      while(currTrainNode!=nullptr){
        //Access only if train is same as train through which we came to station
        if(currTrainNode->object->journeyCode == currEntryQueue.journeyCode){
          //If journey found, add it to list toPrint
          if(index == endIndex){
            //cout << "Journey Code Found: " << currTrainNode->object->journeyCode << endl;

            listOfObjects<TrainInfoPerStation*> *temp = allTrains;

            TrainInfoPerStation* tobeAdded = nullptr;

            while(temp != nullptr){
              if(temp->object->journeyCode == currTrainNode->object->journeyCode){
                tobeAdded = temp->object;
                break;
              }
              temp = temp->next;
            }
            
            if(toPrint == nullptr){
              toPrint = new listOfObjects<TrainInfoPerStation*>(tobeAdded);
            }

            else{
              temp = toPrint;
              while(temp->next != nullptr){
                temp = temp->next;
              }

              temp->next = new listOfObjects<TrainInfoPerStation*>(tobeAdded);
              temp->next->prev = temp;
            }
          }
          //Else add to queue
          else{
            Q[QueueEnd] = TrainEntryQueue(index, currTrainNode->object->journeyCode);
            QueueEnd++;
          }
        }
        currTrainNode = currTrainNode->next;
      }
      toCurrNode = toCurrNode->next;
    } 
  }
  
  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp

  if(toPrint != nullptr){
    printStationInfo(toPrint);
  }

  else{
    cout << "No direct journeys available" << endl;
  }

  //Free memory
  listOfObjects<TrainInfoPerStation*> *temp = toPrint;
  while(temp != nullptr){
    listOfObjects<TrainInfoPerStation*> *next = temp->next;
    delete temp;
    temp = next;
  }
  return;
}

#endif
