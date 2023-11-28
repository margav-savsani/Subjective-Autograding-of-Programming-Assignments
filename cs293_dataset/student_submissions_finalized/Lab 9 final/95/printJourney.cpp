#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
listOfObjects<TrainInfoPerStation*>* print_journey_with_jcode(string srcStnName,int jcode,int curr_index,int destStnIndex,string destStnName,StationAdjacencyList adjacency[DICT_SIZE],listOfObjects<TrainInfoPerStation*>*&a){
  listOfObjects<StationConnectionInfo*>*stations=adjacency[curr_index].toStations;
  if(stations==NULL){
    return a;
  }
  while(stations!=NULL){
    listOfObjects<TrainInfoPerStation*>*trains=stations->object->trains;
    while (trains!=NULL)
    {
      if(trains->object->journeyCode==jcode&&stations->object->adjacentStnIndex==destStnIndex){
        if(a==NULL){
          a=trains;
        }
        else{
        a->next=trains;
        a=a->next;}
        return a;
      }
      else if(trains->object->journeyCode==jcode){
        print_journey_with_jcode(srcStnName,jcode,stations->object->adjacentStnIndex,destStnIndex,destStnName,adjacency,a);
        break;
      }
      trains=trains->next;
    }
    stations=stations->next;
  }
  return a;
}
void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  listOfObjects<TrainInfoPerStation*>*all_journeys;
int a=stnNameToIndex.get(srcStnName)->value;
int b=stnNameToIndex.get(destStnName)->value;
 listOfObjects<TrainInfoPerStation*>*p;

listOfObjects<StationConnectionInfo*>*stations=adjacency[a].toStations;

while (stations!=NULL)
{  listOfObjects<TrainInfoPerStation*>*trains=stations->object->trains;
int index=stations->object->adjacentStnIndex;
  while(trains!=NULL){
     
      if(b==index){
        if(all_journeys==NULL){
        all_journeys=trains;}
        else{
          all_journeys->next=trains;
          all_journeys=all_journeys->next;
        }
      }
     
      p=print_journey_with_jcode(srcStnName,trains->object->journeyCode,index,b,destStnName,adjacency,all_journeys);
      trains=trains->next;
  }
  stations=stations->next;
}
if(p!=NULL){
while (p->prev!=NULL)
{
  p=p->prev;
}
}

printStationInfo(p);
  // insert your code here
  
  
  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
