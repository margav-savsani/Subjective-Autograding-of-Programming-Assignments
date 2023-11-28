#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

int meow(int jCode,int destValue,StationAdjacencyList adjacency[DICT_SIZE],listOfObjects<StationConnectionInfo *>* toStations){
  listOfObjects<StationConnectionInfo *> *list=toStations;    
  while(list!=NULL){
    int zs,a=0;listOfObjects<TrainInfoPerStation *> *x=list->object->trains;
    while(x!=NULL){
      x=x->next;
      zs++;
    }
    int* arr=new int(zs);
    for(int i=0;i<zs;i++){
      arr[i]=x->object->journeyCode;
      x=x->next;
    }
    for(int i=0;i<zs;i++){
      if(arr[i]==jCode){
        a=1;
      }
    }
    if(a==1) break;
    else list=list->next;
  }
  return jCode;
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  Entry<int> *a = stnNameToIndex.get(srcStnName);
  Entry<int> *b = stnNameToIndex.get(destStnName);

  int stnIndex = a->value;
  StationAdjacencyList src = adjacency[stnIndex];
  listOfObjects<TrainInfoPerStation*> *srcstn=stationInfo[stnIndex];

  listOfObjects<StationConnectionInfo *> *toStns=src.toStations;

  int destIndex= b->value;
  //StationAdjacencyList dest = adjacency[destIndex];
  //listOfObjects<TrainInfoPerStation*> *deststn=stationInfo[destIndex];
  int sz;
  listOfObjects<TrainInfoPerStation*> *jc=srcstn;
  while(jc!=NULL){
    jc=srcstn->next;
    sz++;
  }

  int* arr_tr=new int(sz);
  int* arr_fin=new int(sz);

  for(int i=0;i<sz;i++){
    arr_tr[i]=srcstn->object->journeyCode;
    srcstn=srcstn->next;
  }

  for(int i=0;i<sz;i++){
    int my=meow(arr_tr[i],destIndex,adjacency,toStns);
    arr_fin[i]=my;
  }

  listOfObjects<TrainInfoPerStation*> *lst=nullptr;

  if(lst!=nullptr){
    printStationInfo(lst);
  }
  else cout<<"No direct journeys available"<<endl;
  
  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}


#endif

