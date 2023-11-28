#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;


void Planner::printPlanJourneys(string srcStnName, string destStnName,int maxStopOvers, int maxTransitTime)
{ 
  // Used entry in dictionary class to get source index and source tostations
  Entry<int > *stnindex = stnNameToIndex.get(srcStnName);
  int stnvalue = stnindex->value;
  // StationAdjacencyList src = adjacency[stnvalue];
  // listOfObjects<StationConnectionInfo *> *tostns = adjacency[stnvalue].toStations;

  // Used entry in dictionary class to get destination index
  Entry<int > *destindex = stnNameToIndex.get(destStnName);

  listOfObjects<TrainInfoPerStation *> *l = stationInfo[stnvalue];
  listOfObjects<TrainInfoPerStation *> *list2 = nullptr;
  listOfObjects<TrainInfoPerStation *> *dummy_list = stationInfo[stnvalue];
  int a = 0;
  while(l != NULL){
    a++;
    l = l->next;
  }
  int arrtrains[a] ;
  l = stationInfo[stnvalue];
  int b =0;
  while(l != NULL){
    arrtrains[b] = (l->object)->journeyCode;
    l = l->next;
    b++;
  }  
  int arrayfinal[a];  
  for(int w=0;w<a;w++){
    listOfObjects<StationConnectionInfo *> *t = adjacency[stnvalue].toStations;
    
      // here finding the node to which the train with jrnycode goes
  while(true){
  while(t != nullptr){
      listOfObjects<TrainInfoPerStation *> *l = (t->object)->trains;
      int a = 0;
      while(l != NULL){
        a++;
        l = l->next;
      }
      int at[a] ;
      l = (t->object)->trains;
      int b =0;
      while(l != NULL){
        at[b] = (l->object)->journeyCode;
        l = l->next;
        b++;
      }
      bool c = false;
      int s = sizeof(at);
      for(int i =0 ; i<s;i++){
        if(at[i] == arrtrains[w]){
          c = true;
        } 
      }
      if(c){
        break;
      }
      else{
          t = t->next;
      }
  }
  //if the train does not go any further
  if(t == NULL){
    arrayfinal[w] = -1;
    break;
  }
  //if destination is in one of the adjacent nodes
  if((t->object)->adjacentStnIndex == destindex->value){
    arrayfinal[w] = arrtrains[w]; 
    break;
  }
  //continuing with recursion 
  else{  
    t = adjacency[(t->object)->adjacentStnIndex].toStations;
  }
  }    
  }

  for(int i = 0;i<a;i++){
    if(arrayfinal[i]!=-1){
      if(list2==nullptr){
        list2 = new listOfObjects<TrainInfoPerStation *>(dummy_list->object); 
      }
      else{
        list2->next = new listOfObjects<TrainInfoPerStation *>(dummy_list->object);
        (list2->next)->prev = list2; 
        list2 = list2->next;
      }
    } 
    dummy_list = dummy_list->next; 
  }
  if( list2 == nullptr){
    cout<<"No direct journeys available"<<endl;
  }
  else{
    while(list2->prev !=nullptr){
      list2 = list2->prev;
    }
    printStationInfo(list2);    
  }
  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}


#endif
#include "std_headers.h"
#endif

using namespace std;
  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
  
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
