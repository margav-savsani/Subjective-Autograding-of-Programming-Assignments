#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

bool TrainInList(listOfObjects<TrainInfoPerStation *> *trains, listOfObjects<TrainInfoPerStation *> *train)
{
  cout << "TrainInList\n";
  listOfObjects<TrainInfoPerStation *> *dummy = trains;
  while (dummy != nullptr)
  {
    if (dummy->object->journeyCode == train->object->journeyCode)
    {
      return true;
    }
    dummy = dummy->next;
  }
  return false;
}

listOfObjects<TrainInfoPerStation *> *getTrain(StationConnectionInfo *justNext, listOfObjects<TrainInfoPerStation *> *train, int dest, StationAdjacencyList *adjacencyList, Dictionary<int> stnNameToIndex)
{
  listOfObjects<TrainInfoPerStation *> *trainT = train;
  listOfObjects<TrainInfoPerStation *> *trains = justNext->trains;
  listOfObjects<TrainInfoPerStation *> *dummy = trains;
  StationAdjacencyList *nextStn = adjacencyList + justNext->adjacentStnIndex;
  if (justNext->adjacentStnIndex == -1)
  {
    return nullptr;
  }
  if (justNext->adjacentStnIndex == dest)
  {
    if (TrainInList(justNext->trains, trainT))
    {
      return trainT;
    }
    else
    {
      return nullptr;
    }
  }
  bool found = TrainInList(justNext->trains, trainT);
  if (found)
  {
    listOfObjects<StationConnectionInfo *> *dommy = nextStn->toStations;
    while (dommy != nullptr)
    {
      listOfObjects<TrainInfoPerStation *> *tain = getTrain(dommy->object, train, dest, adjacencyList, stnNameToIndex);
      if (tain != nullptr)
      {
        return tain;
      }
      dommy = dommy->next;
    }
  }
  return nullptr;
}

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  listOfObjects<TrainInfoPerStation *> *trainsFound = nullptr;
  listOfObjects<TrainInfoPerStation *> *lastTrain = nullptr;
  int src = (stnNameToIndex.get(srcStnName))->value;
  int dest = (stnNameToIndex.get(destStnName))->value;
  cout << "Index of Src: " << src << endl;
  StationAdjacencyList srcStn = adjacency[src];
  listOfObjects<StationConnectionInfo *> *justNext = srcStn.toStations;
  listOfObjects<StationConnectionInfo *> *travel = justNext;
  while (travel != nullptr)
  {
    cout << "Object " << travel->object << endl;
    listOfObjects<TrainInfoPerStation *> *train = travel->object->trains;
    while (train != nullptr)
    {
      listOfObjects<TrainInfoPerStation *> *trainFound = getTrain(travel->object, train, dest, adjacency, stnNameToIndex);
      if (trainFound != nullptr)
      {
        if (trainsFound == nullptr)
        {
          trainsFound = trainFound;
          lastTrain = trainFound;
        }
        else
        {
          lastTrain->next = trainFound;
          trainFound->prev = lastTrain;
          lastTrain = trainFound;
        }
      }
      train = train->next;
    }
    cout << "Object " << travel->object << endl;
    travel = travel->next;
  }
  if (trainsFound == nullptr)
  {
    cout << "No direct journeys available" << endl;
    return;
  }
  printStationInfo(trainsFound);
  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp

  return;
}

#endif
