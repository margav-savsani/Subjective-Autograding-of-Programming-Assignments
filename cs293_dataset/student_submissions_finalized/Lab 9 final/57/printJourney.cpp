#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include <queue>
using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  int srcin = stnNameToIndex.get(srcStnName)->value;  // getting index of source station
  int desin = stnNameToIndex.get(destStnName)->value; // getting index of destination station
  int *leaving = new int[100];                        // for storing all trains leaving the source station
  int *reached = new int[100];                        // for storing journey codes of trains which will have direct journeys.
  int lef = 0;                                        // for storing no of trains leaving
  int reach = 0;                                      // for storing no of sucessful journeys

  StationAdjacencyList *fromsrc; // for getting adjcent station
  fromsrc = adjacency;
  // fromsrc->toStations

  listOfObjects<StationConnectionInfo *> *to_stations = fromsrc[srcin].toStations; // list of to_stations
  while (to_stations != nullptr)
  {
    listOfObjects<TrainInfoPerStation *> *train = to_stations->object->trains; // head of the linkedlist
    while (train != nullptr)
    {
      leaving[lef] = train->object->journeyCode;
      lef++;
      train = train->next; // selection next train between two stations
    }
    to_stations = to_stations->next; // selecting nextstation in adjacencylist
  }

  for (int j = 0; j < lef; j++)
  { // checking bfc condion of leaving[j]
    queue<int> quu;
    quu.push(srcin);     // adding source station into que
    while (!quu.empty()) // starting BFS from given source
    {
      int k = quu.front();
      quu.pop();
      if (k == desin) // checking if we reached destination
      {
        reached[reach] = leaving[j]; // adding the train as sucessfull journey
        reach++;
        break;
      }
      StationAdjacencyList *from2src;
      from2src = adjacency; // adjacency list of present vertex
      listOfObjects<StationConnectionInfo *> *tost2 = from2src[k].toStations;
      int t2 = 0;                   // for storing no of adjacent stations
      int *adjsttns = new int[100]; // for storing station index of all adjacent stations.
      while (tost2 != nullptr)
      {
        adjsttns[t2] = tost2->object->adjacentStnIndex;
        t2++;
        tost2 = tost2->next;
      }

      StationAdjacencyList *topres;
      topres = adjacency; //[adjsttns[l]];

      for (int l = 0; l < t2; l++) // checking the following conditions for all adjacent trains
      {
        int lef1 = 0;
        int *reachin1 = new int[100]; // storing codes of all trains reaching the present stations

        listOfObjects<StationConnectionInfo *> *from_stat = topres[adjsttns[l]].fromStations;
        while (from_stat != nullptr)
        {
          listOfObjects<TrainInfoPerStation *> *train = from_stat->object->trains;
          while (train != nullptr)
          {
            reachin1[lef1] = train->object->journeyCode;
            lef1++;
            train = train->next;
          }
          from_stat = from_stat->next;
        }

        bool pres = false; // for checking train (leaving[j]) is reaching the present station
        for (int i = 0; i < lef1; i++)
        {
          if (leaving[j] == reachin1[i])
          {
            pres = true;
          }
        }
        if (pres)
        {
          quu.push(adjsttns[l]); // adding the adjacent station to que only if (train[j] is reaching it)
        }
      }
    }
  }
  // printing the journey codes of train.
  for (int t = 0; t < reach; t++)
  {
    cout << "the following trains are found : " << reached[t] << endl;
    cout << "on different days with arrival time and departure time" << endl;
  }

  //printing all info of trains which will successfully reach the destination station from source station.
  // print the day at which it is available arrival and departure time at the sourcestation.
  listOfObjects<TrainInfoPerStation *> *source_j = NULL;
  listOfObjects<TrainInfoPerStation *> *Total_source = stationInfo[stnNameToIndex.get(srcStnName)->value];
  while (Total_source != NULL)
  {
    for (int i = 0; i < reach; i++)
    {
      if (reached[i] == Total_source->object->journeyCode)
      {
        if (source_j == NULL)
        {
          source_j = new listOfObjects<TrainInfoPerStation *>(Total_source->object);
        }
        else
        {
          listOfObjects<TrainInfoPerStation *> *iterator = source_j;
          while (iterator->next != NULL)
          {
            iterator = iterator->next;
          }
          iterator->next = new listOfObjects<TrainInfoPerStation *>(Total_source->object);
        }
      }
    }
    Total_source = Total_source->next;
  }

  if (source_j == NULL)
  {
    cout << RED << "No direct journeys available" << RESET << endl;
    return;
  }
  printStationInfo(source_j);
  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp

  return;
}
#endif
