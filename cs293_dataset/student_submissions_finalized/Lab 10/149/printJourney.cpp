#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

// @brief data structure for implementing queue
struct queue
{
  /// @brief integer queue to store key values of stations
  int q[DICT_SIZE];

  /// @brief length of the queue
  int length;

  /// @brief default constructor for the queue, initialise the length to 0 and assign value -1 to all elements of the queue
  queue()
  {
    length = 0;
    for (int i = 0; i < DICT_SIZE; i++)
      q[i] = -1;
  }

  /// @brief appending an element to the queue, increments the length by 1
  /// @param a key to be stored in the queue
  void append(int a)
  {
    q[length] = a;
    length++;
  }

  /// @brief pop the first element from the queue, shift the queue 1 step forward
  /// @return the element poped out of the queue
  int pop()
  {
    if (length == 0)
      return -1;
    else
    {
      int a = q[0];
      for (int i = 0; i < length - 1; i++)
        q[i] = q[i + 1];
      length--;
      return a;
    }
  }
};

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  if (maxStopOvers == 0)
  {
    int src = stnNameToIndex.get(srcStnName)->value;   // getting the key of source station
    int dest = stnNameToIndex.get(destStnName)->value; // getting the key of the destination station
    bool visited[DICT_SIZE];                           // array to store whether the given station is visited once or not during traversing the graph
    for (int i = 0; i < DICT_SIZE; i++)
      visited[i] = false;

    int n = 0;

    // following loop counts the number of journeys from the source in the adjacency list of source station
    listOfObjects<StationConnectionInfo *> *currnode = adjacency[src].toStations;
    while (true)
    {
      if (currnode != nullptr)
      {
        listOfObjects<TrainInfoPerStation *> *currtrain = currnode->object->trains;
        while (true)
        {
          if (currtrain != nullptr)
          {
            n++;
            currtrain = currtrain->next;
          }
          else
            break;
        }
        currnode = currnode->next;
      }
      else
        break;
    }

    int jc[n]; // array to store the journey codes from the source station
    int i = 0;
    currnode = adjacency[src].toStations;

    // following loop stores all the journey codes available in the source station
    while (true)
    {
      if (currnode != nullptr)
      {
        listOfObjects<TrainInfoPerStation *> *currtrain = currnode->object->trains;
        while (true)
        {
          if (currtrain != nullptr)
          {
            jc[i] = currtrain->object->journeyCode;
            i++;
            currtrain = currtrain->next;
          }
          else
            break;
        }
        currnode = currnode->next;
      }
      else
        break;
    }

    // queue to store the visited nodes during traversing the graph
    queue k;
    k.append(src);
    bool a = false;
    bool b = false;

    // nested loop to traverse the graph according to BFS but in a modified way
    while (k.length != 0)
    {
      currnode = adjacency[k.pop()].toStations; // pop the queue and search its adajacent nodes for destination
      while (currnode != nullptr && !visited[currnode->object->adjacentStnIndex])
      {
        listOfObjects<TrainInfoPerStation *> *currtrain = currnode->object->trains;
        while (currtrain != nullptr)
        {
          int c = currtrain->object->journeyCode;
          for (int i = 0; i < n; i++) // find if the current journey code is also present in array of journey codes of source
          {
            if (jc[i] == c)
            {
              a = true;
              break;
            }
          }
          if (a) // if found, print the journey if the next station is destination, else mark it as visited and append it to queue if not already present in the queue
          {
            if (currnode->object->adjacentStnIndex == dest)
            {
              listOfObjects<TrainInfoPerStation *> *m;
              listOfObjects<TrainInfoPerStation *> *s = stationInfo[src];
              while (s != nullptr)
              {
                if (s->object->journeyCode == c)
                {
                  m = new listOfObjects<TrainInfoPerStation *>(s->object);
                  m->next = nullptr;
                  m->prev = nullptr;
                  b = true;
                  a = false;
                  break;
                }
                s = s->next;
              }
              printStationInfo(m);
            }
            else
            {
              if (!visited[currnode->object->adjacentStnIndex] && currnode->object->adjacentStnIndex != dest)
              {
                k.append(currnode->object->adjacentStnIndex);
                visited[currnode->object->adjacentStnIndex] = true;
              }
              a = false;
            }
          }
          currtrain = currtrain->next;
        }
        currnode = currnode->next;
      }
    }

    // if nothing is printed
    if (!b)
    {
      cout << "No direct journeys available" << endl;
    }
  }
  return;
}

#endif
