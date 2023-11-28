#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"

#endif

#endif

class Station // Single vertex of the graph
{
public:
  int index;
  listOfObjects<TrainInfoPerStation *> *t1;
  listOfObjects<TrainInfoPerStation *> *t2;

  Station(int index)
  {
    index = index;
    t1 = NULL;
    t2 = NULL;
  }
};

listOfObjects<TrainInfoPerStation *> *add(listOfObjects<TrainInfoPerStation *> *train, listOfObjects<TrainInfoPerStation *> *trainsll)
{
  while (trainsll != NULL) // traversing the linked list
  {
    if (trainsll->object->journeyCode == train->object->journeyCode)
    {
      return trainsll;
    }
    trainsll = trainsll->next;
  }
  return NULL;
}
listOfObjects<TrainInfoPerStation *> *AlternateBFS(listOfObjects<Station *> *q, listOfObjects<Station *> *last, int stn1, int stn2, listOfObjects<TrainInfoPerStation *> *Available, listOfObjects<TrainInfoPerStation *> *intermediate, StationAdjacencyList *adjacency)
{
  if (q != NULL) // Continues iff q is not empty
  {
    listOfObjects<StationConnectionInfo *> *curr = adjacency[q->object->index].toStations;
    while (curr != NULL) // cheching the adjacent vertices
    {
      if (curr->object->adjacentStnIndex != stn2)
      {

        if (curr->object->adjacentStnIndex != stn1)
        {
          Station *new_node = new Station(curr->object->adjacentStnIndex);
          listOfObjects<Station *> *node = new listOfObjects<Station *>(new_node);
          listOfObjects<TrainInfoPerStation *> *trains = curr->object->trains;
          while (trains != NULL)
          {
            if (node->object->t1 != NULL)
            {
              listOfObjects<TrainInfoPerStation *> *train = add(trains, q->object->t1);
              if(train==NULL);
              else 
              {
                node->object->t2->next = new listOfObjects<TrainInfoPerStation *>(train->object);
                node->object->t2 = node->object->t2->next;
              }
            }
            else
            {
              listOfObjects<TrainInfoPerStation *> *train = add(trains, q->object->t1);
              if(train==NULL);
              else 
              {
                node->object->t1 = new listOfObjects<TrainInfoPerStation *>(train->object);
                node->object->t2 = node->object->t1;
              }
            }
            trains = trains->next;
          }
          if (node->object->t1 != NULL)
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
              listOfObjects<TrainInfoPerStation *> *train = add(trains, q->object->t1);
              if(train==NULL);
              else 
              {
                Available = new listOfObjects<TrainInfoPerStation *>(train->object);
                intermediate = Available;
              }
            }
            if (Available != NULL)
            {
              listOfObjects<TrainInfoPerStation *> *train = add(trains, q->object->t1);
              if(train==NULL);
              else 
              {
                Available = new listOfObjects<TrainInfoPerStation *>(train->object);
                intermediate = Available;
              }
            }
            else
            {

              listOfObjects<TrainInfoPerStation *> *train = add(trains, q->object->t1);
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

  Station *source = new Station(stn1);
  listOfObjects<Station *> *q = new listOfObjects<Station *>(source);
  listOfObjects<TrainInfoPerStation *> *intermediate = NULL;
  listOfObjects<TrainInfoPerStation *> *Available = NULL;

  while (curr != NULL)
  {
    listOfObjects<TrainInfoPerStation *> *trains = curr->object->trains;
    while (trains != NULL)
    {
      listOfObjects<TrainInfoPerStation *> *train = add(trains, source_trains);
      if (q->object->t1 == NULL)
      {
        q->object->t1 = new listOfObjects<TrainInfoPerStation *>(train->object);
        q->object->t2 = q->object->t1;
      }
      else
      {
        q->object->t2->next = new listOfObjects<TrainInfoPerStation *>(train->object);
        q->object->t2 = q->object->t2->next;
      }
      trains = trains->next;
    }
    curr = curr->next;
  }

  listOfObjects<Station *> *last;
  last = q;
  Available = AlternateBFS(q, last, stn1, stn2, Available, intermediate, adjacency);
  if (Available == NULL)
    cout << "No direct journey is available" << endl;

  else
    printStationInfo(Available); // if atleast one journey is presentadd

  return;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
}
