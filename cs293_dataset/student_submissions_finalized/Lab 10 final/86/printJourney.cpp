#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

bool findjourney(StationAdjacencyList *adjacency, int firststop, int endstop, int jrnycode)
{
  if (firststop == endstop)
    return true;

  listOfObjects<StationConnectionInfo *> *totravel = adjacency[firststop].toStations;
  listOfObjects<TrainInfoPerStation *> *alltravels;

  while (totravel != nullptr)
  {
    alltravels = totravel->object->trains;
    while (alltravels != nullptr)
    {
      if (alltravels->object->journeyCode == jrnycode)
      {
        return findjourney(adjacency, totravel->object->adjacentStnIndex, endstop, jrnycode);
      }
      alltravels = alltravels->next;
    }
    totravel = totravel->next;
  }

  return false;
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  Entry<int> *startstn = stnNameToIndex.get(srcStnName);
  int firststop = startstn->value;

  Entry<int> *stopstn = stnNameToIndex.get(destStnName);
  int endstop = stopstn->value;

  bool travel = false;
  listOfObjects<StationConnectionInfo *> *travelto = adjacency[firststop].toStations;
  listOfObjects<TrainInfoPerStation *> *alltrains;

  while (true)
  {
    alltrains = travelto->object->trains;
    while (true)
    {
      if (findjourney(adjacency, travelto->object->adjacentStnIndex, endstop, alltrains->object->journeyCode))
      {
        travel = true;
        printStationInfo(alltrains);
        break;
      }
      alltrains = alltrains->next;
      if (alltrains == nullptr)
        break;
    }
    travelto = travelto->next;
    if (travelto == nullptr)
      break;
  }

  if (travel == false)
    cout << "No direct journeys available" << endl;
  return;
}

#endif