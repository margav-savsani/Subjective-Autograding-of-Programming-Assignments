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
  
  int src = stnNameToIndex.hashvalue(srcStnName);
  int dest = stnNameToIndex.hashvalue(destStnName);
  
  cout << "This function is to be implemented by you." << endl;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  bool arr[DICT_SIZE];
  arr[src_index] = true;
  vector<int> V;
  V.push_back(src_index);
  while(V.size()!=0)
  {
     int x=V.pop();
     listOfObjects<StationConnectionInfo *> *trains = src_to = adjacency[x].toStations;
     while(sr_to != NULL)
     { 
        listOfObjects<TrainInfoPerStation *> *trains = src_to->object->trains;   
        V.push_back();
       }
    }      
  
  return;
}

#endif
