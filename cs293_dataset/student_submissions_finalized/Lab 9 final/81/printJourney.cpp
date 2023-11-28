#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include <queue>
#include "std_headers.h"
#endif

using namespace std;

int Check(int jrnycode,int statnIndx,StationAdjacencyList*adjacency,listOfObjects<TrainInfoPerStation* > *paths){
  StationAdjacencyList v = adjacency[statnIndx];
  listOfObjects<StationConnectionInfo *>* toadj = v.fromStations;
  while(toadj!=nullptr){
    listOfObjects<TrainInfoPerStation *>* jcode = toadj->object->trains;
    while(jcode!=nullptr){
      if(jcode->object->journeyCode==jrnycode){;
        listOfObjects<TrainInfoPerStation*>* newnode = new listOfObjects<TrainInfoPerStation* >(jcode->object);
        listOfObjects<TrainInfoPerStation* > *curr=paths;
        while(curr->next!=nullptr){

          curr=curr->next;
        }
      curr->next=newnode;
      newnode->prev=curr;
        return toadj->object->adjacentStnIndex;
      }
      jcode=jcode->next;
    }
    toadj=toadj->next;
  }
  return -1;
  
}
listOfObjects<TrainInfoPerStation* > * Recurr(int jrnycode,int sourceIndex,int destIndex,StationAdjacencyList*adjacency){
      TrainInfoPerStation* dummy = new TrainInfoPerStation(0,0,0,0);
      listOfObjects<TrainInfoPerStation* > *paths = new listOfObjects<TrainInfoPerStation* >(dummy);
      int stnindex=sourceIndex;
      while(stnindex!=destIndex){
        stnindex = Check(jrnycode,stnindex,adjacency,paths);
        if(stnindex ==-1) return nullptr;
        }
     return paths->next; 
}

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  TrainInfoPerStation* dummy = new TrainInfoPerStation(0,0,0,0);
  listOfObjects<TrainInfoPerStation* > *journeys=new listOfObjects<TrainInfoPerStation* >(dummy);
  listOfObjects<TrainInfoPerStation* > *path;

  int sourceIndex = stnNameToIndex.get(srcStnName)->value;
  int destIndex = stnNameToIndex.get(destStnName)->value;

  StationAdjacencyList l1 = adjacency[sourceIndex];
  StationAdjacencyList l2 = adjacency[destIndex];
  listOfObjects<StationConnectionInfo *>* leaves = l1.fromStations;
  listOfObjects<StationConnectionInfo *>* arrives = l2.toStations;
 
  
  while(leaves!=nullptr){
    listOfObjects<TrainInfoPerStation *>* jrcode = leaves->object->trains;
    while(jrcode!=nullptr){
      int jr_code = jrcode->object->journeyCode;
      listOfObjects<TrainInfoPerStation *>* jrcode_temp=jrcode;
        listOfObjects<StationConnectionInfo *>* arrives1=arrives;
        while(arrives1!=nullptr){
          listOfObjects<TrainInfoPerStation *>* jrcode1 = arrives1->object->trains;
            while(jrcode1!=nullptr){
              int jr_code1=jrcode1->object->journeyCode;
              if(jr_code1==jr_code){
                StationAdjacencyList*adjacency1=adjacency;
                path=Recurr(jr_code1,sourceIndex,destIndex,adjacency1);
                listOfObjects<TrainInfoPerStation* > *curr=journeys;
                while(curr->next!=nullptr){
                  curr=curr->next;
                }
                curr->next=path;
                path->prev=curr;
              }
              jrcode1=jrcode1->next;
              }
              arrives1=arrives1->next;
            } 
            jrcode=jrcode->next;
        }
        leaves=leaves->next;
    }
    
  
  printStationInfo(journeys->next);


  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
