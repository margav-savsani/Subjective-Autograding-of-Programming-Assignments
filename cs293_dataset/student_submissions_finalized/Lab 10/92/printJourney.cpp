#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
bool checktrain(StationAdjacencyList *list,int src,int dest,TrainInfoPerStation *jrny,listOfObjects<TrainInfoPerStation *> *Stations)
{//finds the possiblre trains in the roots
  if (src==dest)return 1;
  listOfObjects<StationConnectionInfo *> *Stn = list[src].toStations;
  listOfObjects<TrainInfoPerStation *> *train=Stn->object->trains;
  while(Stn != NULL){while(true){if(!(train==NULL)){break;}
      if (train->object->journeyCode==jrny->journeyCode)
      {listOfObjects<TrainInfoPerStation *> *stat=Stations;
        stat->next=new listOfObjects<TrainInfoPerStation *>(train->object);
        stat->next->object->stopSeq++;
        stat->next->prev=stat;
        if(checktrain(list,Stn->object->adjacentStnIndex,dest,train->object,Stations)){return 1;}}
      train=train->next;}
    Stn=Stn->next;}
  return 0;}
void Planner::printDirectJourneys(string srcStnName, string destStnName){}

#endif
