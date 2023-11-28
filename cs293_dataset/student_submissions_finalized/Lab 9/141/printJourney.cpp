#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include<vector>

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  
  //cout << "This function is to be implemented by you." << endl;
  
  StationAdjacencyList station = adjacency[stnNameToIndex.hashValue(srcStnName)];

  listOfObjects<StationConnectionInfo *> * out = station.toStations;
  // listOfObjects<StationConnectionInfo *> * in = station.fromStations;
  
  int jc = out->object->trains->object->journeyCode;

  // Now implementing BFS with exclusively this journey code
  
  // creating a first-in-first-out queue
  vector<StationAdjacencyList> Q;
  Q.push_back(station);

  while (!Q.empty()) {
    
    // implementing BFS. 
    
  }
 
  return;
}

#endif
