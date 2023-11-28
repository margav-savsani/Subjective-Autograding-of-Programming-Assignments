#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#include <list>
#endif

using namespace std;

void printAllPathsUtil(int u, int d, bool visited[],list<int*>paths,int path[], int& path_index,StationAdjacencyList*adjacency,int maxStopOvers)
{
    // Mark the current node and store it in path[]
    visited[u] = true;
    path[path_index] = u;
    path_index++;
 
    // If current vertex is same as destination, then print
    // current path[]
    if (u == d) {
      if(path_index<=maxStopOvers)
          paths.push_back(path);
    }
    else // If current vertex is not destination
    {
        // Recur for all the vertices adjacent to current
        // vertex
        StationAdjacencyList v = adjacency[u];
        listOfObjects<StationConnectionInfo *>* adj = v.fromStations;
        while(adj!=nullptr){
            int adjst = adj->object->adjacentStnIndex;
            if (!visited[adjst]){
                printAllPathsUtil(adjst, d, visited,paths, path,
                                  path_index,adjacency,maxStopOvers);}
                  adj=adj->next;}
    }
 
    // Remove current vertex from path[] and mark it as
    // unvisited
    path_index--;
    visited[u] = false;
}
listOfObjects<TrainInfoPerStation*>* gettrains(int src,int dest,StationAdjacencyList*adjacency){
  StationAdjacencyList v = adjacency[src];
  listOfObjects<StationConnectionInfo *>* adj = v.fromStations;
  while(adj!=nullptr){
    if(adj->object->adjacentStnIndex==dest){
      return adj->object->trains;
    }
    adj=adj->next;
  }
  return nullptr;
}
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

  int sourceIndex = stnNameToIndex.get(srcStnName)->value;
  int destIndex = stnNameToIndex.get(destStnName)->value;
  bool* visted;
  visted = new bool[DICT_SIZE];
  for(int i=0;i<DICT_SIZE;i++){
  visted[i]=false;  
  }
  int*path=new int [DICT_SIZE];
  int path_index = 0;
  list<int*>paths;
  printAllPathsUtil(sourceIndex,destIndex,visted,paths,path,path_index,adjacency,maxStopOvers);
  list<int*>::iterator it;
  for (it = paths.begin(); it != paths.end(); ++it){
    TrainInfoPerStation* dummy = new TrainInfoPerStation(0,0,0,0);
    listOfObjects<TrainInfoPerStation*> *list=new listOfObjects<TrainInfoPerStation* >(dummy);
      while(*(*it)!=0){
        while(list->next!=nullptr){
          list=list->next;
        }
        list->next=gettrains(*(*it),*((*it)+1),adjacency);
      }
      printStationInfo(list);
  }
}

#endif
