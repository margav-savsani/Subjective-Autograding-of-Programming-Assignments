#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

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
  int src = stnNameToIndex.hashValue(srcStnName);
  int dest = stnNameToIndex.hashValue(destStnName);

  //BFS

  bool marked[DICT_SIZE];
  marked[src] = true;
  vector<int> V;
  V.push_back(src);
  while(V.size()!=0){
    int a = V.pop();
    listOfObjects<StationConnectionInfo *> *src_to = adjacency[a].toStations;
    while(src_to){
      listOfObjects<TrainInfoPerStation *> *train = src_to->object->train;
      V.push_back();
    }
  }
  cout << "This function is to be implemented by you." << endl;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
