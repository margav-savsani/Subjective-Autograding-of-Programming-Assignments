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

  Entry<int> *srcstation = stnNameToIndex.get(srcStnName);
  Entry<int> *deststation = stnNameToIndex.get(destStnName);

  bool bool_1 = ((srcstation == nullptr) || (srcstation->value == -1));
  bool bool_2 = ((deststation == nullptr) || (deststation->value == -1));
  if (bool_1){
    cout << "Couldn't find " << srcStnName << "in data" << endl;
    return;
  }
  if (bool_2){
    cout << "Couldn't find " << destStnName << "in data" << endl;
    return;
  }

  listOfObjects<StationConnectionInfo *> *toS = adjacency[srcstation->value].toStations;
  listOfObjects<TrainInfoPerStation *> *jrnyList = new  listOfObjects<TrainInfoPerStation *> ((stationInfo[toS->object->adjacentStnIndex])->object);
  listOfObjects<TrainInfoPerStation *> *lip;
  
  // if{

  // }

  // else cout << "No direct journeys available" << endl;


  cout << srcstation->value <<endl;
  printStationInfo(stationInfo[srcstation->value]);
  bool found = false;
  while (toS != nullptr || found == false){
    cout << " hi 1" << endl;
    cout << " hi 1" << endl;
    lip = jrnyList;
    jrnyList = jrnyList->prev;
    cout << " hi 1" << endl;
    if (toS->object->adjacentStnIndex == deststation->value){
      cout << " hi 1" << endl;
      found = true; 
    }
    toS = toS->next;
    cout << " hi 1" << endl;
    // cout << toS->object->adjacentStnIndex << endl;
    // toS = toS->next;
  }
  if (found){
    cout << " hi 1" << endl;
    printStationInfo(lip);
    cout << " hi 1" << endl;
  }
  cout << " hi 1" << endl;
  listOfObjects<StationConnectionInfo *> *fromS = adjacency[srcstation->value].fromStations;
  cout << " hi 1" << endl;
  cout << deststation->value <<endl;



  // insert your code here
  
  // cout << "This function is to be implemented by you." << endl;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
