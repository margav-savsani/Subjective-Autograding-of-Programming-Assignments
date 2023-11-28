#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#include <bits/stdc++.h>
#endif

using namespace std;
bool find(TrainInfoPerStation *train, vector<TrainInfoPerStation *> trainList);
TrainInfoPerStation *convert(TrainInfoPerStation *initialEdges, listOfObjects<TrainInfoPerStation *> *initialStnList);
void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  if (srcStnName.compare(destStnName) == 0)
  {
    cout << "Source and Destination should be different" << endl;
    return;
  }
  listOfObjects<TrainInfoPerStation *> *journeys = nullptr, *lastElem = nullptr; // will put all journeys in this, and storing the current pointer in it
  vector<int> vertices;                                                          // vertices denote the station indices -- this is also the queue in which pushing and popping occurs
  int index = stnNameToIndex.get(srcStnName)->value;                             // getting index of source station
  int srcStnIndex = index;
  vertices.push_back(index); // pushing the source into the queue

  vector<vector<TrainInfoPerStation *>> edges; // egdes denote the trains which connect the two vertices-- it is a list of list of trains as multiple trains can connect two stations

  while (vertices.size() != 0) // while queue is not empty
  {
    if (vertices[0] == stnNameToIndex.get(destStnName)->value) // when head of the queue becomes the destination
    {
      vector<TrainInfoPerStation *> reachingEdges = *edges.begin(); //.begin gives a pointer to the first elememt - so we dereference it
      for (int i = 0; i < reachingEdges.size(); i++)
      {
        TrainInfoPerStation *finalEdges = convert(reachingEdges[i], stationInfo[srcStnIndex]);
        if (journeys == nullptr) // first input
        {

          journeys = new listOfObjects<TrainInfoPerStation *>(finalEdges);
          lastElem = journeys;
        }
        else // next inputs
        {
          lastElem->next = new listOfObjects<TrainInfoPerStation *>(finalEdges);
          lastElem->next->prev = lastElem;
          lastElem = lastElem->next;
        }
      }

      vertices.erase(vertices.begin()); // pop out the first element of the queue ie, pop out destination and continue bfs
      if (index != srcStnIndex)
        edges.erase(edges.begin());
      continue;
    }
    index = vertices[0];
    listOfObjects<StationConnectionInfo *> *ReachingStations = adjacency[index].toStations;
    listOfObjects<StationConnectionInfo *> *curr = ReachingStations; // cureently holds the first reachingstn
    while (curr != nullptr)
    {
      listOfObjects<TrainInfoPerStation *> *TrainsToCurr = curr->object->trains; // list of trains to each reaching station
      listOfObjects<TrainInfoPerStation *> *temp = TrainsToCurr;
      vector<TrainInfoPerStation *> TrainList;
      while (temp != nullptr) // traversing the entire list of trains
      {

        if (index == srcStnIndex || find(temp->object, edges[0]))
        { // if source station then no checking--push_back every station adjacent to it in the queue,
          // else check whether the train is in the TrainList of the first element of the edge--first element of the edge is the station from which we taking the current train

          TrainList.push_back(temp->object);
        }
        temp = temp->next;
      }
      if (TrainList.size() > 0) // push back elements into queues only if there are trains available
      {
        edges.push_back(TrainList);
        vertices.push_back(curr->object->adjacentStnIndex);
      }
      curr = curr->next;
    }
    vertices.erase(vertices.begin()); // pop first element out of the queue
    if (index != srcStnIndex)
      edges.erase(edges.begin());
  }
  if (journeys != nullptr)
  {
    printStationInfo(journeys);
  }
  else
  {
    cout << "No direct journeys available" << endl;
  }
}

bool find(TrainInfoPerStation *train, vector<TrainInfoPerStation *> trainList) // this checks whether train is in trainList
{
  for (int i = 0; i < trainList.size(); i++)
  {
    if (train->journeyCode == trainList[i]->journeyCode)
      return true;
  }
  return false;
}

TrainInfoPerStation *convert(TrainInfoPerStation *initialEdges, listOfObjects<TrainInfoPerStation *> *initialStnList)
{ // I initially had trainlist whose arrival and departure
  // were wrt the destination, now it has the arrival and departure times of the source station as was required.
  listOfObjects<TrainInfoPerStation *> *stations = initialStnList;
  while (stations != nullptr)
  {
    if (initialEdges->journeyCode == stations->object->journeyCode)
    {
      return stations->object;
    }
    stations = stations->next;
  }
}

// Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
// for the source station and then we can print it out by invoking
// printStationInfo that we had used in Lab 7.
// printStationInfo is a private member function of the Planner class
// It is declared in planner.h and implemented in planner.cpp

#endif
