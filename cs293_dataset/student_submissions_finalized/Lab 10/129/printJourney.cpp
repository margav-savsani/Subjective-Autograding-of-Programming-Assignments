#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  if (maxStopOvers == 0)
  {
    // insert your code here
    // inserting my code
    listOfObjects<TrainInfoPerStation *> *ansstart = nullptr; // head of the final list to be output
    listOfObjects<TrainInfoPerStation *> *ansend = nullptr;   // tail of the final list to be output
    // Queue_BFS *maintain = nullptr;

    int s_index = stnNameToIndex.hashValue(srcStnName);
    while (true)
    {
      if (srcStnName == stnNameToIndex.getKeyAtIndex(s_index))
      { // index of the source station

        break;
      }
      s_index = (s_index + 1) % (DICT_SIZE);
    }

    int dest_index = stnNameToIndex.hashValue(destStnName);
    while (true)
    {
      if (destStnName == stnNameToIndex.getKeyAtIndex(dest_index))
      { // index of the destination station

        break;
      }
      dest_index = (dest_index + 1) % (DICT_SIZE);
    }
    Queue_BFS *head = nullptr;                                                 // head of the queue
    Queue_BFS *tail = nullptr;                                                 // tail of the queue
    listOfObjects<StationConnectionInfo *> *x = adjacency[s_index].toStations; // neighbours of the starting station
    while (x != nullptr)
    {

      int a = x->object->adjacentStnIndex; // index of the node adjacent to source
      listOfObjects<TrainInfoPerStation *> *y = x->object->trains;
      while (y != nullptr)
      {
        if (head == nullptr)
        {
          Queue_BFS *xhead = new Queue_BFS(a, y->object->journeyCode); // adding each train to the queue
          head = xhead;
          // maintain = xhead;
          tail = xhead;

          if (a == dest_index)
          { // checking if adjacent node is the final node
            if (ansstart == nullptr)
            {
              listOfObjects<TrainInfoPerStation *> *garb = new listOfObjects<TrainInfoPerStation *>(y->object);
              ansstart = garb;
              ansend = garb;
              listOfObjects<TrainInfoPerStation *> *s = stationInfo[s_index];
            }
            else
            {
              listOfObjects<TrainInfoPerStation *> *garb = new listOfObjects<TrainInfoPerStation *>(y->object);

              ansend->next = garb;
              ansend = ansend->next;
            }
          }

          // tail = head;
          y = y->next;
        }
        else
        { // just adding to the queue
          // tail = tail->next;
          Queue_BFS *xhead = new Queue_BFS(a, y->object->journeyCode);
          Queue_BFS *t = head;
          // Queue_BFS* c = maintain;

          // while(t->next != nullptr){
          //   t = t->next;
          // }
          // while(c->next != nullptr){

          // }
          // t->next = xhead;

          tail->next = xhead;
          tail = tail->next;
          if (a == dest_index)
          {
            if (ansstart == nullptr)
            {
              listOfObjects<TrainInfoPerStation *> *garb = new listOfObjects<TrainInfoPerStation *>(y->object);
              ansstart = garb;
              ansend = garb;
            }
            else
            {
              listOfObjects<TrainInfoPerStation *> *garb = new listOfObjects<TrainInfoPerStation *>(y->object);
              ansend->next = garb;
              ansend = ansend->next;
            }
          }
          y = y->next;
        }
      }
      x = x->next;
    }

    while (head != nullptr)
    {                                        // empty queue in BFS
      x = adjacency[head->index].toStations; // index of neighbours of head
      while (x != nullptr)
      {
        bool found = false; // denotes if a train with a particular journeycode is found in a neighbour of head

        int a = x->object->adjacentStnIndex;                         // index of a neighbouring station
        listOfObjects<TrainInfoPerStation *> *y = x->object->trains; // trains on that particular edge in graph
        while (y != nullptr)
        {

          if (y->object->journeyCode == head->jcode)
          { // train code matching
            // tail = tail->next;
            if (a == dest_index)
            {
              if (ansstart == nullptr)
              {
                listOfObjects<TrainInfoPerStation *> *garb = new listOfObjects<TrainInfoPerStation *>(y->object);
                ansstart = garb;
                ansend = garb;
              }
              else
              {
                listOfObjects<TrainInfoPerStation *> *garb = new listOfObjects<TrainInfoPerStation *>(y->object);
                ansend->next = garb;
                ansend = ansend->next;
              }
            }
            Queue_BFS *xhead = new Queue_BFS(a, y->object->journeyCode);
            Queue_BFS *t = head;
            // while(t->next!= nullptr){
            //   t = t->next;
            // }
            // t->next = xhead;
            tail->next = xhead;
            tail = tail->next;
            found = true;
            break;
          }
          y = y->next;
        }
        if (found == true)
        { // found a journey-code , it cannot be there in any other neighbour
          break;
        }
        x = x->next;
      }
      head = head->next;
    }
    if (ansstart == nullptr)
    { // no journeys available
      cout << "No direct journeys available" << endl;
    }
    else
    {

      while (ansstart != nullptr)
      { // just printing
        int jcode = ansstart->object->journeyCode;
        listOfObjects<TrainInfoPerStation *> *s = stationInfo[s_index];
        while (s != nullptr)
        {
          if (s->object->journeyCode == jcode)
          {
            listOfObjects<TrainInfoPerStation *> *k = new listOfObjects<TrainInfoPerStation *>(s->object);
            k->next = nullptr;
            k->prev = nullptr;
            printStationInfo(k);
          }
          s = s->next;
        }
        ansstart = ansstart->next;
      }
    }

    // col[s_index] = 2;

    // if(){}

    // else{
    //   cout<<"No direct journeys available"<<endl;
    // }
  }

  // insert your code here

  cout << "This function is to be implemented by you." << endl;

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  return;
}

#endif
