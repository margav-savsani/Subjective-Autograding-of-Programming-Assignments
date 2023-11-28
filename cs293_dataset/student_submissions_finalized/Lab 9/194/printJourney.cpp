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
  
  //cout << "This function is to be implemented by you." << endl;
  Entry<int> *srcStnIndexEntry = stnNameToIndex.get(srcStnName);
  Entry<int> *dstStnIndexEntry = stnNameToIndex.get(dstStnName);
  int srcStnIndex=srcStnIndexEntry->value;
  int dstStnIndex=dstStnIndexEntry->value;
  while(adjacency[srcStnIndex]->toStations!=nullptr){
    
  }
  return;
}
