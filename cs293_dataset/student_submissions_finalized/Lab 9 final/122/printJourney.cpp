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
  int a = stnNameToIndex.findFreeIndex(srcStnName);
  int b = stnNameToIndex.findFreeIndex(srcStnName);
  StationAdjacencyList s = A[a];
  listOfObjects<StationConnectionInfo *> * t =  s.toStations;
  while(t != nullptr){
      StationConnectionInfo c = t->object;
      listOfObjects<TrainInfoPerStation *> * tr = c->trains;
      while(tr ! = nullptr){
        queue<int>q;
        q.push_back(t->object->adjacentStnIndex);
        while( ! q.empty()){
          
          StationAdjacencyList v = A[q.top]
          q.pop;
          listOfObjects<StationConnectionInfo *> * i =  v.toStations;
          listOfObjects<TrainInfoPerStation *> * tra = vi->object->trains;
          while(tra != nullptr){
            if(tra.journeyCode == tr->journeyCodes){
              if(i->object->adjacentStnIndex == b){
              }
              else{
                q.push_back(i->object->adjacentStnIndex);
              }
            }

          } 
        }  
        tr = tr->next;      
      }

      t = t->next;
        
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
