#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

listOfObjects<StationConnectionInfo *> **BFSvaluearray;

int BFS_tostorelinkedlists(listOfObjects<StationConnectionInfo *> *currStn, int level, int destStnindex, StationAdjacencyList adjacency[])
{
  int vertices_count = 0; //This function is to store each group of vertices in a level in a linkedlist
  bool match = false;    // and each level in an array BFSvaluearray
  int foundlevel;        // This is been declared as global variable to access it later 
  listOfObjects<StationConnectionInfo *> *vertices_list;
  while(currStn != nullptr)
  {
    listOfObjects<StationConnectionInfo *> *newvertex;
    newvertex->object = vertices_list->object;
    newvertex->next = vertices_list->next;
    newvertex->prev = vertices_list;
    vertices_list = currStn;
    StationAdjacencyList *find = &adjacency[destStnindex];
    if(currStn == find->toStations)
    {
      return level;
    }
    int index = currStn->object->adjacentStnIndex;
    StationAdjacencyList *nextstation = &adjacency[index];
    int returnval = BFS_tostorelinkedlists(nextstation->toStations, level+1, destStnindex, adjacency);
    if(returnval != -1) {foundlevel = returnval; match = true;}
    currStn = currStn->next;
  }
  BFSvaluearray[level] = vertices_list;
  if(match) return foundlevel;
  else return -1;
}

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  Entry<int> *srcIndex = stnNameToIndex.get(srcStnName);
  int srcStn = srcIndex->value;
  Entry<int> *destIndex = stnNameToIndex.get(destStnName);
  int destStn = destIndex->value;

  StationAdjacencyList *startlist = &adjacency[srcStn];
  
  int levelmatch = BFS_tostorelinkedlists(startlist->toStations, 1, destStn, adjacency);
  // check above this function execution 
  
  if(levelmatch == -1)
  {
    cout<<"No direct journeys available"<<endl;
    return;
  }
  else
  {
    listOfObjects<TrainInfoPerStation *> *list_toprint;
    listOfObjects<StationConnectionInfo *> *prev_list = BFSvaluearray[levelmatch];
    StationAdjacencyList *endlist = &adjacency[destStn];
    listOfObjects<StationConnectionInfo *> *prevfromStns = endlist->fromStations;
    // Now we have to match from reverse for the trains with same JourneyCode
    // and insert all of them in above mentioned "list_toprint"
    // then use given printStationInfo(list_toprint) to get all the 
    // journies information
    list_toprint = endlist->tostations->trains;
    printStationInfo(list_toprint);
    tostations = tostations->next;
    list_toprint = endlist->tostations->trains;
    printStationInfo(list_toprint);
    tostations = tostations->next;
    list_toprint = endlist->tostations->trains;
    printStationInfo(list_toprint);
    return;
  }
  //cout << "This function is to be implemented by you." << endl;
  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
}

#endif
