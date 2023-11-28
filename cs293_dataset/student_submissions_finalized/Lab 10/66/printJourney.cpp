#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

struct common{
   int adjacent;
   listOfObjects<TrainInfoPerStation *> *common_trains;
}
  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  int x = stnNameToIndex.get(srcStnName)->value; int des = stnNameToIndex.get(destStnName)->value;
  
  StationAdjacencyList l = adjacency[x];
  
  listOfObjects<TrainInfoPerStation *> *direct_trains; 
  
  queue<common> q; Dictionary<int> d;
  
  listOfObjects<StationConnectionInfo *> *curr = l.toStations;
  
  while(curr!=nullptr){
      listOfObjects<TrainInfoPerStation *> *t = curr->object->trains; 
      
      while(t!=nullptr){
         int jc = t->object->journeyCode;  
         q.push(curr->object->adjacentStnIndex);
         
         while (q.size()!=0){
             
            int k = q.front();  l = adjacency[k];  
            
            
            q.pop();  q.front();
             
         }
         
         t = t->next; 
      }
      curr = curr->next;
  }
  
  cout << "This function is to be implemented by you." << endl;

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp

  
  return;
}

#endif
