#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP
#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#include <queue> //used the queue
#endif

using namespace std;
//checking the node from which the destination is present
void check(int initIndx,int finIndx,StationAdjacencyList *adjacency){
  StationAdjacencyList v = adjacency[initIndx];
  listOfObjects<StationConnectionInfo *>* toadj = v.toStations;
  while(toadj->next != NULL){
    
  }
  
}
void BFS(listOfObjects<StationConnectionInfo *> *a,int fin,queue<int> q){
  listOfObjects<StationConnectionInfo *> *nextstat = a;
  while(nextstat->next != NULL){
    listOfObjects<TrainInfoPerStation *> *netr = nextstat->object->trains;
    if(nextstat->prev == NULL){
      while(netr->next != NULL){
        q.emplace(netr->object->journeyCode);
        /*first i will add all the journey codes adjacent to the parent node next i will 
        check the repeatition of the each and every journey code in that respective root if the journey code doesnt repeat 
        the i will delete it from the queue while doing this if i found the final location of the destination in the nodes 
        then i will return it ,in case if didn't find the final location then i will return a null queue.instead of doing 
        the BFS generally i will do it recursivesly taking the nodes adjacent to root 
        ( i will go through the node in which the final destination is present)*/ 
      }
      listOfObjects<StationConnectionInfo *> *nextadjstat ;
      bool stattrainpass;

    }
    if(nextstat->object->adjacentStnIndex == fin){
      return ;//when the final location is arrived
    }
  }
}

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  int ini = stnNameToIndex.get(srcStnName)->value;
  int fin = stnNameToIndex.get(destStnName)->value;
  StationAdjacencyList init = adjacency[ini];
  int a = 0;
  int b = 0;
  listOfObjects<StationConnectionInfo *> *u = init.toStations;
  listOfObjects<StationConnectionInfo *> *v = init.toStations;
  listOfObjects<StationConnectionInfo *> *w = init.toStations;
  while(u->next != NULL){
    a++;
    u = u->next;
  }
  queue<int> q[a];
  //finding the location of the node final

  while(v->next != NULL){
    
    BFS(v,fin,q[b]);
    b++;
  }
  //here i will call the BFS queue then if it returns empty queue then i will print no journeys 
  //available to respective destinations else i will use  a for loop and print journey info of thet respective journey
  //code then it will print the initial location and final location.  
  return;
}

#endif
