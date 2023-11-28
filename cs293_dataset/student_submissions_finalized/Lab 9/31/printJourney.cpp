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

  int start = (stnNametoIndex.get(srcStnName))->value;
  int dest = (destStnName.get(destStnName))->value;

  
  cout << "No direct journeys available" << endl;
  return;
}