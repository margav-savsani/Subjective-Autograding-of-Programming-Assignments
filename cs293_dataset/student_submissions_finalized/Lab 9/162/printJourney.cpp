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
  int srcStnIdx =  stnNameToIndex.get(srcStnName)->value;
  int destStnIdx =  stnNameToIndex.get(destStnName)->value;
  cout << "This function is to be implemented by you." << endl;
  
  return;
}
