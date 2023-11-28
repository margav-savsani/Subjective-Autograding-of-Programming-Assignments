#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"

#endif

#endif

class Node // Single vertex of the graph
{
public:
  int Index;
  listOfObjects<TrainInfoPerStation *> *trains;
  listOfObjects<TrainInfoPerStation *> *trains2;

  Node(int index)
  {
    Index = index;
    trains = NULL;
    trains2 = NULL;
  }
};

listOfObjects<TrainInfoPerStation *> *train_present(listOfObjects<TrainInfoPerStation *> *train, listOfObjects<TrainInfoPerStation *> *trains_list)
{
  while (trains_list != NULL) // traversing trains_list (linked list)
  {
    if (trains_list->object->journeyCode == train->object->journeyCode)
    {
      return trains_list;
    }
    trains_list = trains_list->next;
  }
  return NULL;
}
listOfObjects<TrainInfoPerStation *> *AlternateBFS(listOfObjects<Node *> *q, listOfObjects<Node *> *last, int stn1, int stn2, listOfObjects<TrainInfoPerStation *> *Available, listOfObjects<TrainInfoPerStation *> *intermediate, StationAdjacencyList *adjacency)
{
  if (q != NULL) // Continues iff q is not empty
  {
    listOfObjects<StationConnectionInfo *> *curr = adjacency[q->object->Index].toStations;
    while (curr != NULL) // cheching the adjacent vertices
    {
      if (curr->object->adjacentStnIndex != stn1)
      {

        if (curr->object->adjacentStnIndex != stn2)
        {
          Node *new_node = new Node(curr->object->adjacentStnIndex);
          listOfObjects<Node *> *node = new listOfObjects<Node *>(new_node);
          listOfObjects<TrainInfoPerStation *> *trains = curr->object->trains;
          while (trains != NULL)
          {
            if (node->object->trains != NULL)
            {
              listOfObjects<TrainInfoPerStation *> *train = train_present(trains, q->object->trains);
              if(train==NULL);
              else 
              {
                node->object->trains2->next = new listOfObjects<TrainInfoPerStation *>(train->object);
                node->object->trains2 = node->object->trains2->next;
              }
            }
            else
            {
              listOfObjects<TrainInfoPerStation *> *train = train_present(trains, q->object->trains);
              if(train==NULL);
              else 
              {
                node->object->trains = new listOfObjects<TrainInfoPerStation *>(train->object);
                node->object->trains2 = node->object->trains;
              }
            }
            trains = trains->next;
          }
          if (node->object->trains != NULL)
          {
            last->next = node;
            last = node;
          }
        }
        else 
        {
          listOfObjects<TrainInfoPerStation *> *trains = curr->object->trains;
          while (trains != NULL)
          {
            if (Available == NULL)
            {
              listOfObjects<TrainInfoPerStation *> *train = train_present(trains, q->object->trains);
              if(train==NULL);
              else 
              {
                Available = new listOfObjects<TrainInfoPerStation *>(train->object);
                intermediate = Available;
              }
            }
            if (Available != NULL)
            {
              listOfObjects<TrainInfoPerStation *> *train = train_present(trains, q->object->trains);
              if(train==NULL);
              else 
              {
                Available = new listOfObjects<TrainInfoPerStation *>(train->object);
                intermediate = Available;
              }
            }
            else
            {

              listOfObjects<TrainInfoPerStation *> *train = train_present(trains, q->object->trains);
              if(train==NULL);
              else 
              {
                intermediate->next = new listOfObjects<TrainInfoPerStation *>(train->object);
                intermediate = intermediate->next;
              }
            }
            trains = trains->next;
          }
        }
      }
      curr = curr->next;
    }
    q = q->next;
    Available = AlternateBFS(q, last, stn1, stn2, Available, intermediate, adjacency);
  }
  return Available; // returns the trains which are available
}

void Planner::printDirectJourneys(string srcStnName, string destStnName) // function to be implemented
{

  bool answer = 0;
  int stn1 = stnNameToIndex.get(srcStnName)->value;
  int stn2 = stnNameToIndex.get(destStnName)->value;
  listOfObjects<StationConnectionInfo *> *curr = adjacency[stn1].toStations;
  listOfObjects<TrainInfoPerStation *> *source_trains = stationInfo[stn1];
  listOfObjects<TrainInfoPerStation *> *final_trains = stationInfo[stn2];
  // int count = 0;

  Node *source = new Node(stn1);
  listOfObjects<Node *> *q = new listOfObjects<Node *>(source);
  listOfObjects<TrainInfoPerStation *> *intermediate = NULL;
  listOfObjects<TrainInfoPerStation *> *Available = NULL;

  while (curr != NULL)
  {
    listOfObjects<TrainInfoPerStation *> *trains = curr->object->trains;
    while (trains != NULL)
    {
      listOfObjects<TrainInfoPerStation *> *train = train_present(trains, source_trains);
      if (q->object->trains == NULL)
      {
        q->object->trains = new listOfObjects<TrainInfoPerStation *>(train->object);
        q->object->trains2 = q->object->trains;
      }
      else
      {
        q->object->trains2->next = new listOfObjects<TrainInfoPerStation *>(train->object);
        q->object->trains2 = q->object->trains2->next;
      }
      trains = trains->next;
    }
    curr = curr->next;
  }

  listOfObjects<Node *> *last;
  last = q;
  Available = AlternateBFS(q, last, stn1, stn2, Available, intermediate, adjacency);
  if (Available == NULL)
    cout << "No direct journey is available" << endl;

  else
    printStationInfo(Available); // if atleast one journey is train_present

  return;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
}