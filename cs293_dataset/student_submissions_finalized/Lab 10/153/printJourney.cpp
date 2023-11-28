#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
  
class Transition{
private:
  int station_id, wait, cur_jc, next_jc;
  //Naturally, wait is in minutes, because of the used time representation

public:
  Transition(){station_id=wait=cur_jc=next_jc=-1;}
  Transition(int sid, int cjc, int njc, int w){
    station_id=sid;
    cur_jc=cjc;
    next_jc=njc;
    wait=w;
  }
  ~Transition(){}

};

int g_dest_id;
StationAdjacencyList* g_adj_lists;
listOfObjects<TrainInfoPerStation*> **g_stnInfo;

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here

  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp


  // TODO: See plan.todo for complete plan
  g_adj_lists=this->adjacency;
  Entry<int> *entry =  this->stnNameToIndex.get(srcStnName);
  if(entry == nullptr) return;
  int src_ind = entry->value;
  entry =  this->stnNameToIndex.get(destStnName);
  if(entry == nullptr) return;
  g_dest_id = entry->value;
  
  

  return;
}

#endif
