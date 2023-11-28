#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
//#include <queue>
using namespace std;

class linkedlist
{
public:
  int index;
  int code;
  linkedlist *next;
  linkedlist *prev;
  // linkedlist *tail;
  //  Constructor
  linkedlist(int indValue, int codeValue)
  {
    index = indValue;
    code = codeValue;
    next = prev = nullptr;
    // tail = this;
  }

  // Destructor
  ~linkedlist() { ; }
};

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  // insert your code here

  int count = 0; // count is to count no of direct journeys fron source to destination station.
  listOfObjects<TrainInfoPerStation *> *listing;
  Entry<int> *source = stnNameToIndex.get(srcStnName);
  int source_index = source->value; // storing index of the source station
  Entry<int> *dest = stnNameToIndex.get(destStnName);
  int dest_index = dest->value; // storing index of the destination station

  linkedlist *queue = new linkedlist(source_index, -1);
  while (queue != nullptr) // loop runs until the queue becomes empty
  {
    int ind = queue->index;
    int jnrycode = queue->code;

    if (jnrycode == -1) // when the adjacent stations of source are added
    {
      listOfObjects<StationConnectionInfo *> *to = adjacency[ind].toStations;

      while (to != nullptr) // loop for going through all the to stations
      {
        int adj = to->object->adjacentStnIndex; // index of adjacent station
        listOfObjects<TrainInfoPerStation *> *each = to->object->trains;

        while (each != nullptr) // loop for going through each train between adjacent stations
        {
          if (adj == dest_index)
          {
            if (count == 0)
              listing = new listOfObjects<TrainInfoPerStation *>(each->object);
            else
            {
              listOfObjects<TrainInfoPerStation *> *last1 = listing;
              while (last1->next != nullptr)
                last1 = last1->next;
              listOfObjects<TrainInfoPerStation *> *add = new listOfObjects<TrainInfoPerStation *>(each->object);
              last1->next = add;
            }
            count++;
          }
          else
          {
            linkedlist *adjstn = new linkedlist(adj, each->object->journeyCode);
            linkedlist *last = queue;
            while (last->next != nullptr)
              last = last->next;
            last->next = adjstn;
          }
          each = each->next;
        }
        to = to->next;
      }
      if (queue->next == nullptr) // checking if queue has only one element
      {
        queue = nullptr;
      }
      else // queue having more than one element
      {
        queue = queue->next;
        queue->prev = nullptr;
      }
    }

    else // remaining cases
    {
      listOfObjects<StationConnectionInfo *> *to = adjacency[ind].toStations;
      while (to != nullptr) // loop for going through all the to stations
      {
        int adj = to->object->adjacentStnIndex;
        listOfObjects<TrainInfoPerStation *> *each = to->object->trains;
        while (each != nullptr) // loop for going through each train between adjacent stations
        {
          if (adj == dest_index && each->object->journeyCode == jnrycode)
          {
            if (count == 0)
              listing = new listOfObjects<TrainInfoPerStation *>(each->object);
            else
            {
              listOfObjects<TrainInfoPerStation *> *last1 = listing;
              while (last1->next != nullptr)
                last1 = last1->next;
              listOfObjects<TrainInfoPerStation *> *add = new listOfObjects<TrainInfoPerStation *>(each->object);
              last1->next = add;
            }
            count++;
          }
          else if (each->object->journeyCode == jnrycode)
          {
            linkedlist *adjstn = new linkedlist(adj, each->object->journeyCode);
            linkedlist *last = queue;
            while (last->next != nullptr)
              last = last->next;
            last->next = adjstn;
          }
          each = each->next;
        }
        to = to->next;
      }

      if (queue->next == nullptr) // checking if queue has only one element
      {
        queue = nullptr;
      }
      else // queue having more than one element
      {
        queue = queue->next;
        queue->prev = nullptr;
      }
    }
  }

  if (count == 0)
  {
    cout << "No direct journeys available" << endl;
    return;
  }

  printStationInfo(listing);
  return;
}

// Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
// for the source station and then we can print it out by invoking
// printStationInfo that we had used in Lab 7.
// printStationInfo is a private member function of the Planner class
// It is declared in planner.h and implemented in planner.cpp
