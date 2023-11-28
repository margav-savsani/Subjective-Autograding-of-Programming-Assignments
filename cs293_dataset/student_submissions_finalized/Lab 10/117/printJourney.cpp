#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef PLANNER_H
#include "planner.h"
#endif
// dekhna padega ache se, kya hora hai
int i = 0;

using namespace std;

bool Present(listOfObjects<TrainInfoPerStation *> *list, TrainInfoPerStation *object)
{
  while (list != nullptr)
  {
    if (list->object->journeyCode == object->journeyCode)
      return true;
    list = list->next;
  }
  return false;
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here

  if (srcStnName.compare(destStnName) == 0)
  {
    cout << "Source and Destination Station must be different\n";
    return;
  }
  // insert your code here

  listOfObjects<TrainInfoPerStation *> *listOfTrains = NULL, *endindex = nullptr;       // list of trains to be printed
  int destIndex = stnNameToIndex.get(destStnName)->value;                               // destination index
  listOfObjects<string> *queueOfStation = nullptr, *endPointerQueueOfStation = nullptr; // queue to be used
  queueOfStation = new listOfObjects(srcStnName);
  endPointerQueueOfStation = queueOfStation;                                                                            // first element is the srcStnName
  listOfObjects<listOfObjects<TrainInfoPerStation *> *> *possibleTrains = nullptr, *endpointerPossibleTrains = nullptr; // stored possible trains, directly corresponding to the vector queueofStation

  while (queueOfStation != nullptr)
  {
    string currStation = queueOfStation->object; // store the element in queue in which we are present
    int currStationDictionaryindex = stnNameToIndex.get(currStation)->value;
    if (currStationDictionaryindex == destIndex) // We reach destination in the queue, no BFS here, just store the trains in out list
    {
      listOfObjects<TrainInfoPerStation *> *allowedTrains = possibleTrains->object; // vector of trains reaching destination
      while (allowedTrains != nullptr)                                              // add the elements in out list
      {
        if (listOfTrains == NULL) // if out list is empty
        {
          listOfTrains = new listOfObjects<TrainInfoPerStation *>(allowedTrains->object);
          endindex = listOfTrains;
        }
        else // if it is not
        {
          endindex->next = new listOfObjects<TrainInfoPerStation *>(allowedTrains->object);
          endindex->next->prev = endindex;
          endindex = endindex->next;
        }
        allowedTrains = allowedTrains->next;
      }
      possibleTrains = possibleTrains->next; // dequeue in vector
      queueOfStation = queueOfStation->next; // dequeue the first element
    }
    else // Any other station than destination
    {
      listOfObjects<StationConnectionInfo *> *toAdjacentStations = adjacency[currStationDictionaryindex].toStations; // stores the list of all stations which can be reached from our element
      while (toAdjacentStations != NULL)                                                                             // BFS at the node
      {
        listOfObjects<TrainInfoPerStation *> *trainsCanReachStn = nullptr, *endPointerTrainsCanReachStn = nullptr; // to store possible trains
        int adjacentStationDictionaryIndex = toAdjacentStations->object->adjacentStnIndex;
        if (queueOfStation == nullptr)
        {
          queueOfStation = new listOfObjects(stnNameToIndex.getKeyAtIndex(adjacentStationDictionaryIndex));
          endPointerQueueOfStation = queueOfStation;
        }
        else
        {
          endPointerQueueOfStation->next = new listOfObjects(stnNameToIndex.getKeyAtIndex(adjacentStationDictionaryIndex));
          endPointerQueueOfStation->next->prev = endPointerQueueOfStation;
          endPointerQueueOfStation = endPointerQueueOfStation->next;
        }
        if (currStation.compare(srcStnName) == 0) // currstation is source station
        {
          listOfObjects<TrainInfoPerStation *> *trains = toAdjacentStations->object->trains; // trains of adjacent stations
          while (trains != NULL)
          {

            // adding all to the vector of vector containing allowed trains
            if (trainsCanReachStn == nullptr)
            {
              trainsCanReachStn = new listOfObjects(trains->object);
              endPointerTrainsCanReachStn = trainsCanReachStn;
            }
            else
            {
              endPointerTrainsCanReachStn->next = new listOfObjects(trains->object);
              endPointerTrainsCanReachStn->next->prev = endPointerTrainsCanReachStn;
              endPointerTrainsCanReachStn = endPointerTrainsCanReachStn->next;
            }
            trains = trains->next;
          }
          // possibleTrains.push_back(trainsCanReachStn); // pushing it to the main vector
          if (possibleTrains == nullptr)
          {
            possibleTrains = new listOfObjects(trainsCanReachStn);
            endpointerPossibleTrains = possibleTrains;
          }
          else
          {
            endpointerPossibleTrains->next = new listOfObjects(trainsCanReachStn);
            endpointerPossibleTrains->next->prev = endpointerPossibleTrains;
            endpointerPossibleTrains = endpointerPossibleTrains->next;
          }
        }
        else // currStation is not source, will have a list of edges that are allowed, i.e ones that have come from source, done everything else similarly
        {
          listOfObjects<TrainInfoPerStation *> *allowedTrains = possibleTrains->object;

          listOfObjects<TrainInfoPerStation *> *trains = toAdjacentStations->object->trains;
          while (trains != NULL)
          {
            if (Present(allowedTrains, trains->object)) // only add trains if they are in the allowed ones
            {
              if (trainsCanReachStn == nullptr)
              {
                trainsCanReachStn = new listOfObjects(trains->object);
                endPointerTrainsCanReachStn = trainsCanReachStn;
              }
              else
              {
                endPointerTrainsCanReachStn->next = new listOfObjects(trains->object);
                endPointerTrainsCanReachStn->next->prev = endPointerTrainsCanReachStn;
                endPointerTrainsCanReachStn = endPointerTrainsCanReachStn->next;
              }
            }
            trains = trains->next;
          }
          if (trainsCanReachStn != nullptr)
          {
            if (possibleTrains == nullptr)
            {
              possibleTrains = new listOfObjects(trainsCanReachStn);
              endpointerPossibleTrains = possibleTrains;
            }
            else
            {
              endpointerPossibleTrains->next = new listOfObjects(trainsCanReachStn);
              endpointerPossibleTrains->next->prev = endpointerPossibleTrains;
              endpointerPossibleTrains = endpointerPossibleTrains->next;
            }
          }
          // possibleTrains.push_back(trainsCanReachStn); // if empty, then push it onto the queue and simulataneously remove the pushed vertex with no allowed trains
          else
          {
            endPointerQueueOfStation = endPointerQueueOfStation->prev;
          }
          // queueOfStation.pop_back();
        }

        toAdjacentStations = toAdjacentStations->next;
      }
      queueOfStation = queueOfStation->next;
      if (currStation.compare(srcStnName) != 0)
      {
        possibleTrains = possibleTrains->next;
      }
    }
  }
  cout << "reached\n";
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

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  return;
}

#endif
