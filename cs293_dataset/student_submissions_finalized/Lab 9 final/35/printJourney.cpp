#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <queue>

using namespace std;

//This func returns the queue containing the possible journey codes to be printed
//This will find the possible journeys by taking trains common between trains leaving from src and trains arriving at dest
queue<int > possibletrainJrcodes(int src,int dest,listOfObjects<TrainInfoPerStation *> **stationInfo){
  queue<int > Possibletrains;
  listOfObjects<TrainInfoPerStation *> *s=stationInfo[src];
  while(s!=nullptr){
    if(s->object->depTime!=-1) {
      listOfObjects<TrainInfoPerStation *> *d=stationInfo[dest];
      while(d!=nullptr){
        if(d->object->arrTime!=-1 && d->object->journeyCode==s->object->journeyCode) {
          if(s->object->stopSeq==d->object->stopSeq-1) Possibletrains.push(s->object->journeyCode);
          break;
        }
        d=d->next; 
      }
    }
    s=s->next; 
  }
  return Possibletrains;
};

//This will traverse through and adds path to DirectJourneys
listOfObjects<TrainInfoPerStation *> *BFS(int src,int dest,StationAdjacencyList*adjacency,listOfObjects<TrainInfoPerStation *> **stationInfo){
  listOfObjects<TrainInfoPerStation *> *DirectJourneys = nullptr;
  listOfObjects<TrainInfoPerStation *> *tempDirectJrnys=nullptr;
  listOfObjects<StationConnectionInfo *> *fromSrc = adjacency[src].toStations;
  queue<StationConnectionInfo*> Q;
  while(fromSrc!=nullptr){
    StationConnectionInfo* StationNode = new StationConnectionInfo();
    StationNode->adjacentStnIndex = fromSrc->object->adjacentStnIndex;
    StationNode->trains = fromSrc->object->trains;
    Q.push(StationNode);
    fromSrc = fromSrc->next;
  }
  while (!Q.empty()){
    StationConnectionInfo* curr=Q.front();
    Q.pop();
    listOfObjects<StationConnectionInfo *> *fromCurr=adjacency[curr->adjacentStnIndex].toStations;
    while(fromCurr!=nullptr){
      int fromCurrIndex=fromCurr->object->adjacentStnIndex;
      listOfObjects<TrainInfoPerStation*>* validtrains=nullptr;
      listOfObjects<TrainInfoPerStation*>* fromCurrTrains=fromCurr->object->trains;
      queue<int> possibletrainJourneycodes = possibletrainJrcodes(src,dest,stationInfo);
      //If the fromCurr train is in possibletrainJourneycodes then add it to DirectJourneys 
      /*if(possibletrainJourneycodes.Contains(fromCurr)){
        if(validtrains == nullptr){
          validtrains=new listOfObjects<TrainInfoPerStation*>(fromCurrTrains->object);
        }
      }*/
      StationConnectionInfo* StationNode = new StationConnectionInfo();
      StationNode->adjacentStnIndex = fromCurrIndex;
      StationNode->trains = fromCurrTrains;
      if(validtrains!=nullptr){   
        if(fromCurrIndex==dest){
          if(DirectJourneys==nullptr){
            DirectJourneys=validtrains;
            tempDirectJrnys=DirectJourneys;
          }
          else{
            tempDirectJrnys->next=validtrains;
          }
        }          
        Q.push(StationNode);
      }
      fromCurr = fromCurr->next;
    }
  return DirectJourneys;
}
}

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  // insert your code here
  int src = stnNameToIndex.get(srcStnName)->value;
  int dest = stnNameToIndex.get(destStnName)->value;

  // BFS function gives the list of directjourneys as a listOfObjects<TrainInfoPerStation *>
  listOfObjects<TrainInfoPerStation *> *DirectJourneys = BFS(src,dest,adjacency,stationInfo);

  // printing part
  if(DirectJourneys != nullptr){
    while(DirectJourneys!=nullptr){
    // printStationInfo is a private member function of the Planner class
    // It is declared in planner.h and implemented in planner.cpp
    printStationInfo(DirectJourneys);
    cout << endl;
    DirectJourneys = DirectJourneys->next;
    }
    }
  else cout << "No direct journeys available" << endl;
  return;
}

#endif