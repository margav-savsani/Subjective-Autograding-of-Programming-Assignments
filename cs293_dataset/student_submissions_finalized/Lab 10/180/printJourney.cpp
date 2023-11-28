#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void recursive_find(listOfObjects<TrainInfoPerStation*>*starting_trains,listOfObjects<StationConnectionInfo*>* to_station_list ,int dest_stn_index, int &count , StationAdjacencyList adjacency[],listOfObjects<TrainInfoPerStation*>*answer){
  listOfObjects<TrainInfoPerStation*>* initial_trains = starting_trains;
  listOfObjects<StationConnectionInfo*>* stations_to = to_station_list;
  while(initial_trains != nullptr){
    int jc = initial_trains->object->journeyCode;
    while(stations_to != nullptr){

      listOfObjects<TrainInfoPerStation*>* all_trains = stations_to->object->trains;
      while(all_trains != nullptr){

        if(all_trains->object->journeyCode == jc){
          if(stations_to->object->adjacentStnIndex == dest_stn_index){
            cout << "jc: " << jc << endl;
          }
          else{
            recursive_find(starting_trains,adjacency[stations_to->object->adjacentStnIndex].toStations,dest_stn_index,count,adjacency,answer);
          }
        }
        all_trains = all_trains->next;
      }

      stations_to = stations_to->next;
    }
    initial_trains = initial_trains->next;  
  }
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

  
  return;
}

#endif
