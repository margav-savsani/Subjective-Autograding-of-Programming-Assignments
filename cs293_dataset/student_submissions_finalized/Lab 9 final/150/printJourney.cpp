#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
using namespace std;

// STRUCT helpful as a BFS queue object have two attributes
// station name and jrny code
struct myclass
{
  int stn;
  TrainInfoPerStation jrny;
};

// give the destination station no on which following jrny code will land in the myqueue
// -1 if the jrny is not present in the myqueue linked list
int next_station(listOfObjects<StationConnectionInfo *> *myqueue, int journey_code)
{
  bool ans = false;
  while (myqueue != nullptr)
  {
    listOfObjects<TrainInfoPerStation *> *trains = myqueue->object->trains;
    while (trains != nullptr)
    {
      if (trains->object->journeyCode == journey_code)
        return myqueue->object->adjacentStnIndex;
      trains = trains->next;
    }
    myqueue = myqueue->next;
  }
  return -1;
}

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  // find the start and end index from the dictionary by their names.
  int start_index = stnNameToIndex.get(srcStnName)->value;
  int end_index = stnNameToIndex.get(destStnName)->value;
  // insert your code here
  // Took the to list from source station
  listOfObjects<StationConnectionInfo *> *myqueue = adjacency[start_index].toStations;
  // the linked list myqueue2 acting as queue for BFS
  // modified BFS will have multiple visits to node
  listOfObjects<myclass *> *myqueue2 = nullptr;
  // storing the tail
  listOfObjects<myclass *> *myqueue2_last = nullptr;
  // adding all trains from source to the queue as a struct of pair of destination station
  // and traininfoperstation
  while (myqueue != nullptr)
  {
    listOfObjects<TrainInfoPerStation *> *trains = myqueue->object->trains;
    while (trains != nullptr)
    {
      myclass *a = new myclass({myqueue->object->adjacentStnIndex, *trains->object});
      if (myqueue2 == nullptr)
      {
        myqueue2 = new listOfObjects<myclass *>(a);
        myqueue2_last = myqueue2;
      }
      else
      {
        myqueue2_last->next = new listOfObjects<myclass *>(a);
        myqueue2_last = myqueue2_last->next;
      }
      trains = trains->next;
    }
    myqueue = myqueue->next;
  }
  // queue of the valid trains i.e, that will go from start to end index
  listOfObjects<TrainInfoPerStation *> *myqueue3 = nullptr;
  listOfObjects<TrainInfoPerStation *> *myqueue3_last = nullptr;

  // checking till all list in queue are empty
  while (myqueue2 != nullptr)
  { // check if station index is equal to end if it is equal then we are done and add it to myqueue3
    // otherwise check if the train goes further from our present staion to next station and if yes
    // add it to the back of queue and remove object from queue else if there is no further jrny with
    // this jrny code then simply remove this from queue since no further jrny is possible. 
    if (myqueue2->object->stn != end_index)
    {
      int a = next_station(adjacency[myqueue2->object->stn].toStations, myqueue2->object->jrny.journeyCode);
      if (a != -1)
      {
        myclass *b = new myclass({a, myqueue2->object->jrny});
        myqueue2_last->next = new listOfObjects<myclass *>(b);
        myqueue2_last = myqueue2_last->next;
      }
      myqueue2 = myqueue2->next;
    }
    else
    {   // finding the Traininfoperstation at the source station by matching it with the jrny code  
        // in the list of Traininfoperstation of source and adding it to myqueue3 
        listOfObjects<TrainInfoPerStation *> *a = stationInfo[start_index];
        while (a != nullptr)
        {
          if (a->object->journeyCode == myqueue2->object->jrny.journeyCode)
          {
            if (myqueue3 == nullptr)
            {
              myqueue3 = new listOfObjects<TrainInfoPerStation *>(a->object);
              myqueue3_last = myqueue3;
              break;
            }
            else
            {
              myqueue3_last->next = new listOfObjects<TrainInfoPerStation *>(a->object);
              myqueue3_last = myqueue3_last->next;
              break;
            }
          }
          a = a->next;
        }
       myqueue2=myqueue2->next;
    }
    }
    // printing the list.
    printStationInfo(myqueue3);
   
   // if no jrny found print this
    if (myqueue3 == nullptr)
    cout << "No direct journeys available" << endl;

    return;
  }
