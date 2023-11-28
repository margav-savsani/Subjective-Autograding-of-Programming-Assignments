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
  // inserting my code
  int s_index = stnNameToIndex.hashValue(srcStnName);
  int dest_index = stnNameToIndex.hashValue(destStnName);

  
  cout << "This function is to be implemented by me" << endl;
  int col[DICT_SIZE];
  col[s_index] = 2;
  
  
  
  
  return;
}
