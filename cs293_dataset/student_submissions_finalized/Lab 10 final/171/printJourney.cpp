#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

bool dest(int jrnycode,int srind,int desind,StationAdjacencyList adjacency[]){        //function which returns true if there exist a direct journey from 
  if(srind==-1)                                                                       //source index to dest index with a given journeycode
    return false;
  if(srind==desind)
    return true;
  int index;
  listOfObjects<StationConnectionInfo *> *s = adjacency[srind].toStations;
  while(s!=NULL){
    int p=0;
    listOfObjects<TrainInfoPerStation *> *t = s->object->trains;
    while(t!=NULL){
      if(t->object->journeyCode==jrnycode){
        p++;
        index=s->object->adjacentStnIndex;
        break;
      }
      t=t->next;
    }
    if(p!=0)
      return dest(jrnycode,index,desind,adjacency);

    s=s->next;
  }
  return false;
}

  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  int srind = stnNameToIndex.get(srcStnName)->value;
  int desind = stnNameToIndex.get(destStnName)->value;
  
  listOfObjects<StationConnectionInfo *> *stations = adjacency[srind].toStations;

  TrainInfoPerStation *n = new TrainInfoPerStation(0,0,0,0);
  listOfObjects<TrainInfoPerStation *> *ans = new listOfObjects<TrainInfoPerStation *>(n);

  while(stations!=NULL){                                                      //checking with every train journeycode in 
    listOfObjects<TrainInfoPerStation *> *t = stations->object->trains;       //stationconnectioninfo in tostations of source station
    while(t!=NULL){
      if(dest(t->object->journeyCode,stations->object->adjacentStnIndex,desind,adjacency)){
        listOfObjects<TrainInfoPerStation *> *final = ans;
        while(final->next!=NULL){
          final=final->next;
        }
        final->next = new listOfObjects<TrainInfoPerStation *>(t->object);
      }
      t=t->next;
    }
    stations=stations->next;

  }

  if(ans->next==NULL)
    cout << "No direct journeys available" << endl;
  printStationInfo(ans->next);
  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  
  return;
}

#endif
