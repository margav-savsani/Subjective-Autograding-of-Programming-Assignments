#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp
  int index1 = stnNameToIndex.get(srcStnName)->value;   //finding the index of source station   
  int index2 = stnNameToIndex.get(destStnName)->value;    //finding the index of the destination station
  listOfObjects<TrainInfoPerStation *> *stn = stationInfo[index1];    //finding all the train schedules from source station
  listOfObjects<int> *queue1 = nullptr;
  listOfObjects<TrainInfoPerStation *> *parent1 = nullptr;    //list to store the direct connecting trains
  bool *visited = new bool[DICT_SIZE];    //array to check if a node is visited or not
  while(stn != nullptr)   //iterating through all the trains from source station
  {
    queue1 = new listOfObjects<int>(index1);    //inputing the index of source station in queue
    visited = new bool[DICT_SIZE];
    for(int i=0; i<DICT_SIZE; i++)
    {
      visited[i] = false;
    }
    visited[index1] = true;
    listOfObjects<int> *q = queue1;
    while(q != nullptr)   //performing bfs
    {
      int s = q->object;
      listOfObjects<StationConnectionInfo *> *adj = adjacency[s].toStations;   
      while(adj != NULL)    //iterating over all adjacent nodes
      {
        listOfObjects<TrainInfoPerStation *> *train1 = adj->object->trains;
        while(train1 != nullptr)
        {
          if(train1->object->journeyCode == stn->object->journeyCode)   //checking if the station has same journey code to which we are iterating over
          {
            if(adj->object->adjacentStnIndex == index2)   //if destination station is reached
            {
              if(parent1 == nullptr)
              {
                parent1 = new listOfObjects<TrainInfoPerStation *>(stn->object);
              }
              else
              {
                listOfObjects<TrainInfoPerStation *> *p = parent1;
                while(p->next != nullptr)
                {
                  p = p->next;
                }
                p->next = new listOfObjects<TrainInfoPerStation *>(stn->object);
              }
              break;
            }
            if(!visited[adj->object->adjacentStnIndex])   //checking is node is visited
            {
              visited[adj->object->adjacentStnIndex] = true;
              listOfObjects<int> *q2 = queue1;
              while(q2->next != nullptr)
              {
                q2 = q2->next;
              }
              q2->next = new listOfObjects<int>(adj->object->adjacentStnIndex);
            }
            break;
          }
          else if(train1->object->depTime - stn->object->arrTime <= maxTransitTime && train1->object->depTime - stn->object->arrTime >= 0)
            {
              if(maxStopOvers == 0)
              {
                continue;
              }
              else
              {
                
              }
            }
            {
              
            }
          train1 = train1->next;
        }
        adj = adj->next;
      }
      q = q->next;
      adj = nullptr;
    }
    stn = stn->next;
  }
  if(parent1 == nullptr)
  {
    cout<<"No direct journeys available"<<endl;
  }
  else
  {
    printStationInfo(parent1);
  }

  
  return;
}

#endif
