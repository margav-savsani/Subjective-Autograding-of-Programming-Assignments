#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

// TrainInfoPerStation* check(){

// }

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  
  cout << "This function is to be implemented by you." << endl;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  StationAdjacencyList source = adjacency[stnNameToIndex.hashValue(srcStnName)];
  //listOfObjects<TrainInfoPerStation *>* journ;
  listOfObjects<StationConnectionInfo *>* stopsto= source.toStations;
  //listOfObjects<StationConnectionInfo *>* stopsfr= source.toStations;
  int i=0;
  
  
  while(stopsto!= nullptr){
    listOfObjects<TrainInfoPerStation *>* st = stopsto->object->trains;
    while(st!=nullptr){
      listOfObjects<TrainInfoPerStation *>* de = stationInfo[stnNameToIndex.hashValue(destStnName)];
      if(st->object == de->object){
          printStationInfo(st);
          i++;
      }
      st = st->next;
    }
    stopsto= stopsto->next;
  }
  if(i==0) cout<<"No direct journeys available"<<endl;
  return;
}

#endif
