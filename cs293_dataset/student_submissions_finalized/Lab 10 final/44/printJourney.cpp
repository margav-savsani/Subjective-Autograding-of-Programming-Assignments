#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;


void Planner::printPlanJourneys(string srcStnName, string destStnName,  int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  int srcStnIndex = stnNameToIndex.get(srcStnName)->value;  //index of source station
  int destStnIndex = stnNameToIndex.get(destStnName)->value;  // index of destination station

  deque<int> qOfstnIndex;   // queue to store current station indexes
  qOfstnIndex.push_back(srcStnIndex);   // add source station to the queue
  int* parentStns = new int[DICT_SIZE];   //stores parent station 
  
  //dictionary of stations and the trains reaching them, out of the ones leaving source station
  Dictionary<listOfObjects<TrainInfoPerStation*>*> trInfoPerstn;

  //storing the source station
  Entry<listOfObjects<TrainInfoPerStation*>*> station(stationInfo[srcStnIndex]);  // storing the info of all trains at the source station
  station.key = srcStnName; //source station key
  trInfoPerstn.put(station);

  while(!qOfstnIndex.empty()){  //modified bfs algorithm
    if(qOfstnIndex.front() == destStnIndex && qOfstnIndex.size()==1){
      listOfObjects<TrainInfoPerStation*>* listOfTrains = trInfoPerstn.get(destStnName)->value; //list of trains reaching the destination station
      
      printStationInfo(listOfTrains);   //printing the list of all trains reaching the destination after leaving source
      
      trInfoPerstn.remove(stnNameToIndex.getKeyAtIndex(destStnIndex)); //removing the destination station from dictionary as it can be reached again from some other path
    }
    else{    
      listOfObjects<StationConnectionInfo *> *adjStn = adjacency[qOfstnIndex.front()].toStations; //list of adjacent stations
      int iterator = 1;  //iterator for inserting the adjacent stations in the queue just after the curernt station
      while(adjStn != nullptr){ //insertion of adjacent stations in the queue
        //leaving the parent station we have to traverse every other adjacent station
        if(parentStns[qOfstnIndex.front()] != adjStn->object->adjacentStnIndex){
          qOfstnIndex.push_back(adjStn->object->adjacentStnIndex);    //insertion in the queue
          parentStns[adjStn->object->adjacentStnIndex] = qOfstnIndex.front();             //storing the parent

          //store all the trains starting from parent station and reaching the station to be stored in the queue
          int parentStnIndex = parentStns[adjStn->object->adjacentStnIndex];
          listOfObjects<TrainInfoPerStation*>* trainsLeavingPerStn = trInfoPerstn.get(stnNameToIndex.getKeyAtIndex(parentStnIndex))->value;  //trains leaving parent station

          listOfObjects<TrainInfoPerStation*>* allTrainsReachingCurrStn = stationInfo[adjStn->object->adjacentStnIndex];  //all trains reaching current station
          listOfObjects<TrainInfoPerStation*>* storeallTrainsReachingCurrStn = allTrainsReachingCurrStn;                  //trailing pointer
          listOfObjects<TrainInfoPerStation*>* trainsReachingCurrStn = nullptr;                                           //trains reaching current station from parent station
          listOfObjects<TrainInfoPerStation*>* storetrainsReachingCurrStn = nullptr;                                      //trailing pointer 2
          bool firstMatch = true; //ensures the first match case of trains
          while(trainsLeavingPerStn != nullptr){  //looping through trains leaving parent station
            while(allTrainsReachingCurrStn != nullptr){   //looping through trains arriving at current station
              if(trainsLeavingPerStn->object->journeyCode == allTrainsReachingCurrStn->object->journeyCode){
                if(firstMatch){   //first match case
                  firstMatch = false;
                  trainsReachingCurrStn = new listOfObjects<TrainInfoPerStation*>(allTrainsReachingCurrStn->object);
                  storetrainsReachingCurrStn = trainsReachingCurrStn;
                }
                else{   //general case
                  trainsReachingCurrStn->next = new listOfObjects<TrainInfoPerStation*>(allTrainsReachingCurrStn->object);
                  trainsReachingCurrStn = trainsReachingCurrStn->next;
                }
                allTrainsReachingCurrStn = allTrainsReachingCurrStn->next;
              }
              else{
                allTrainsReachingCurrStn = allTrainsReachingCurrStn->next;
              }
            }
            allTrainsReachingCurrStn = storeallTrainsReachingCurrStn;   //restoring all trains reaching current station
            trainsLeavingPerStn = trainsLeavingPerStn->next;
          }
          trainsReachingCurrStn = storetrainsReachingCurrStn; //restoring trains reaching current station

          //storing the current station along with the list of arrived trains in the dictonary
          Entry<listOfObjects<TrainInfoPerStation*>*> newstation(trainsReachingCurrStn);
          newstation.key = stnNameToIndex.getKeyAtIndex(adjStn->object->adjacentStnIndex);
          trInfoPerstn.put(newstation);

          iterator++;
        }
        
        adjStn = adjStn->next;

      }
    }
    qOfstnIndex.pop_front();    //deleting the first element from the queue
  }

  


  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
