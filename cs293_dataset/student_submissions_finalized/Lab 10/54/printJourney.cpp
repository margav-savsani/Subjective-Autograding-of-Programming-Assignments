#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

int BFSforward(listOfObjects<StationConnectionInfo *> *currStn, StationConnectionInfo *BFSarr[], int destStnindex)
{
  if(currStn == nullptr) return 0;
  else
  {
    StationConnectionInfo **NEWBFSarr;
    int adj_vertices = 0;
    while(currStn != nullptr)
    {
      BFSarr[adj_vertices] = currStn->object;
      adj_vertices++;
      if(currStn->object->adjacentStnIndex == destStnindex)
      {
        return -1;
      }
      currStn = currStn->next;
    }
  }
}

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  Entry<int> *srcStnIndexEntry = stnNameToIndex.get(srcStnName);
  int srcStnindex = srcStnIndexEntry->value;
  Entry<int> *destStnIndexEntry = stnNameToIndex.get(destStnName);
  int destStnindex = destStnIndexEntry->value;

  StationAdjacencyList *startlist = &adjacency[srcStnindex];
  StationConnectionInfo ***arr;
  StationConnectionInfo **BFSarr;

  int cur_tostns = 0;

  while(true)
  {
    listOfObjects<StationConnectionInfo *> *currStn = startlist->toStations;
    StationConnectionInfo **BFSarr;
    int adj_vertices = 0;
    listOfObjects<StationConnectionInfo *> *Queue = currStn;
    while(Queue != nullptr)
    {
      StationConnectionInfo *head = currStn->object;
      while(currStn->object != nullptr)
      {

      }
      BFSarr[adj_vertices] = currStn->object;
      adj_vertices++;
      if(currStn->object->adjacentStnIndex == destStnindex)
      {
        break;
      }
      currStn = currStn->next;
    }
    if(currStn != nullptr) break;
    else
    {
      arr[cur_tostns] = BFSarr;
      cur_tostns++;
    }
  }

  //cout << "This function is to be implemented by you." << endl;
  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif