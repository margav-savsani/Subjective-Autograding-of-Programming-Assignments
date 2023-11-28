#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
class jrnycodestnindex
{
public:
  int Journeycode;
  int stationindex;
};
bool directjourney(StationAdjacencyList *A, int index1, int index2, int jcode)
{
  listOfObjects<StationConnectionInfo *> *Stationsconnect = A[index1].toStations;
  listOfObjects<TrainInfoPerStation *> *t;
  if (index1 == index2)
    return true;
  while (Stationsconnect!=nullptr)
  {
    t = Stationsconnect->object->trains;
    while (t!=nullptr)
    {
      if (t->object->journeyCode == jcode)
      {
        return directjourney(A, Stationsconnect->object->adjacentStnIndex, index2, jcode);
      }
      t = t->next;
    }
    Stationsconnect = Stationsconnect->next;
    if (Stationsconnect == nullptr)
      break;
  }
  return false;
}
void Planner::printDirectJourneys(string srcStnName, string destStnName)
{ // insert your code here
StationAdjacencyList a = adjacency[(stnNameToIndex.get(srcStnName))->value];
  listOfObjects<TrainInfoPerStation *> *maintrain_tail = nullptr;
  listOfObjects<int> *jrnycodes_tail = nullptr;
  listOfObjects<int> *stationindex_tail = nullptr;
  listOfObjects<StationConnectionInfo *> *h = a.toStations;
  listOfObjects<int> *jrnycodes = nullptr;
  listOfObjects<TrainInfoPerStation *> *maintrain = nullptr;
  listOfObjects<int> *stationindex = nullptr;
  while (h != nullptr)
  {
    listOfObjects<TrainInfoPerStation *> *j = h->object->trains;
    while (j != nullptr)
    {
      if (maintrain == nullptr)
      {
        maintrain = new listOfObjects<TrainInfoPerStation *>(j->object);
        jrnycodes = new listOfObjects<int>(j->object->journeyCode);
        stationindex = new listOfObjects<int>(h->object->adjacentStnIndex);
      }
      else
      {
        listOfObjects<TrainInfoPerStation *> *r = new listOfObjects<TrainInfoPerStation *>(j->object);
        listOfObjects<int> *f = new listOfObjects<int>(j->object->journeyCode);
        listOfObjects<int> *w = new listOfObjects<int>(h->object->adjacentStnIndex);
        r->next = maintrain;
        f->next = jrnycodes;
        w->next = stationindex;
        stationindex = w;
        maintrain = r;
        jrnycodes = f;
      }
      j = j->next;
    }
    h = h->next;
  }
/////////////////////////////////////////////////////////////////////////
 Entry<int> *j2 = stnNameToIndex.get(destStnName);
 int index2 = j2->value;
  Entry<int> *j1 = stnNameToIndex.get(srcStnName);
  int index1 = j1->value;
  bool directjourneyavailable = false;
  listOfObjects<StationConnectionInfo *> *stationsconnect = adjacency[index1].toStations;
  listOfObjects<TrainInfoPerStation *> *t;
  while (stationsconnect!=nullptr)
  {
    t = stationsconnect->object->trains;
    while (t != nullptr)
    {
      if (directjourney(adjacency, stationsconnect->object->adjacentStnIndex, index2, t->object->journeyCode))
      {
        directjourneyavailable = true;
        printStationInfo(t);
        break;
      }
      t = t->next;
    }
    stationsconnect = stationsconnect->next;
    if(stationsconnect==nullptr){break;}
  }
  if (directjourneyavailable == false)
    cout << "N0 DIRECT TRAINS AVAILABLE" << endl;
  return;
  ///////////////////////////////////////////////////////////////////////////
  while (maintrain != nullptr || maintrain_tail != nullptr)
  {
    if (maintrain == NULL)
    {
      maintrain = maintrain_tail;
      jrnycodes = jrnycodes_tail;
      stationindex = stationindex_tail;
      stationindex_tail = nullptr;
      maintrain_tail = nullptr;
      jrnycodes_tail = nullptr;
    }
    StationAdjacencyList k = adjacency[stationindex->object];
    listOfObjects<StationConnectionInfo *> *j = k.toStations;
    while (j != nullptr)
    {
      listOfObjects<TrainInfoPerStation *> *l = j->object->trains;
      while (l != nullptr)
      {
        if (j->object->adjacentStnIndex == stnNameToIndex.get(destStnName)->value)
        {
          cout << jrnycodes->object << endl;
          cout << "journeycode" << endl;
          break;
        }
        else if (maintrain->object->journeyCode == l->object->journeyCode)
        {
          if (maintrain_tail == nullptr)
          {
            maintrain_tail = new listOfObjects<TrainInfoPerStation *>(j->object->trains->object);
            jrnycodes_tail = new listOfObjects<int>(maintrain->object->journeyCode);
            stationindex_tail = new listOfObjects<int>(j->object->adjacentStnIndex);
          }
          else
          {
            listOfObjects<TrainInfoPerStation *> *r = new listOfObjects<TrainInfoPerStation *>(j->object->trains->object);
            listOfObjects<int> *f = new listOfObjects<int>(maintrain->object->journeyCode);
            listOfObjects<int> *q = new listOfObjects<int>(j->object->adjacentStnIndex);
            r->next = maintrain_tail;
            f->next = jrnycodes_tail;
            q->next = stationindex_tail;
            stationindex_tail = q;
            maintrain_tail = r;
            jrnycodes_tail = f;
          }
          break;
        }
        else
        {
          l = (l->next);
        }
      }
      j = j->next;
    }
    jrnycodes = jrnycodes->next;
    maintrain = maintrain->next;
    stationindex = stationindex->next;
  }
  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp

  return;
}
#endif
