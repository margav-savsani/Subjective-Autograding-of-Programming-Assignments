#ifndef PLANNER_H
#include "planner.h"
#endif

#ifnded STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  int src_hash = stnNameToIndex.hashValue(srcStnName);
  int des_hash = stnNameToIndex.hashValue(destStnName);

  listOfObjects<stationInfo> *station;

  cout << "No direct journeys available" << endl;
  
  return;
}
