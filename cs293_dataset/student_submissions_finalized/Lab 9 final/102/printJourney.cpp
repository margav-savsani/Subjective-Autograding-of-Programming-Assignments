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
  int sourceStnIndex = stnNameToIndex.get(srcStnName)->value;  
  int dstnStnIndex = stnNameToIndex.get(destStnName)->value;  

  int* pStns = new int[DICT_SIZE];   //array for storing the indexes of parent stations of the each station
  deque<int> queueOfstnIndex;   // the main queue of bfs which stores the current station indexes
  queueOfstnIndex.push_back(sourceStnIndex);   //adding the source station to the end of the queue
  
  
  //dictionary of stations and the trains reaching them out of the ones leaving source station
  Dictionary<listOfObjects<TrainInfoPerStation*>*> trainInfoStnDict;

  //storing the source station
  Entry<listOfObjects<TrainInfoPerStation*>*> stationEntry(stationInfo[sourceStnIndex]);  //storing the info of all trains at the source station
  stationEntry.key = srcStnName; //source station key
  trainInfoStnDict.put(stationEntry);

  while(!queueOfstnIndex.empty()){  //modified bfs algorithm
    if(queueOfstnIndex.front() == dstnStnIndex && queueOfstnIndex.size()==1){
      listOfObjects<TrainInfoPerStation*>* listOfTrains = trainInfoStnDict.get(destStnName)->value; //getting the list of trains reaching the destination station
      printStationInfo(listOfTrains);   //printing the output which is list of all trains reaching the destination after leaving source
      
      trainInfoStnDict.remove(stnNameToIndex.getKeyAtIndex(dstnStnIndex)); //removing the destination station from dictionary as it can be reached again via other path
    }
    else{    
      listOfObjects<StationConnectionInfo *> *adjStn = adjacency[queueOfstnIndex.front()].toStations; //list of adjacent stations
      while(adjStn != nullptr){ //insertion of adjacent stations in the queue
        //leaving the parent station we have to traverse every other adjacent station
        if(pStns[queueOfstnIndex.front()] != adjStn->object->adjacentStnIndex){
          queueOfstnIndex.push_back(adjStn->object->adjacentStnIndex);    //insertion in the queue
          pStns[adjStn->object->adjacentStnIndex] = queueOfstnIndex.front();             //storing the parent

          //store all the trains starting from parent station and reaching the station to be stored in the queue

          
          listOfObjects<TrainInfoPerStation*>* listofTrainsReachingCurrStn = stationInfo[adjStn->object->adjacentStnIndex];  
          listOfObjects<TrainInfoPerStation*>* listOfallTrainsReachingCurrStn = listofTrainsReachingCurrStn;                  
          listOfObjects<TrainInfoPerStation*>* storetrainsReachingCurrStn = nullptr;                                      
          listOfObjects<TrainInfoPerStation*>* trainReachingCurrStn = nullptr;  

          int parentStnIndex = pStns[adjStn->object->adjacentStnIndex];
          listOfObjects<TrainInfoPerStation*>* trainsLeavingPStn = trainInfoStnDict.get(stnNameToIndex.getKeyAtIndex(parentStnIndex))->value;  //trains leaving parent station


          bool matchExist = true;
          while(trainsLeavingPStn != nullptr){  
            while(listofTrainsReachingCurrStn != nullptr){   //looping through trains arriving at current station
              if(trainsLeavingPStn->object->journeyCode == listofTrainsReachingCurrStn->object->journeyCode){
                if(matchExist){   //first match case
                  trainReachingCurrStn = new listOfObjects<TrainInfoPerStation*>(listofTrainsReachingCurrStn->object);
                  storetrainsReachingCurrStn = trainReachingCurrStn;
                  matchExist = false;
                }
                else{   //general case
                  trainReachingCurrStn->next = new listOfObjects<TrainInfoPerStation*>(listofTrainsReachingCurrStn->object);
                  trainReachingCurrStn = trainReachingCurrStn->next;
                }
              }
              listofTrainsReachingCurrStn = listofTrainsReachingCurrStn->next;
            }
            listofTrainsReachingCurrStn = listOfallTrainsReachingCurrStn;   //restoring all trains reaching current station
            trainsLeavingPStn = trainsLeavingPStn->next;
          }
          trainReachingCurrStn = storetrainsReachingCurrStn; //restoring trains reaching current station

          Entry<listOfObjects<TrainInfoPerStation*>*> nextstnEntry(trainReachingCurrStn);
          nextstnEntry.key = stnNameToIndex.getKeyAtIndex(adjStn->object->adjacentStnIndex);
          trainInfoStnDict.put(nextstnEntry);

        }
        
        adjStn = adjStn->next;

      }
    }
    queueOfstnIndex.pop_front();    //deleting the first element from the queue
  }
  return;
}
#endif
