#ifndef PLANNER_H
#include "planner.h"
#include <string.h> //I defined it to debug error messages
#endif

#ifnded STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  //something is wrong with the headers, getting erorrs everywhere
  // STD_HEADERS_H file is missing during the inlab time
  int s = stnNameToIndex.get(srcStnName)->value;
  int d = stnNameToIndex.get(destStnName)->value;
  StationAdjacencyList st = adjacency[s];
  listOfObjects<StationConnectionInfo *> *lis = st.toStations;
  while (true)
  {
    if(lis==nullptr) break;
    // if()
  }
  
  return;
}