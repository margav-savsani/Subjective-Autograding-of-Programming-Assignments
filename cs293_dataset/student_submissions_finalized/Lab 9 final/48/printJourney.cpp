#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include<bits/stdc++.h>
using namespace std;
bool find_element(std::vector<int> arr, int k){
    
    std::vector<int>::iterator it;
    
    it = std::find(arr.begin(), arr.end(), k);
    
    if(it != arr.end())
    
        return true;
    
    else
    
        return false;
}
void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  
  cout << "This function is to be implemented by you." << endl;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  int index = (stnNameToIndex.get(srcStnName))->value;
  int aindex = (stnNameToIndex.get(destStnName))->value;
  listOfObjects<StationConnectionInfo *> *all=adjacency[index].toStations;
  listOfObjects<StationConnectionInfo *> *all1=adjacency[aindex].fromStations;
  listOfObjects<TrainInfoPerStation *> *a=nullptr;
  vector<int> visited;
  while(all!=nullptr){
    if(find_element(visited,all->object->adjacentStnIndex)){
      all=all->next;
    }
    else{
      listOfObjects<TrainInfoPerStation *> *temp=all->object->trains;
      while(temp!=nullptr){
        
      }
      visited.push_back(all->object->adjacentStnIndex);
      all=all->next;
    }
  }
  // if(a!=nullptr){
  //   printStationInfo(a);
  // }
  // else{
  //   cout<<"No direct journeys available"<<endl;
  // }
  return;
}

#endif
