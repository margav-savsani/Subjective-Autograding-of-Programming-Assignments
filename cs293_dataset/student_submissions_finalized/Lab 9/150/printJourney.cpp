#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  int start_index = stnNameToIndex.get(srcStnName)->value;
  int end_index =  stnNameToIndex.get(destStnName)->value;
  StationAdjacencyList mystart =adjacency[start_index];
  // insert your code here
   listOfObjects<StationConnectionInfo *> *myqueue = adjacency[start_index].fromStations;
   if (myqueue==nullptr) cout << "hi";
   while (myqueue != nullptr){
     cout << myqueue->object->trains->object->journeyCode;
       if (myqueue->object->adjacentStnIndex == end_index)
             {
               listOfObjects<TrainInfoPerStation *> *mytrain =myqueue->object->trains;
               while(mytrain!=nullptr){
                cout << mytrain->object->journeyCode;
                mytrain=mytrain->next;
               }
             }
        else {
                 listOfObjects<StationConnectionInfo *> *mycurr =myqueue;
                 while(mycurr->next!=nullptr){
                  mycurr=mycurr->next;
                 }
                  mycurr->next = adjacency[myqueue->object->adjacentStnIndex].toStations;

        }



   }
  cout << "This function is to be implemented by you." << endl;
  
  return;
}
