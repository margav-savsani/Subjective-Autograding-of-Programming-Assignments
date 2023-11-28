#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;


bool find(TrainInfoPerStation * train, listOfObjects<TrainInfoPerStation *> *trainList,int maxTransitTime);
TrainInfoPerStation *convert(TrainInfoPerStation * initialEdges, listOfObjects<TrainInfoPerStation *> * initialStnList);
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{


    if (srcStnName.compare(destStnName) == 0)
    {
      cout << "Source and Destination should be different" << endl;
      return;
    }
    listOfObjects<TrainInfoPerStation *> *journeys = nullptr, *lastElem = nullptr; // will put all journeys in this, and storing the current pointer in it
                                                            // vertices denote the station indices -- this is also the queue in which pushing and popping occurs
    int index = stnNameToIndex.get(srcStnName)->value;                             // getting index of source station
    int srcStnIndex = index;
    listOfObjects<int> *vertices = new listOfObjects<int>(index);// pushing the source into the queue
    listOfObjects<int> *head_vertices = vertices;//head of this queue
    listOfObjects<int> *tail_vertices = vertices;
    listOfObjects<listOfObjects<TrainInfoPerStation *>*> *edges = nullptr; // egdes denote the trains which connect the two vertices-- it is a list of list of trains as multiple trains can connect two stations
    listOfObjects<listOfObjects<TrainInfoPerStation *>*> *head_edges = nullptr;
    listOfObjects<listOfObjects<TrainInfoPerStation *>*> *tail_edges = nullptr;
    while (vertices!=nullptr) // while queue is not empty
    {
      if (head_vertices->object == stnNameToIndex.get(destStnName)->value) // when head of the queue becomes the destination
      {
        listOfObjects<TrainInfoPerStation *> *reachingEdges = (head_edges->object); // gives a pointer to the first elememt - so we dereference it
        while(reachingEdges!=nullptr)
        {
          TrainInfoPerStation *finalEdges = convert(reachingEdges->object, stationInfo[srcStnIndex]);
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
          reachingEdges = reachingEdges->next;
        }

        head_vertices = head_vertices->next; // pop out the first element of the queue ie, pop out destination and continue bfs
        if (index != srcStnIndex)
          head_edges = head_edges->next;
        continue;
      }
      index = head_vertices->object;
      listOfObjects<StationConnectionInfo *> *ReachingStations = adjacency[index].toStations;
      listOfObjects<StationConnectionInfo *> *curr = ReachingStations; // cureently holds the first reachingstn
      while (curr != nullptr)
      {
        listOfObjects<TrainInfoPerStation *> *TrainsToCurr = curr->object->trains; // list of trains to each reaching station
        listOfObjects<TrainInfoPerStation *> *temp = TrainsToCurr;
        listOfObjects<TrainInfoPerStation *> *TrainList = nullptr,*tail_TrainList = nullptr;
        while (temp != nullptr) // traversing the entire list of trains
        {

          if (index == srcStnIndex || find(temp->object, head_edges->object,maxTransitTime))
          { // if source station then no checking--push_back every station adjacent to it in the queue,
            // else check whether the train is in the TrainList of the first element of the edge--first element of the edge is the station from which we taking the current train
            if(TrainList == nullptr){
              TrainList = new listOfObjects<TrainInfoPerStation*>(temp->object);
              tail_TrainList = TrainList;
            }
            else{
              TrainList = TrainList->next;
              TrainList->object = temp->object;
              TrainList->prev->next = TrainList;
              tail_TrainList = tail_TrainList->next;
              
            }
          }
          temp = temp->next;
        }
        if (TrainList!=nullptr) // push back elements into queues only if there are trains available
        { 
          if(edges == nullptr){
            edges = new listOfObjects<listOfObjects<TrainInfoPerStation*>*>(TrainList);////////////////////////CHECK THIS LINE
            tail_edges = head_edges = edges;
          }
          else{
            edges = edges->next;
            edges->object = TrainList;
            edges->prev->next = edges;
            tail_edges = tail_edges->next;
          }

          if(vertices == nullptr){
            vertices = new listOfObjects<int>(curr->object->adjacentStnIndex);////////////////////////CHECK THIS LINE
            tail_vertices = head_vertices = vertices;
          }
          else{
            vertices = vertices->next;
            *vertices = curr->object->adjacentStnIndex;
            vertices->prev->next = vertices;
            tail_vertices = tail_vertices->next;
          }
        
        }
        curr = curr->next;
      }
      head_vertices = head_vertices->next; // pop first element out of the queue
      if (index != srcStnIndex)
        head_edges = head_edges->next;
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

  bool find(TrainInfoPerStation * train, listOfObjects<TrainInfoPerStation *> *trainList,int maxTransitTime) // this checks whether train is in trainList
  {
    listOfObjects<TrainInfoPerStation *> *temp = trainList;
    while(temp!=nullptr)
    {
      if (train->journeyCode == trainList->object->journeyCode)
        return true;
    }
    return false;
  }

  TrainInfoPerStation *convert(TrainInfoPerStation * initialEdges, listOfObjects<TrainInfoPerStation *> * initialStnList)
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

#endif
