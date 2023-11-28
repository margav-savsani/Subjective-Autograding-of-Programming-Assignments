#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
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

  // taking out the index where srcStn and destStn are stored
  int srcIndex = stnNameToIndex.get(srcStnName)->value;
  int destIndex = stnNameToIndex.get(destStnName)->value;
  // while finding the route whenever the number of stops exceeds maxStopOvers
  // then break
  int num_stops = 0;
  
  // *************************************** TODO ***************************************
  // so applying dfs here would make more sense as starting from the source station we try
  // to traverse a path and if we reach a dead end without finding the destination we 
  // backtrack and check all other stations that can be reached through the station just before
  // and continue doing this till we cover all possible paths , but here let's say in a path
  // we come along the destination then we have to check if the number of different journey codes
  // we traversed along is less than the maxStopUser ,so we need to store it in some way
  // Also we need to make sure that we don't continue on a path where waiting time is greater
  // than the time passed as a parameter , so since we are performing a dfs we would have to 
  // bactrack on the path and continue the search from there i.e basically move to next in the
  // list of objects list that would be storing all these adjacent stations
  // Also take care of the days while you are checking the transit time between arrival
  // at a station and departure for the train from that station

  StationAdjacencyList *src_adj = &adjacency[srcIndex];
  listOfObjects<StationAdjacencyList *> *adjstnlist = new listOfObjects<StationAdjacencyList *>(src_adj);

  //loop till the node where the adjacency list is not 0 as where it is 0 we would have to backtrack
  while(src_adj != nullptr){
    // this would have all the statoins that are adjacent to the node whose src_adj is checked above
    listOfObjects<StationConnectionInfo*> *adj = adjstnlist->object->toStations;
    while(adj!=nullptr){
      num_stops++;
      if(num_stops>maxStopOvers) break; // recheck
      if(adj->object->trains->object->depTime - adj->object->trains->object->arrTime >= maxTransitTime){
        break;
      } //recheck
      adj = adj->next;
    }
    // setting the variable as the adjacency list of the adjacent station of src to loop recursively 
    src_adj = &adjacency[adj->object->adjacentStnIndex];
  }

  return;
}

#endif
