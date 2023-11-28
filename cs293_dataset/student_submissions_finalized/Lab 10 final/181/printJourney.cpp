#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
int c;
bool directjourney1(StationAdjacencyList *A, int index1, int index2, int jcode, int maxstopovers, int dayofweek,int arrivaltime)
{
  listOfObjects<StationConnectionInfo *> *Stationsconnect = A[index1].toStations;
  listOfObjects<TrainInfoPerStation *> *t;
  if (index1 == index2 && maxstopovers == 0)
  {
    return true;
  }
  bool a = false;
  while (Stationsconnect != nullptr)
  {
    t = Stationsconnect->object->trains;
    while (t != nullptr)
    {   if(Stationsconnect!=nullptr)
      if (t->object->journeyCode == jcode)
      {
        if (directjourney1(A, Stationsconnect->object->adjacentStnIndex, index2, jcode, maxstopovers, dayofweek,t->object->arrTime))
        {
          a = true;
        }
      }
      if (t->object->journeyCode != jcode)
      {
        if (directjourney1(A, Stationsconnect->object->adjacentStnIndex, index2, t->object->journeyCode, maxstopovers - 1, dayofweek,t->object->arrTime))
        {
          a = true;
        }
      }
      t = t->next;
    }
    Stationsconnect = Stationsconnect->next;
    if (Stationsconnect == nullptr)
      break;
  }
  return a;
}

bool directjourney(StationAdjacencyList *A, int index1, int index2, int jcode, int maxstopovers, int dayofweek,int arrivaltime)
{
  listOfObjects<StationConnectionInfo *> *Stationsconnect = A[index1].toStations;
  listOfObjects<TrainInfoPerStation *> *t;
  if (index1 == index2 && maxstopovers == 0)
  {
    cout << "END" << endl;
    return true;
  }
  bool a = false;
  while (Stationsconnect != nullptr)
  {
    t = Stationsconnect->object->trains;
    while (t != nullptr)
    {
      if (t->object->journeyCode == jcode)
      {
        if (directjourney1(A, Stationsconnect->object->adjacentStnIndex, index2, jcode, maxstopovers, dayofweek,t->object->arrTime))
        {
          a = true;
          directjourney(A, Stationsconnect->object->adjacentStnIndex, index2, jcode, maxstopovers, dayofweek,t->object->arrTime);
        }
      }
      if (t->object->journeyCode != jcode)
      {
        if (directjourney1(A, Stationsconnect->object->adjacentStnIndex, index2, t->object->journeyCode, maxstopovers - 1, dayofweek,t->object->arrTime) && t->object->daysOfWeek[dayofweek])
        {
          cout << t->object->journeyCode << " " << maxstopovers - 1 <<" arrtime "<<t->object->arrTime<<" deptime "<<t->object->depTime<< endl;
          a = true;
          directjourney(A, Stationsconnect->object->adjacentStnIndex, index2, t->object->journeyCode, maxstopovers - 1, dayofweek,t->object->arrTime);
        }
      }
      t = t->next;
    }
    Stationsconnect = Stationsconnect->next;
    if (Stationsconnect == nullptr)
      break;
  }
  return a;
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  int c = maxTransitTime;
  /////////////////////////////////////////////////////////////////////////
  Entry<int> *j2 = stnNameToIndex.get(destStnName);
  int index2 = j2->value;
  Entry<int> *j1 = stnNameToIndex.get(srcStnName);
  int index1 = j1->value;
  bool directjourneyavailable = false;
  listOfObjects<StationConnectionInfo *> *stationsconnect = adjacency[index1].toStations;
  listOfObjects<TrainInfoPerStation *> *t;
  for (int j = 0; j < 7; j++)
  {
    for (int i = 0; i <= maxStopOvers; i++)
    {
      listOfObjects<StationConnectionInfo *> *stationsconnect = adjacency[index1].toStations;
      string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
      while (stationsconnect != nullptr)
      {
        t = stationsconnect->object->trains;
        while (t != nullptr)
        {
          if (directjourney1(adjacency, stationsconnect->object->adjacentStnIndex, index2, t->object->journeyCode, i, j,t->object->arrTime))
          {
            printStationInfo(t);
            directjourneyavailable = true;
            cout << days[j] << endl;
            directjourney(adjacency, stationsconnect->object->adjacentStnIndex, index2, t->object->journeyCode, i, j,t->object->arrTime);
            break;
          }
          t = t->next;
        }
        stationsconnect = stationsconnect->next;
        if (stationsconnect == nullptr)
        {
          break;
        }
      }
    }
  }
  if (directjourneyavailable == false)
    cout << "N0 DIRECT TRAINS AVAILABLE" << endl;
  return;
  ///////////////////////////////////////////////////////////////////////////

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp

  return;
}
#endif
