#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include<vector>
using namespace std;

listOfObjects<TrainInfoPerStation *> * bfs(int journeyCode, int index, int dest, StationAdjacencyList *adjacency,int maxStopOvers,int maxTransitTime,int mystoptime,int mytransisttime)
{
  listOfObjects<StationConnectionInfo *> *d = adjacency[index].toStations; // adjacency list
  if (index == dest)
  { // if destination station is index
    return nullptr;
  }
  while (d != nullptr)
  {
    listOfObjects<TrainInfoPerStation *> *toadd = d->object->trains;
    while (toadd != nullptr)
    {
      if (journeyCode == toadd->object->journeyCode)
      {                                                                                       // bfs step
        return bfs(toadd->object->journeyCode, d->object->adjacentStnIndex, dest, adjacency); // bfs step
      }
      toadd = toadd->next; // trains list
    }
    d = d->next;
  }
  return nullptr;
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  int src = stnNameToIndex.get(srcStnName)->value;                                             // index of source station
  int dest = stnNameToIndex.get(destStnName)->value;                                           // index of destination station
  listOfObjects<StationConnectionInfo *> *dummy = adjacency[src].toStations;                   // pointers to adjacency list to source station
  // TrainInfoPerStation *t = new TrainInfoPerStation(0, 0, 0, 0);                                // constructer
  // listOfObjects<TrainInfoPerStation *> *pointer = new listOfObjects<TrainInfoPerStation *>(t); // pointer to last train in linked list
  // listOfObjects<TrainInfoPerStation *> *output = pointer; 
  vector<listOfObjects<TrainInfoPerStation *> *>final;
  int mystops=0;
  int mytranstime=0;                                     
  while (dummy != nullptr)
  {
    listOfObjects<TrainInfoPerStation *> *toadd = dummy->object->trains; // adjacency list to source
    while (toadd != nullptr)
    {
      if (bfs(toadd->object->journeyCode, dummy->object->adjacentStnIndex, dest, adjacency,maxStopOvers,maxTransitTime,mystops,mytranstime)!=nullptr)
      {                                                                          // BFS step
        final.push_back(bfs(toadd->object->journeyCode, dummy->object->adjacentStnIndex, dest, adjacency,maxStopOvers,maxTransitTime,mystops,mytranstime));                                               // updating pointer
      }
      toadd = toadd->next; // next train in train list
    }
    dummy = dummy->next; // next station in adjacencylist
  }
  for(int k=0;k<final.size();k++){

    if (final[k] == nullptr)
    {
      cout << "No direct journey's available" << endl;
    }
    else
    {
      printStationInfo(final[k]);
    }
  }
  return;
}

#endif
