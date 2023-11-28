#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  listOfObjects<TrainInfoPerStation *> * stations; //The linked list of station infos.
  listOfObjects<StationConnectionInfo *> * iterator; 

  // The adjacency list contains the list of adjacent nodes corresponding to a given station name.
  // Iterating through the list.
  iterator = adjacency->toStations;
  while((iterator!=NULL)&&(stnNameToIndex.getKeyAtIndex(iterator->object->adjacentStnIndex)!=srcStnName)){
    iterator = iterator->next;
  }
  listOfObjects<TrainInfoPerStation *> * trains = iterator->object->trains;
  while(trains!=NULL){
    trains = trains->next;
  }
  cout << "This function is to be implemented by you." << endl;
  
  return;
}
