#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  int index1 = stnNameToIndex.get(srcStnName).value;
  StationAdjacencyList srcStn = adjacency[index1];
  int index2 = stnNameToIndex.get(destStnName).value;
  StationAdjacencyList destStn = adjacency[index2];

  cout << "This function is to be implemented by you." << endl;
  
  return;
}
