#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "codes.h"
#include "std_headers.h"
#include "planner.h"
#include<vector>
#endif
using namespace std;

bool checkfunc(listOfObjects<TrainInfoPerStation *>*A, listOfObjects<TrainInfoPerStation *>*B, int maxTransitTime){
  // This function gives the true of false for checking trains if days are different or same
    int a, b;
    int c = A->object->arrTime;// arrival time of train at station A.
    int d = B->object->depTime;// departure rime of train at station B.
    for(int i=0;i<7;i++){
        if(A->object->daysOfWeek[i] == true){// Checks if train is present at station A in any of the days.
            a = i;
            break;
        }
    }
    for(int i=0;i<7;i++){// at station B
        if(B->object->daysOfWeek[i]){
            b = i;
            break;
        }
    }
    if(a < b){// if days are different then compares maxTransitTime and returns accordingly.
        if((b-a)*2400+(d-c) < maxTransitTime){
            return true;
        }
        else{
            return false;
        }
    }
    if(b < a){// if days are different and then compares maxTransitTime and returns accordingly.
        if((7+b-a)*2400+(d-c) < maxTransitTime){
            return true;
        }
        else{
            return false;
        }
    }
    if(a == b){// if days are same the just compares arrtime and deptime and returns accordingly.
        if(d-c < maxTransitTime){
            return true;
        }
        else{
            return false;
        }
    }
return false;
}


bool myfunc(StationAdjacencyList *adj,listOfObjects<TrainInfoPerStation *>*stat, int curr, int dest, int maxStopOvers, int maxTransitTime, int jcode){
  if(curr == dest){// checks if destination is present.
    return true;
  }
  else if(maxStopOvers == 0){// else if maxStopOvers are zero.
    return false;
  }
  else{// if not any of above all then recursion of function.
    int a;
    listOfObjects<StationConnectionInfo *> *list = adj[curr].toStations;// adjacent to curr station
    while(list != nullptr){
      listOfObjects<TrainInfoPerStation *> *trainlist = list->object->trains;// list of trains from source to adjacent station.
      while(trainlist != nullptr){
        a = list->object->adjacentStnIndex;// adjacent index to station.
        listOfObjects<TrainInfoPerStation *> *list1 = stat;// stationinfo[a] gives list of trains of station a.
        while(list1 != nullptr){
          if(checkfunc(trainlist, list1, maxTransitTime) && trainlist->object->journeyCode != jcode){
            myfunc(adj, stat, a, dest, maxStopOvers-1, maxTransitTime, jcode);
          }
          list1 = list1->next;
        }
        trainlist = trainlist->next;
      }
      list = list->next;
    }
  }
  return false;
}


void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  int srcStnIdx = stnNameToIndex.get(srcStnName)->value;
  int destStnIdx = stnNameToIndex.get(destStnName)->value;
  listOfObjects<StationConnectionInfo *> * adjToList = adjacency[srcStnIdx].toStations;
  listOfObjects<TrainInfoPerStation *> *list = new listOfObjects<TrainInfoPerStation *>(0);
  while(adjToList != nullptr){
    listOfObjects<TrainInfoPerStation *> *ltrai = adjToList->object->trains;
    while(ltrai != nullptr){
      int a = adjToList->object->adjacentStnIndex;
      bool c = myfunc(adjacency, stationInfo[a], srcStnIdx, destStnIdx, maxStopOvers, maxTransitTime, ltrai->object->journeyCode);
      if(c){
        list->next = ltrai;
        list = list->next;
      }
    }
    adjToList = adjToList->next;
  }
  while(list != nullptr){
    printStationInfo(list);
    list = list->prev;
  }
  return;
}
#endif
