#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

class seqTrains
{
public:
  listOfObjects<int> *stns;
  listOfObjects<int> *trains;
  listOfObjects<int> *transitTimes;
  seqTrains()
  {
    trains = nullptr;
    transitTimes = nullptr;
  }
  seqTrains(int stn, int jrnyCode)
  {
    listOfObjects<int> *it = trains;
    listOfObjects<int> *lol = new listOfObjects<int>(jrnyCode);
    while (it != nullptr)
    {
      it = it->next;
    }
    it->next = lol;
    listOfObjects<int> *it2 = stns;
    listOfObjects<int> *lol2 = new listOfObjects<int>(stn);
    while (it2 != nullptr)
    {
      it2 = it2->next;
    }
    it2->next = lol2;
  }
  void addTrain(int jrnyCode)
  {
    listOfObjects<int> *it = this->trains;
    listOfObjects<int> *lol = new listOfObjects<int>(jrnyCode);
    while (it != nullptr)
    {
      it = it->next;
    }
    it->next = lol;
  }
  void addStn(int stn)
  {
    listOfObjects<int> *it = this->stns;
    listOfObjects<int> *lol = new listOfObjects<int>(stn);
    while (it != nullptr)
    {
      it = it->next;
    }
    it->next = lol;
  }

  void add(int stn, int jrnyCode)
  {
    listOfObjects<int> *it = this->trains;
    listOfObjects<int> *lol = new listOfObjects<int>(jrnyCode);
    while (it != nullptr)
    {
      it = it->next;
    }
    it->next = lol;
    listOfObjects<int> *it2 = this->stns;
    listOfObjects<int> *lol2 = new listOfObjects<int>(stn);
    while (it2 != nullptr)
    {
      it2 = it2->next;
    }
    it2->next = lol2;
  }
  void print()
  {
    while (trains != nullptr && transitTimes != nullptr)
    {
      cout << stns->object << " " << trains->object << " " << transitTimes->object << endl;
      trains = trains->next;
      transitTimes = transitTimes->next;
      stns = stns->next;
    }
  }
};

listOfObjects<seqTrains> *getRoutes(int src, int dest, StationAdjacencyList *adjacency, int maxStopOvers, int maxTransitTime)
{
  static int level = 0;
  static listOfObjects<seqTrains> *list = nullptr;
  static listOfObjects<seqTrains> *last = nullptr;
  if (level > maxStopOvers)
  {
    return nullptr;
  }
  if (src == dest)
  {
    seqTrains s;
    s.addStn(dest);
    list = new listOfObjects<seqTrains>(s);
    return list;
  }
  level++;
  // Code
  StationAdjacencyList srcStn = adjacency[src];
  listOfObjects<StationConnectionInfo *> *stn_and_trains = srcStn.toStations;
  listOfObjects<StationConnectionInfo *> *each_stn = stn_and_trains;
  while (each_stn != nullptr)
  {
    int nextstn = each_stn->object->adjacentStnIndex;
    listOfObjects<TrainInfoPerStation *> *each_train_per_stn = each_stn->object->trains;
    while (each_train_per_stn != nullptr)
    {
      if (list == nullptr)
      {
        list = getRoutes(nextstn, dest, adjacency, maxStopOvers, maxTransitTime);
        last = getRoutes(nextstn, dest, adjacency, maxStopOvers, maxTransitTime);
      }
      else
      {
        last->next = getRoutes(nextstn, dest, adjacency, maxStopOvers, maxTransitTime);
        getRoutes(nextstn, dest, adjacency, maxStopOvers, maxTransitTime)->prev = last;
        last = last->next;
      }
    }
  }
  // Code done
  return list;
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here

  listOfObjects<seqTrains> *routesFound = nullptr;
  int src = (stnNameToIndex.get(srcStnName))->value;
  int dest = (stnNameToIndex.get(destStnName))->value;
  StationAdjacencyList srcStn = adjacency[src];
  routesFound = getRoutes(src, dest, adjacency, maxStopOvers, maxTransitTime);
  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  return;
}

#endif
