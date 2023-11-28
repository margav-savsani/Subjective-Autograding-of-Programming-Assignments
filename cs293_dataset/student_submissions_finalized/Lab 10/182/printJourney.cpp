#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  
  cout << "This function is to be implemented by you." << endl;
}

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
       
      }
      train=train->next;
    }
    Stn=Stn->next;
  }
  return false;
}

#endif
