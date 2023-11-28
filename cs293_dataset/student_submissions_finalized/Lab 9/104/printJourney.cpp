#ifndef PLANNER_H
#include "planner.h"
#endif

#ifnded STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

Class Queue{
  // to store list of journeycodes

  listOfObjects<int> journeyCodeList;
  listOfObjects<Entry<int>> stationNodesList;

  // to implement insertion and deletion
};

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  
  // index of source station in dictionary
  int indexOfSrcStn = stnNameToIndex.get(srcStnName)->value;

  // index of destination station in dictionary
  int indexofDestStn = stnNameToIndex.get(destStnName)->value;

  listOfObjects<StationConnectionInfo*> curr;
  listOfObjects<StationConnectionInfo*> next;

  // adjacency list of srcStation
  StationAdjacencyList *currStn = &adjacency[indexOfSrcStn];

  // train list from source station
  toTrains = currStn->toStations;

  // Remaining: to implement a queue class 
  // to store children of current nodes
  // then BFS over them storing the journey codes of parent stations
  // then check for those journey codes in children


  
  return;
}
