#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

// checker to check whether a complete journey is present or not
// works in a recursive way using toStations list
//returns journeycode if present else -1
int checker(int jrCode, listOfObjects<StationConnectionInfo *> *toStations,int destination,StationAdjacencyList adjacency[DICT_SIZE]){
  listOfObjects<StationConnectionInfo *> *currnode = toStations;
  while(currnode!=nullptr){
    listOfObjects<TrainInfoPerStation *>*l = (currnode->object)->trains;
    int len = 0;
    while(l != NULL){
      len++;
      l = l->next;      
    }
    int arr[len];
    l = (currnode->object)->trains;
    len = 0;
    while(l != NULL){
      arr[len] = (l->object)->journeyCode;
      len++;
      l = l->next;      
    }
    bool y = false;
    for(int i=0;i<len;i++){
      if(arr[i]==jrCode){
        y = true;
      }
    }
    if(y)break;
    else currnode = currnode->next;
  }
  //if the train journey stops at some station then return -1
  if(currnode == NULL)return -1;
  // checking if station index is same as destination
  else if((currnode->object)->adjacentStnIndex == destination)return jrCode;
  //else continue with recursion
  else{
    return checker(jrCode,adjacency[(currnode->object)->adjacentStnIndex].toStations,destination,adjacency);
  }
}

//calls checker and then appends journeycodes into a list if completion is present
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{ 
  //getting index of source station
  Entry<int> *currsrc = stnNameToIndex.get(srcStnName);
  int index1 = currsrc->value;
  //getting index of destination station
  Entry<int> *currdest = stnNameToIndex.get(destStnName);
  int index2 = currdest->value;  
  listOfObjects<TrainInfoPerStation *> *list = nullptr; 
  listOfObjects<TrainInfoPerStation *> *train = stationInfo[index1]; 
  int len = 0;
  while(train != NULL){
    len++;
    train = train->next;      
  }
  int arr[len];
  train = stationInfo[index1];
  len = 0;
  while(train != NULL){
    arr[len] = (train->object)->journeyCode;
    len++;
    train = train->next;      
  }
  train = stationInfo[index1];
  int truearray[len] ; 
  for(int i = 0;i<len;i++){   
    truearray[i] = checker(arr[i],adjacency[index1].toStations,index2,adjacency);      
  }
  for(int i = 0;i<len;i++){
    if(truearray[i]!=-1){
      if(list==nullptr){
        list = new listOfObjects<TrainInfoPerStation *>(train->object);        
      }
      else{
        list->next = new listOfObjects<TrainInfoPerStation *>(train->object);
        (list->next)->prev = list;
        list = list->next;
      }
    } 
    train = train->next;     
  }
  if(list == nullptr){
    cout<<"No journeys found between given source and destination"<<endl;
  }
  else{
    while(list->prev !=NULL){
      list = list->prev;      
    }
    printStationInfo(list);
  }
  return;
}
#endif
