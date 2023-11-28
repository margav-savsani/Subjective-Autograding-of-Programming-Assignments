#ifndef PLANNER_H
#include "planner.h"
#endif

#ifnded STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;



void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  // get the to station names of the srcStnName.
  // get from station names of destStnName.
  // search if tostnName contains destStnName.
  // if yes output it.
  // for each toStnName 
  
  // Getting index of srcStnName and destStnName
  static int src_hash = stnNameToIndex.get(srcStnName);
  static int dest_hash = stnNameToIndex.get(destStnName);
  
  // Storing the toStation names of source station
  listOfObjects<StationConnectionInfo *> *toStations = adjacency[src_hash].toStations;
  // Storing the fromStation names of dest station
  // listOfObjects<StationConnectionInfo *> *fromStations = adjacency[src_hash].fromStations;
  static TrainInfoPerStation *train = nullptr;
  static listOfObjects<int> *temp = new Jcode;
  while(toStations != nullptr){
    src_hash = toStations->object->adjacentStnIndex;
    if(src_hash == dest_hash){
      listOfObjects<TrainInfoPerStation *> *trains = toStations->object->trains;
      bool found = false;
      while(trains != nullptr){
        if(trains->object->journeyCode == train->journeyCode){bool == true;break;}
      }
      if(found){
        cout << "JCode : " << train->journeyCode << endl;
      }
    }
    listOfObjects<TrainInfoPerStation *> *trains = toStations->object->trains;
    if(train == nullptr){
      while(trains != nullptr){
        train = trains->object;
        printDirectJourneys(srcStnName, destStnName);
        trains = trains->next;
        train = nullptr;
      }
    }
    else{

    }
    while(trains != nullptr){

    }
  }
  cout << "This function is to be implemented by you." << endl;
  
  return;
}
