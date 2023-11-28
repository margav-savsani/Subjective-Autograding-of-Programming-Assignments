#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <bits/stdc++.h>
using namespace std;


void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  int srcStnIndex = stnNameToIndex.get(srcStnName)->value;  //source station name index
  int destStnIndex = stnNameToIndex.get(destStnName)->value;  // destination station name index

  deque<int> qOfstnIndex;   // the main queue of bfs which stores the current station indexes
  qOfstnIndex.push_back(srcStnIndex);   //adding the source station to the queue
  int* parentStns = new int[DICT_SIZE];   //array for storing the indexes of parent stations of the each station
  
  //dictionary of stations and the trains reaching them out of the ones leaving source station
  Dictionary<listOfObjects<TrainInfoPerStation*>*> trInfoStn;

  //storing the source station
  Entry<listOfObjects<TrainInfoPerStation*>*> station(stationInfo[srcStnIndex]);  //storing the info of all trains at the source station
  station.key = srcStnName; //source station key
  trInfoStn.put(station);

  while(!qOfstnIndex.empty()){  //modified bfs algorithm
    if(qOfstnIndex.front() == destStnIndex){
      listOfObjects<TrainInfoPerStation*>* listOfTrains = trInfoStn.get(srcStnName)->value; //getting the list of trains reaching the destination station
      
      printStationInfo(listOfTrains);   //printing the output which is list of all trains reaching the destination after leaving source
      
      trInfoStn.remove(stnNameToIndex.getKeyAtIndex(destStnIndex)); //removing the destination station from dictionary as it can be reached again via other path
    }
    else{    
      listOfObjects<StationConnectionInfo *> *adjStn = adjacency[qOfstnIndex.front()].toStations; //list of adjacent stations
      int itr = 1;  //iterator for inserting the adjacent stations in the queue just after the curernt station
      while(adjStn != nullptr){ //insertion of adjacent stations in the queue
        //leaving the parent station we have to traverse every other adjacent station
        if(parentStns[qOfstnIndex.front()] != adjStn->object->adjacentStnIndex){
          qOfstnIndex.insert(qOfstnIndex.begin()+itr, adjStn->object->adjacentStnIndex);  //insertion in the queue
          parentStns[adjStn->object->adjacentStnIndex] = qOfstnIndex.front();             //storing the parent

          //store all the trains starting from parent station and reaching the station to be stored in the queue
          int parentStnIndex = parentStns[adjStn->object->adjacentStnIndex];
          listOfObjects<TrainInfoPerStation*>* trainsLeavingPStn = trInfoStn.get(stnNameToIndex.getKeyAtIndex(parentStnIndex))->value;  //trains leaving parent station

          
          listOfObjects<TrainInfoPerStation*>* allTrainsReachingCurrStn = stationInfo[adjStn->object->adjacentStnIndex];  //all trains reaching current station
          listOfObjects<TrainInfoPerStation*>* storeallTrainsReachingCurrStn = allTrainsReachingCurrStn;                  //recovery for above pointer
          listOfObjects<TrainInfoPerStation*>* trainsReachingCurrStn = nullptr;                                           //trains reaching current station from parent station
          listOfObjects<TrainInfoPerStation*>* storetrainsReachingCurrStn = nullptr;                                      //recovery for above pointer
          bool firstMatch = true; //ensures the first match case of trains
          while(trainsLeavingPStn != nullptr){  //looping through trains leaving parent station
            while(allTrainsReachingCurrStn != nullptr){   //looping through trains arriving at current station
              if(trainsLeavingPStn->object->journeyCode == allTrainsReachingCurrStn->object->journeyCode){
                if(firstMatch){   //first match case
                  firstMatch = false;
                  trainsReachingCurrStn = new listOfObjects<TrainInfoPerStation*>(allTrainsReachingCurrStn->object);
                  storetrainsReachingCurrStn = trainsReachingCurrStn;
                }
                else{   //general case
                  trainsReachingCurrStn->next = new listOfObjects<TrainInfoPerStation*>(allTrainsReachingCurrStn->object);
                  trainsReachingCurrStn = trainsReachingCurrStn->next;
                }
              }
              allTrainsReachingCurrStn = allTrainsReachingCurrStn->next;
            }
            allTrainsReachingCurrStn = storeallTrainsReachingCurrStn;   //restoring all trains reaching current station
            trainsLeavingPStn = trainsLeavingPStn->next;
          }
          trainsReachingCurrStn = storetrainsReachingCurrStn; //restoring trains reaching current station

          //storing the current station along with the list of arrived trains in the dictonary
          Entry<listOfObjects<TrainInfoPerStation*>*> newstation(trainsReachingCurrStn);
          newstation.key = stnNameToIndex.getKeyAtIndex(adjStn->object->adjacentStnIndex);
          trInfoStn.put(newstation);

          itr++;
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
