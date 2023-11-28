#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  if(adjacency[ stnNameToIndex.get(destStnName)->value ].fromStations == nullptr){
    cout << "No direct journeys available" << endl;
  }
  if(adjacency[ stnNameToIndex.get(srcStnName)->value ].fromStations == nullptr){
    cout << "No direct journeys available" << endl;
  }
  
  return;
}
