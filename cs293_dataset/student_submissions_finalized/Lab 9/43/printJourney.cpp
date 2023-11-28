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
  Entry<int>* t = stnNametoIndex.get(srcStnName);
  int p =t->value;
  StationAdjacencyList r = adjacency[p];
  cout << "This function is to be implemented by you." << endl;
  
  return;
}
