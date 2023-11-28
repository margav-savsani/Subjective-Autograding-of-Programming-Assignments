#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

void recursion(TrainInfoPerStation *currTrain, int currStopOvers, int maxTransitTime, int maxStopOvers, int index, int destStnIndex, StationAdjacencyList *adjacency, listOfObjects<TrainInfoPerStation *> *p, listOfObjects<TrainInfoPerStation *> *upto)
{                                                                   // recursion
  upto->next = new listOfObjects<TrainInfoPerStation *>(currTrain); // storing our train in upto
  upto->next->prev = upto;
  upto = upto->next;
  if (currStopOvers > maxStopOvers)
  { // base case of recursion
    return;
  }
  else if (index == destStnIndex)
  { // base case of recursion
    listOfObjects<TrainInfoPerStation *> *temp = upto;
    while (temp->prev != nullptr)
    {                                                                   // ends while loop
      p->next = new listOfObjects<TrainInfoPerStation *>(temp->object); // adding our trains list to pointer which we output
      p->next->prev = p;
      p = p->next;
      temp = temp->prev;
    }
    return;
  }
  else
  {
    listOfObjects<StationConnectionInfo *> *currStnAdjList = adjacency[index].toStations; //  Adjacency list for current Station
    listOfObjects<TrainInfoPerStation *> *copy = upto;                                    // dummy variable for upto
    while (currStnAdjList != nullptr)
    {                                                                                    // loop through all stations adjancent to current stations
      listOfObjects<TrainInfoPerStation *> *currtrains = currStnAdjList->object->trains; // all trains between current station and adjacent station
      while (currtrains != nullptr)
      { // ends while loop when condition is false
        if (currtrains->object->journeyCode == index)
        { // we donot add that train when journey code is not changing
          copy->next = nullptr;
          recursion(currtrains->object, currStopOvers, maxTransitTime, maxStopOvers, currStnAdjList->object->adjacentStnIndex, destStnIndex, adjacency, p, copy);
        }
        else
        { // if journey code is changing we change add the train in the data
          copy->next = nullptr;
          copy->next = new listOfObjects<TrainInfoPerStation *>(currtrains->object);
          copy->next->prev = copy;
          copy = copy->next;
          recursion(currtrains->object, ++currStopOvers, maxTransitTime, maxStopOvers, currStnAdjList->object->adjacentStnIndex, destStnIndex, adjacency, p, copy); // increasing the currStopOvers
        }
        currtrains = currtrains->next; // changing the currtrains to its next destination
      }
      currStnAdjList = currStnAdjList->next; // changing the station to its next destination
    }
    return;
  }
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  int src = stnNameToIndex.get(srcStnName)->value;
  int dest = stnNameToIndex.get(destStnName)->value;
  listOfObjects<StationConnectionInfo *> *currStnAdjList = adjacency[src].toStations; // Adjacency list of current Station
  TrainInfoPerStation *t1 = new TrainInfoPerStation(0, 0, 0, 0);                      // creating new trains
  TrainInfoPerStation *t = new TrainInfoPerStation(0, 0, 0, 0);                       // creating new trains
  listOfObjects<TrainInfoPerStation *> *pointer = new listOfObjects<TrainInfoPerStation *>(t);
  listOfObjects<TrainInfoPerStation *> *till = new listOfObjects<TrainInfoPerStation *>(t1);
  listOfObjects<TrainInfoPerStation *> *output = pointer; // pointer to last object in the list of trains
  int c = 0;
  while (currStnAdjList != nullptr)
  {
    listOfObjects<TrainInfoPerStation *> *alltrains = currStnAdjList->object->trains;
    while (alltrains != nullptr)
    {
      recursion(alltrains->object, 0, maxTransitTime, maxStopOvers, currStnAdjList->object->adjacentStnIndex, dest, adjacency, pointer, till); // passing into recursion with currStopOvers as zero
      alltrains = alltrains->next;                                                                                                             // changing the currtrains to its next destination
    }
    currStnAdjList = currStnAdjList->next; // changing the station to its next adjancent station
  }
  if (output->next == nullptr)
  {
    cout << "No direct journey's available" << endl; // no direct journey's available
  }
  else
  {
    printStationInfo(output->next); // printing all journey's information
  }
  return;
}
#endif
