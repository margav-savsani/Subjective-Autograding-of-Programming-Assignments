#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include "planner.h"
using namespace std;
  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  if (srcStnName == destStnName)
    return;

  // insert your code here
  Entry<int> *src,*destname;
  int s,d;
  src=stnNameToIndex.get(srcStnName);
  destname=stnNameToIndex.get(destStnName);
  s=src->value;
  d=destname->value;
  listOfObjects<TrainInfoPerStation *> *stn;
  TrainInfoPerStation *dummy;
  dummy=new TrainInfoPerStation(0,0,0,0);
  stn=new listOfObjects<TrainInfoPerStation *> (dummy);
  listOfObjects<StationConnectionInfo *> *Stn = adjacency[s].toStations;
  if (Stn==nullptr)
  {
    cout<<"No Trains"<<endl;
    return;
  }
  listOfObjects<TrainInfoPerStation *> *trns=Stn->object->trains;
  while(Stn!=nullptr)
  {
    while(trns != nullptr)
    {
      if (BST(s,d,trns->object,stn))
      {
        printStationInfo(stn->next);
      }
      trns=trns->next;
    }
    Stn=Stn->next;
  }
}

bool BST(int src,int dest,TrainInfoPerStation *jrny,listOfObjects<TrainInfoPerStation *> *Stations)
{
  if (src==dest)
    return true;
  listOfObjects<StationConnectionInfo *> *Stn=new listOfObjects<StationConnectionInfo *>;
  Stn = adjacency[src].toStations;
  if (Stn == nullptr)
    return false;
  listOfObjects<TrainInfoPerStation *> *trns=Stn->object->trains;
  while(Stn != nullptr)
  {
    while(trns != nullptr)
    {
      if (trns->object->==jrny->)
      {
        listOfObjects<TrainInfoPerStation *> *st1=Stations;
        while(st1->next != nullptr)
          st1=st1->next; 
          
      }
    }
    trns=trns->next;
  }
  Stn=Stn->next;
  return false;
}

#endif
