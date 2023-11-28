#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  
  cout << "This function is to be implemented by you." << endl;

  Entry<int> * srcIndex = stnNameToIndex.get(srcStnName);
  listOfObjects<StationConnectionInfo *> * to_st = adjacency[srcIndex->value].toStations;
  if(to_st==nullptr){
    cout << "no journeys" << endl;
    return;
  }

  listOfObjects<StationConnectionInfo *> * Station_arr = new listOfObjects<StationConnectionInfo *>(*to_st);
  listOfObjects<StationConnectionInfo *> * Station_arr_marker = Station_arr;
  while(Station_arr!=nullptr){
    to_st = Station_arr;
    while(to_st!=nullptr){
      cout << "i" << endl;
      listOfObjects<TrainInfoPerStation*>* my_trains = to_st->object->trains;
      while(my_trains!=nullptr){
        cout << my_trains->object->journeyCode << endl;
      }
      Station_arr_marker->next = new listOfObjects<StationConnectionInfo*>(*adjacency[to_st->object->adjacentStnIndex].toStations);
      Station_arr_marker = Station_arr_marker->next;
      to_st=to_st->next;
    }
    Station_arr = Station_arr->next;
  }

  Entry<int> * destIndex = stnNameToIndex.get(srcStnName);


  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif




