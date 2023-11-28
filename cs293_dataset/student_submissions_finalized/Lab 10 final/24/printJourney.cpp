#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

bool train_yes(int startt,int endd, StationAdjacencyList adjacency[]){
  int j=0;
  int i=0;
  int index_adj;
  if(startt==endd){return true;}
  else if (startt==-1){return false;}
  else{
    listOfObjects<StationConnectionInfo *> *station = adjacency[startt].toStations;//adjacent stations list
    while(station!=nullptr){ //for each adjacent station
      index_adj = station->object->adjacentStnIndex; //adjacent stations of them
      listOfObjects<TrainInfoPerStation *> *X = station->object->trains;
      if(X!=nullptr){
        station=station->next;
        return(train_yes(index_adj,endd,adjacency));
      }
      else return false;
    }
  }
} 
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  int srcStnIndex = stnNameToIndex.get(srcStnName)->value;
  int destStnIndex = stnNameToIndex.get(destStnName)->value;
  //cout<<"srcStnIndex"<<srcStnIndex<<endl;
  //cout<<"destStnIndex"<< destStnIndex<<endl;
  
  listOfObjects <StationConnectionInfo * > *adjstns_srcstn = adjacency[srcStnIndex].toStations;
  
  while(adjstns_srcstn!=nullptr){
    srcStnIndex = adjstns_srcstn->object->adjacentStnIndex;
    cout<<"srcStnIndex"<<srcStnIndex<<endl;
    int no_of_trains=0;
    listOfObjects <TrainInfoPerStation *> *trainslist = adjstns_srcstn->object->trains;     
    while(trainslist!=nullptr){
      no_of_trains=no_of_trains+1;
      if(train_yes(srcStnIndex,destStnIndex,adjacency)){
        cout<<"train exists from "<<srcStnIndex<<" to "<<destStnIndex<<endl;
        //train_yes(srcStnIndex,destStnIndex,adjacency);
      }
      trainslist = trainslist->next;
    }
    adjstns_srcstn = adjstns_srcstn->next;
    cout<<"no_of_trains "<< no_of_trains<<endl;
  }
  
  return;
}

#endif
