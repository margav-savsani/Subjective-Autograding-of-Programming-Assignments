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

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp
  // The Index of destination station
  int destination_ind = stnNameToIndex.get(destStnName)->value;

  // The Direct journeys are stored in form of Queue of their Train-No.
  // DynamicQueue<int> Train_nos;

  // // insert your code here
  // DynamicQueue<QueueElem> queue_BFS;

  // Index of the station_Name
  int index = stnNameToIndex.get(srcStnName)->value;

  // The adjacency of the current station.
  StationAdjacencyList *curr = adjacency;

  // An iterator for the to.Stations to store all the adjacent stations
  listOfObjects<StationConnectionInfo *> *adjstns = curr[index].toStations;

  while (adjstns != NULL) // Storing all the adjacent station Names
  {
    // The index of the station which we have reached
    int ind_of_station = adjstns->object->adjacentStnIndex;

    // An iterator for trains to this station
    listOfObjects<TrainInfoPerStation *> *train = adjstns->object->trains;

    while (train != NULL)
    {
      // If there is direct train at start from source to stop.
      if (ind_of_station == destination_ind)
      {
        // Adding the TrainNo to the Queue of Train_nos.
        Train_nos.QInsert(train->object->journeyCode);
        train = train->next;
        continue; // Since we donot add these trains to the Queue
      }
      queue_BFS.QInsert(QueueElem(ind_of_station, train->object->journeyCode));
      train = train->next;
    }
    adjstns = adjstns->next;
  }

  while (!queue_BFS.isEmpty())
  {                                    // The Main BFS loop
    QueueElem *head = new QueueElem(); // Head of the Queue
    queue_BFS.QDelete(head);           // This stores the Head in the 'head' pointer
    int trainno = head->trainno;       // Gives the Train No of the Head
    int stn_ind = head->stn_ind;       // Gives Station index of the HEAD.
    adjstns = adjacency[stn_ind].toStations;
    while (adjstns != NULL)
    {
      listOfObjects<TrainInfoPerStation *> *train = adjstns->object->trains;
      int adjStn = adjstns->object->adjacentStnIndex;
      while (train != NULL)
      {
        if (train->object->journeyCode == trainno)
        {
          // Check Whether the Removed trainno is same as that removed from Queue.
          if (adjStn == destination_ind)
          {
            // When we reach the destination required.
            //  Adding the TrainNo in the Queue Train_nos
            Train_nos.QInsert(train->object->journeyCode);
            break; // No further train exists hence exit While Loop
          }
          // Adding the element into the Queue
          queue_BFS.QInsert(QueueElem(adjStn, trainno));
        }
        train = train->next;
      }
      adjstns = adjstns->next;
    }
  }
  // Finally Train_nos contain all the Train numbers.
  // We Check the Source Station for the corresponding TrainNo.

  // Finally the list to be returned.
  listOfObjects<TrainInfoPerStation *> *source_j = NULL;

  // Total Train Info for the source station.
  listOfObjects<TrainInfoPerStation *> *Total_source = stationInfo[stnNameToIndex.get(srcStnName)->value];

  while (Total_source != NULL)
  {
    if (Train_nos.find_elem(Total_source->object->journeyCode))
    {
      if (source_j == NULL)
      {
        source_j = new listOfObjects<TrainInfoPerStation *>(Total_source->object);
      }
      else
      { // Adding the element to the list at the start
        listOfObjects<TrainInfoPerStation *> *iterator = source_j;
        iterator->prev = new listOfObjects<TrainInfoPerStation *>(Total_source->object);
        iterator->prev->next = iterator;
        source_j = iterator->prev;
      }
    }
    Total_source = Total_source->next;
  }

  if (source_j == NULL)
  {
    std::cout << "No direct journeys available" << endl;
    return;
  }

  printStationInfo(source_j);
  // This would return all the journeys from the source station.

  return;
}

#endif
