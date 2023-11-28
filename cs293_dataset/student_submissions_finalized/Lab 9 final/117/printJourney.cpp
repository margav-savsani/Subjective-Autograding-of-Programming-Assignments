#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <bits/stdc++.h>

using namespace std;

// find(allowedTrains.begin(), allowedTrains.end(), trains->object) == allowedTrains.end()
bool Present(vector<TrainInfoPerStation *> allowedTrains, TrainInfoPerStation *object)
{
  for (int i = 0; i < allowedTrains.size(); i++)
  {
    if (allowedTrains[i]->journeyCode == object->journeyCode)
      return true;
  }
  return false;
}

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  if (srcStnName.compare(destStnName) == 0)
  {
    cout << "Source and Destination Station must be different\n";
    return;
  }
  // insert your code here

  listOfObjects<TrainInfoPerStation *> *listOfTrains = NULL, *endindex = nullptr; // list of trains to be printed
  int destIndex = stnNameToIndex.get(destStnName)->value;                         // destination index
  vector<string> queueOfStation;                                                  // queue to be used
  queueOfStation.push_back(srcStnName);                                           // first element is the srcStnName
  vector<vector<TrainInfoPerStation *>> possibleTrains;                           // stored possible trains, directly corresponding to the vector queueofStation

  while (!queueOfStation.empty())
  {
    string currStation = *queueOfStation.begin();                            // store the element in queue in which we are present
    int currStationDictionaryindex = stnNameToIndex.get(currStation)->value; // index of that element
    if (currStationDictionaryindex == destIndex)                             // We reach destination in the queue, no BFS here, just store the trains in out list
    {
      vector<TrainInfoPerStation *> allowedTrains = *possibleTrains.begin(); // vector of trains reaching destination
      while (!allowedTrains.empty())                                         // add the elements in out list
      {
        if (listOfTrains == NULL) // if out list is empty
        {
          listOfTrains = new listOfObjects<TrainInfoPerStation *>(*allowedTrains.begin());
          endindex = listOfTrains;
        }
        else // if it is not
        {
          endindex->next = new listOfObjects<TrainInfoPerStation *>(*allowedTrains.begin());
          endindex->next->prev = endindex;
          endindex = endindex->next;
        }
        allowedTrains.erase(allowedTrains.begin());
      }
      possibleTrains.erase(possibleTrains.begin()); // dequeue in vector
      queueOfStation.erase(queueOfStation.begin()); // dequeue the first element
    }
    else // Any other station than destination
    {
      listOfObjects<StationConnectionInfo *> *toAdjacentStations = adjacency[currStationDictionaryindex].toStations; // stores the list of all stations which can be reached from our element
      while (toAdjacentStations != NULL)                                                                             // BFS at the node
      {
        vector<TrainInfoPerStation *> trainsCanReachStn; // to store possible trains
        int adjacentStationDictionaryIndex = toAdjacentStations->object->adjacentStnIndex;
        queueOfStation.push_back(stnNameToIndex.getKeyAtIndex(adjacentStationDictionaryIndex)); // enqueue
        if (currStation.compare(srcStnName) == 0)                                               // currstation is source station
        {
          listOfObjects<TrainInfoPerStation *> *trains = toAdjacentStations->object->trains; // trains of adjacent stations
          while (trains != NULL)
          {
            trainsCanReachStn.push_back(trains->object); // adding all to the vector of vector containing allowed trains
            trains = trains->next;
          }
          possibleTrains.push_back(trainsCanReachStn); // pushing it to the main vector
        }
        else // currStation is not source, will have a list of edges that are allowed, i.e ones that have come from source, done everything else similarly
        {
          vector<TrainInfoPerStation *> allowedTrains = *possibleTrains.begin();

          listOfObjects<TrainInfoPerStation *> *trains = toAdjacentStations->object->trains;
          while (trains != NULL)
          {
            if (Present(allowedTrains, trains->object)) // only add trains if they are in the allowed ones
            {
              trainsCanReachStn.push_back(trains->object);
            }
            trains = trains->next;
          }
          if (trainsCanReachStn.size() != 0)
            possibleTrains.push_back(trainsCanReachStn); // if empty, then push it onto the queue and simulataneously remove the pushed vertex with no allowed trains
          else
            queueOfStation.pop_back();
        }

        toAdjacentStations = toAdjacentStations->next;
      }
      queueOfStation.erase(queueOfStation.begin()); // dequeue the first element
      if (currStation.compare(srcStnName) != 0)
      {
        possibleTrains.erase(possibleTrains.begin());
      }
    }
  }

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp

  if (listOfTrains == NULL)
    cout << "No direct journeys available\n";
  else
  {
    listOfObjects<TrainInfoPerStation *> *iterate = listOfTrains;
    while (iterate != nullptr)
    {
      listOfObjects<TrainInfoPerStation *> *sourceTrains = stationInfo[stnNameToIndex.get(srcStnName)->value];
      while (sourceTrains != nullptr)
      {
        if (sourceTrains->object->journeyCode == iterate->object->journeyCode)
        {
          iterate->object = sourceTrains->object;

          break;
        }
        sourceTrains = sourceTrains->next;
      }
      iterate = iterate->next;
    }
    printStationInfo(listOfTrains);
  }
  return;
}

#endif
