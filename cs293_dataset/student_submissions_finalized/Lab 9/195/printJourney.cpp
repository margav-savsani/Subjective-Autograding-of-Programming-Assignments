#ifndef PLANNER_H
#include "planner.h"
#endif
#include<iostream>

#ifnded STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  int start=stnNameToIndex.get(srcStnName)->value;
  int end=stnNameToIndex.get(destStnName)->value;
  StationAdjacencyList list=adjacency[start];
  listOfObjects<StationConnectionInfo*>* tolist=list.toStations;
  while(tolist!=nullptr){
    if(tolist->object->adjacentStnIndex==end){
      cout<<tolist->object->trains->object->journeyCode<<endl;
      return;
    }
  tolist=tolist->next;
  }
  // insert your code here
  
  cout << "This function is to be implemented by you." << endl;
  
  return;
}
