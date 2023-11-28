#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#include <bits/stdc++.h>
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  int x = stnNameToIndex.get(srcStnName)->value; int des = stnNameToIndex.get(destStnName)->value;
  
  StationAdjacencyList l = adjacency[x];
  
  listOfObjects<TrainInfoPerStation *> *direct_trains; 
  
  queue<int> q; Dictionary<int> d;
  
  listOfObjects<StationConnectionInfo *> *curr = l.toStations;
  
  while(curr!=nullptr){
      listOfObjects<TrainInfoPerStation *> *t = curr->object->trains; 
      
      while(t!=nullptr){
         int jc = t->object->journeyCode;  
         q.push(curr->object->adjacentStnIndex);
         
         while (q.size()!=0){
             
            int k = q.front();  l = adjacency[k];  
            
            
            q.pop();   
         }
         
         t = t->next; 
      }
      curr = curr->next;
  } 
  // insert your code here
  
  cout << "This function is to be implemented by you." << endl;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
