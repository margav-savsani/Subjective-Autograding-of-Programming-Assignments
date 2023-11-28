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
  Entry<int> *e = stnNameToIndex.get(stationInfo);
  int i=e->value;
  StationAdjacencyList s=adjacency[i];
  

  cout << "This function is to be implemented by you." << endl;
  
  return;
}
