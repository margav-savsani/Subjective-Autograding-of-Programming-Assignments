#ifndef PLANNER_H
#include "planner.h"
#endif

#ifnded STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  
  cout << "This function is to be implemented by you." << endl;
  
  int srcstnidx=stnNameToIndex.get(srcStnName)->value;
  int destStnIdx = stnNameToIndex.get(destStnName)->value;

  StationAdjacencyList startlist adjacency [srcStnIdx]; 
  listofobjects<StationConnectionInfo>starttolist=startlist.toStations;
  return;
}
