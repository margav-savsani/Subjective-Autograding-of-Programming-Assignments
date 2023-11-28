#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

class Networkobj
{
public:
  int stopovers;
  listOfObjects<int *> *station_indexes;
  listOfObjects<int *> *station_indexes2;
  listOfObjects<TrainInfoPerStation *> *trains;
  listOfObjects<TrainInfoPerStation *> *trains2;

  Networkobj()
  {
    stopovers = 0;
    trains = NULL;
    trains2 = NULL;
    station_indexes = NULL;
    station_indexes2 = NULL;
  }
};
class Node
{
public:
  int Index;
  listOfObjects<Networkobj *> *journies;
  listOfObjects<Networkobj *> *journies2;

  Node(int index)
  {
    Index = index;
    journies = NULL;
    journies2 = NULL;
  }
};

listOfObjects<TrainInfoPerStation *> *presentadd(listOfObjects<TrainInfoPerStation *> *train, listOfObjects<TrainInfoPerStation *> *trains)
{
  while (trains != nullptr)
  {
    if (trains->object->journeyCode == train->object->journeyCode)
    {
      listOfObjects<TrainInfoPerStation *> *train_2 = new listOfObjects<TrainInfoPerStation *>(trains->object);
      return train_2;
    }
    trains = trains->next;
  }
  return nullptr;
}


listOfObjects<Networkobj *> *AlternateBFS(int t_time, int stopovers, listOfObjects<TrainInfoPerStation *> **stationInfo, listOfObjects<Node *> *q, listOfObjects<Node *> *tail, listOfObjects<Networkobj *> *journeys_available, listOfObjects<Networkobj *> *journeys_available2,int stn1, int stn2, StationAdjacencyList *adjacency)
{
  if (q != nullptr) // Continues if q is not empty
  {
    int index = q->object->Index;
    listOfObjects<Networkobj *> *curr = q->object->journies;
    while (curr != nullptr)
    {
      curr = curr->next;
    }
    listOfObjects<StationConnectionInfo *> *currinf = adjacency[index].toStations;
    while (currinf != nullptr)
    {
      if (currinf->object->adjacentStnIndex == stn2) // If destination found add to trains_available list
      {
        if (q->object->Index == stn1 && q->object->journies->object->trains->next == NULL)
        {
          listOfObjects<Networkobj *> *curr = q->object->journies;
          while (curr != nullptr)
          {
            listOfObjects<Networkobj *> *new_obj = new listOfObjects<Networkobj *>(curr->object);
            listOfObjects<TrainInfoPerStation *> *trains = currinf->object->trains;
            while (trains != nullptr)
            {
              if (trains->object->journeyCode == new_obj->object->trains2->object->journeyCode)
              {
                if (new_obj->object->stopovers <= stopovers)
                {
                  if (journeys_available != nullptr)
                  {
                    journeys_available2->next = new_obj;
                    journeys_available2 = journeys_available2->next;
                  }
                  else if (journeys_available == nullptr)
                  {
                    journeys_available = new_obj;
                    journeys_available2 = new_obj;
                  }
                }
              }
              trains = trains->next;
            }
            curr = curr->next;
          }
        }
        else
        {
          listOfObjects<Networkobj *> *curr = q->object->journies;
          while (curr != nullptr)
          {
            listOfObjects<TrainInfoPerStation *> *trains = currinf->object->trains;
            while (trains != nullptr)
            {
              Networkobj *new_net = new Networkobj();
              listOfObjects<TrainInfoPerStation *> *t = curr->object->trains;
              while (t != nullptr)
              {
                if (new_net->trains != nullptr)
                {
                  listOfObjects<TrainInfoPerStation *> *tr = new listOfObjects<TrainInfoPerStation *>(t->object);
                  new_net->trains2->next = tr;
                  new_net->trains2 = new_net->trains2->next;
                }
                if (new_net->trains == nullptr)
                {
                  listOfObjects<TrainInfoPerStation *> *tr = new listOfObjects<TrainInfoPerStation *>(t->object);
                  new_net->trains = tr;
                  new_net->trains2 = tr;
                }

                t = t->next;
              }
              listOfObjects<int *> *d = curr->object->station_indexes;
              while (d != nullptr)
              {
                if (new_net->station_indexes == nullptr)
                {
                  listOfObjects<int *> *ij = new listOfObjects<int *>(d->object);
                  new_net->station_indexes = ij;
                  new_net->station_indexes2 = ij;
                }
                else
                {
                  listOfObjects<int *> *ij = new listOfObjects<int *>(d->object);
                  new_net->station_indexes2->next = ij;
                  new_net->station_indexes2 = new_net->station_indexes2->next;
                }
                d = d->next;
              }
              new_net->stopovers = curr->object->stopovers;
              listOfObjects<Networkobj *> *new_obj = new listOfObjects<Networkobj *>(new_net);
              if (trains->object->journeyCode != new_obj->object->trains2->object->journeyCode)
              {
                if (new_obj->object->stopovers < stopovers)
                {
                  listOfObjects<TrainInfoPerStation *> *train = presentadd(trains, stationInfo[index]);
                  bool ispath = true;
                  if (train->object->depTime - new_obj->object->trains2->object->arrTime > t_time)
                  {
                    ispath = false;
                  }
                  listOfObjects<TrainInfoPerStation *> *new_train = new listOfObjects<TrainInfoPerStation *>(trains->object);
                  new_obj->object->trains2->next = new_train;
                  new_train->prev = new_obj->object->trains2;
                  new_obj->object->trains2 = new_obj->object->trains2->next;
                  int *num = new int(q->object->Index);
                  listOfObjects<int *> *val1 = new listOfObjects<int *>(num);
                  new_obj->object->station_indexes2->next = val1;
                  val1->prev = new_obj->object->station_indexes2;
                  new_obj->object->station_indexes2 = new_obj->object->station_indexes2->next;
                  new_obj->object->stopovers++;
                  if (ispath)
                  {
                    if (journeys_available != nullptr)
                    {
                      journeys_available2->next = new_obj;
                      journeys_available2 = journeys_available2->next;
                    }
                    else
                    {
                      journeys_available = new_obj;
                      journeys_available2 = new_obj;
                    }
                                    }
                }
              }
              else
              {
                if (new_obj->object->stopovers <= stopovers)
                {
                  if (journeys_available == nullptr)
                  {
                    journeys_available = new_obj;
                    journeys_available2 = new_obj;
                  }
                  else
                  {
                    journeys_available2->next = new_obj;
                    journeys_available2 = journeys_available2->next;
                  }
                }
              }
              trains = trains->next;
            }
            curr = curr->next;
          }
        }
      }
      else
      {
        Node *new_node = new Node(currinf->object->adjacentStnIndex);
        if (q->object->Index == stn1 && q->object->journies->object->trains->next == NULL)
        {
          listOfObjects<Networkobj *> *curr = q->object->journies;
          while (curr != nullptr)
          {
            listOfObjects<TrainInfoPerStation *> *trains = currinf->object->trains;
            while (trains != nullptr)
            {
              Networkobj *new_net = new Networkobj();
              listOfObjects<TrainInfoPerStation *> *t = curr->object->trains;
              while (t != nullptr)
              {
                if (new_net->trains != nullptr)
                {
                  listOfObjects<TrainInfoPerStation *> *tr = new listOfObjects<TrainInfoPerStation *>(t->object);
                  new_net->trains2->next = tr;
                  new_net->trains2 = new_net->trains2->next;
                }
                else if (new_net->trains == nullptr)
                {
                  listOfObjects<TrainInfoPerStation *> *tr = new listOfObjects<TrainInfoPerStation *>(t->object);
                  new_net->trains = tr;
                  new_net->trains2 = tr;
                }

                t = t->next;
              }
              listOfObjects<int *> *d = curr->object->station_indexes;
              while (d != nullptr)
              {
                if (new_net->station_indexes == nullptr)
                {
                  listOfObjects<int *> *ij = new listOfObjects<int *>(d->object);
                  new_net->station_indexes = ij;
                  new_net->station_indexes2 = ij;
                }
                else if (!(new_net->station_indexes == nullptr))
                {
                  listOfObjects<int *> *ij = new listOfObjects<int *>(d->object);
                  new_net->station_indexes2->next = ij;
                  new_net->station_indexes2 = new_net->station_indexes2->next;
                }
                d = d->next;
              }
              listOfObjects<Networkobj *> *new_obj = new listOfObjects<Networkobj *>(new_net);
              if (trains->object->journeyCode == new_obj->object->trains2->object->journeyCode)
              {
                if (new_node->journies == nullptr)
                {
                  new_node->journies = new_obj;
                  new_node->journies2 = new_obj;
                }
                else if (!(new_node->journies == nullptr))
                {

                  new_node->journies2->next = new_obj;
                  new_node->journies2 = new_node->journies2->next;
                }
              }
              trains = trains->next;
            }
            curr = curr->next;
          }
        }
        else
        {
          listOfObjects<Networkobj *> *curr = q->object->journies;
          while (curr != nullptr)
          {
            listOfObjects<TrainInfoPerStation *> *trains = currinf->object->trains;
            while (trains != nullptr)
            {
              Networkobj *new_net = new Networkobj();
              listOfObjects<TrainInfoPerStation *> *t = curr->object->trains;
              while (t != nullptr)
              {
                if (new_net->trains == nullptr)
                {
                  listOfObjects<TrainInfoPerStation *> *tr = new listOfObjects<TrainInfoPerStation *>(t->object);
                  new_net->trains = tr;
                  new_net->trains2 = tr;
                }
                else if (new_net->trains != nullptr)
                {
                  listOfObjects<TrainInfoPerStation *> *tr = new listOfObjects<TrainInfoPerStation *>(t->object);
                  new_net->trains2->next = tr;
                  new_net->trains2 = new_net->trains2->next;
                }
                t = t->next;
              }
              listOfObjects<int *> *d = curr->object->station_indexes;
              while (d != nullptr)
              {
                if (new_net->station_indexes == nullptr)
                {
                  listOfObjects<int *> *ij = new listOfObjects<int *>(d->object);
                  new_net->station_indexes = ij;
                  new_net->station_indexes2 = ij;
                }
                else
                {
                  listOfObjects<int *> *ij = new listOfObjects<int *>(d->object);
                  new_net->station_indexes2->next = ij;
                  new_net->station_indexes2 = new_net->station_indexes2->next;
                }
                d = d->next;
              }
              new_net->stopovers = curr->object->stopovers;
              listOfObjects<Networkobj *> *new_obj = new listOfObjects<Networkobj *>(new_net);
              if (trains->object->journeyCode == new_obj->object->trains2->object->journeyCode)
              {
                if (new_obj->object->stopovers <= stopovers)
                {
                  if (new_node->journies == nullptr)
                  {

                    new_node->journies = new_obj;
                    new_node->journies2 = new_obj;
                  }
                  else if (new_node->journies != nullptr)
                  {
                    new_node->journies2->next = new_obj;
                    new_node->journies2 = new_node->journies2->next;
                  }
                }
              }
              else
              {
                listOfObjects<TrainInfoPerStation *> *train = presentadd(trains, stationInfo[index]);
                listOfObjects<TrainInfoPerStation *> *new_train = new listOfObjects<TrainInfoPerStation *>(trains->object);
                bool ispath = true;
                if (train->object->depTime - new_obj->object->trains2->object->arrTime > t_time)
                {
                  ispath = false;
                }
                new_obj->object->trains2->next = new_train;
                new_train->prev = new_obj->object->trains2;
                new_obj->object->trains2 = new_obj->object->trains2->next;
                int *num = new int(q->object->Index);
                listOfObjects<int *> *val1 = new listOfObjects<int *>(num);
                new_obj->object->station_indexes2->next = val1;
                val1->prev = new_obj->object->station_indexes2;
                new_obj->object->station_indexes2 = val1;
                new_obj->object->stopovers++;
                if (new_obj->object->stopovers <= stopovers)
                {
                  if (ispath)
                  {
                    if (new_node->journies != nullptr)
                    {
                      new_node->journies2->next = new_obj;
                      new_node->journies2 = new_node->journies2->next;
                    }
                    else
                    {

                      new_node->journies = new_obj;
                      new_node->journies2 = new_obj;
                    }
                  }
                }
              }
              trains = trains->next;
            }
            curr = curr->next;
          }
        }
        listOfObjects<Node *> *node = new listOfObjects<Node *>(new_node);
        if (node->object->journies != nullptr)
        {
          tail->next = node;
          tail = node;
        }
      }
      currinf = currinf->next;
    }
    q = q->next;
    journeys_available = AlternateBFS(t_time, stopovers, stationInfo, q, tail, journeys_available, journeys_available2, stn1, stn2, adjacency); // The recursive call
  }
  return journeys_available;
}
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  
  int stn1 = stnNameToIndex.get(srcStnName)->value;
  int stn2 = stnNameToIndex.get(destStnName)->value;
  listOfObjects<Networkobj *> *journeys_available = nullptr;
  listOfObjects<Networkobj *> *journeys_available2 = nullptr;
  Node *new_node = new Node(stn1);
  listOfObjects<Node *> *q = new listOfObjects<Node *>(new_node);
  listOfObjects<StationConnectionInfo *> *currinf = adjacency[stn1].toStations;
  listOfObjects<TrainInfoPerStation *> *source_trains = stationInfo[stn1];
  while (currinf != nullptr) // Population the Node of the source station with trains leaving from the source station
  {
    listOfObjects<TrainInfoPerStation *> *trains = currinf->object->trains;
    while (trains != nullptr)
    {
      listOfObjects<TrainInfoPerStation *> *train = presentadd(trains, source_trains);
      if (q->object->journies == nullptr)
      {
        Networkobj *new_net = new Networkobj();
        listOfObjects<TrainInfoPerStation *> *new_train = new listOfObjects<TrainInfoPerStation *>(train->object);
        int *num = new int(stn1);
        listOfObjects<int *> *new_index = new listOfObjects<int *>(num);
        new_net->station_indexes = new_index;
        new_net->station_indexes2 = new_index;
        new_net->trains = new_train;
        new_net->trains2 = new_train;
        listOfObjects<Networkobj *> *new_obj = new listOfObjects<Networkobj *>(new_net);
        q->object->journies = new_obj;
        q->object->journies2 = new_obj;
      }
      else
      {
        Networkobj *new_net = new Networkobj();
        listOfObjects<TrainInfoPerStation *> *new_train = new listOfObjects<TrainInfoPerStation *>(train->object);
        int *num = new int(stn1);
        listOfObjects<int *> *new_index = new listOfObjects<int *>(num);
        new_net->station_indexes = new_index;
        new_net->station_indexes2 = new_index;
        new_net->trains = new_train;
        new_net->trains2 = new_train;
        listOfObjects<Networkobj *> *new_obj = new listOfObjects<Networkobj *>(new_net);
        new_obj->next = q->object->journies;
        q->object->journies->prev = new_obj;
        q->object->journies = new_obj;
      }
      trains = trains->next;
    }
    currinf = currinf->next;
  }
  listOfObjects<Node *> *tail;
  tail = q;
  journeys_available = AlternateBFS(maxTransitTime, maxStopOvers, stationInfo, q, tail, journeys_available, journeys_available2, stn1, stn2, adjacency); // Calling AlternateBFS from the source station
  listOfObjects<Networkobj *> *curr = journeys_available;
  string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  if (curr == nullptr)
  {
    cout << "No journies available" << endl;
  }
  else
  {
    cout << " AVAILABLE JOURNIES ARE THE FOLLOWING \n"
         << endl;
    while (curr != nullptr)
    {
      cout << "STOPS :" << curr->object->stopovers << endl;
      cout << ""
           << "STARTS: "
           << "" << endl;
      listOfObjects<int *> *stn_ptr = curr->object->station_indexes;
      listOfObjects<TrainInfoPerStation *> *train = curr->object->trains;
      int d = 0;
      while (stn_ptr != NULL)
      {
        if (d != 0)
        {
          cout << ""
               << "CONTINUE WITH"
               << "" << endl;
        }
        cout << "Station: " << stnNameToIndex.getKeyAtIndex(*stn_ptr->object) << endl;
        cout << "Journey code: "
             << "" << train->object->journeyCode << ""
             << " ";
        cout << ""
             << "Arrival: "
             << "";
        if (train->object->arrTime == -1)
        {
          cout << "Starts";
        }
        else
        {
          cout << train->object->arrTime;
        }
        cout << ""
             << " Departure: "
             << "";
        if (train->object->depTime == -1)
        {
          cout << "Ends";
        }
        else
        {
          cout << train->object->depTime;
        }
        cout << endl;
        stn_ptr = stn_ptr->next;
        train = train->next;
        d++;
      }
      cout << ""
           << "ENDS: "
           << "" << endl;
      cout << stnNameToIndex.getKeyAtIndex(stn2) << endl;
      train = curr->object->trains2;
      cout << "Day/days of travelling: "
           << " ";
      int k=0;     
      while(k<7) {
        if (train->object->daysOfWeek[k])
        {
          // cout << "" << days[d] << "" << "  ";
          cout << days[k] << " ";
        }
        k++;
      }    
     
      cout << '\n'
           << endl;
      curr = curr->next;
    }
  }

}


#endif