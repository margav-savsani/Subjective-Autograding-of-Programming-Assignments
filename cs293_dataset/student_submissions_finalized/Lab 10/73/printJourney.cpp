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
{
  if (src==dest)
    return true;
  listOfObjects<StationConnectionInfo *> *Stn = list[src].toStations;
  if (Stn == nullptr)
    return false;
  listOfObjects<TrainInfoPerStation *> *train=Stn->object->trains;
  while(Stn != nullptr)
  {
    while(train != nullptr)
    {
      if (train->object->journeyCode==jrny->journeyCode)
      {
        listOfObjects<TrainInfoPerStation *> *st1=Stations;
        while(st1->next != nullptr)
          st1=st1->next;
        TrainInfoPerStation *sample;
        sample=train->object;
        st1->next=new listOfObjects<TrainInfoPerStation *>(sample);
        st1->next->object->stopSeq=st1->object->stopSeq+1;
        st1->next->prev=st1;
        return checktrain(list,Stn->object->adjacentStnIndex,dest,train->object,Stations);
      }
      train=train->next;
    }
    Stn=Stn->next;
  }
  return false;
}
void Planner::printPlanJourneys(string srcStnName, string destStnName,int max,int min)
{
  if (srcStnName == destStnName)
    return;

  // insert your code here
  Entry<int> *srcname,*destname;
  int src,dest;
  srcname=stnNameToIndex.get(srcStnName);
  destname=stnNameToIndex.get(destStnName);
  src=srcname->value;
  dest=destname->value;
  listOfObjects<TrainInfoPerStation *> *stn;
  TrainInfoPerStation *sample;
  sample=new TrainInfoPerStation(-1,-1,0,0);
  stn=new listOfObjects<TrainInfoPerStation *> (sample);
  listOfObjects<StationConnectionInfo *> *Stn = adjacency[src].toStations;
  if (Stn==nullptr)
  {
    cout<<"No Trains"<<endl;
    return;
  }
  listOfObjects<TrainInfoPerStation *> *train=Stn->object->trains;
  while(Stn!=nullptr)
  {
    while(train != nullptr)
    {
      if (checktrain(adjacency,src,dest,train->object,stn))
      {
        printStationInfo(stn->next);
        stn->next=nullptr;
      }
      train=train->next;
    }
    Stn=Stn->next;  
  }
  return;
}

#endif