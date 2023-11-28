#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#define IN_PROGRESS 0
#define INVALID -1
#define VALID 1
using namespace std;

int Planner::DFS(int stationIndex, int countStopOvers, int maxStopOvers, int maxTransitTime){
  // check countStopOvers > maxStopOvers as invalid
  if(countStopOvers>maxStopOvers){return INVALID;}

  listOfObjects<StationConnectionInfo *> *toList = new listOfObjects<StationConnectionInfo *>(nullptr);
  toList = adjacency[stationIndex].toStations; // to store the linked list of Stations which can be reached from the starting station

  while(toList!=nullptr){

    toList = toList->next;
  }

  //before calling DFS on the next node check maxTransitTime <= (DepartureOftrain to that station - ArrivalTime of the previous train)

}
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
   // To get the starting station index 
  Entry<int>* startStationEntry = stnNameToIndex.get(srcStnName);
  int startIndex = startStationEntry->value;

  // To getthe index of the end station
  Entry<int>* endStationEntry = stnNameToIndex.get(destStnName);
  int endIndex = endStationEntry->value;

  // Access the pointer to the out linked list of trains from the start stations to check which nodes to traverse during the BFS
  listOfObjects<StationConnectionInfo *> *toList = new listOfObjects<StationConnectionInfo *>(nullptr);
  toList = adjacency[startIndex].toStations; // to store the linked list of Stations which can be reached from the starting station

  while(toList!=NULL){
    
    toList = toList->next;
  }


  
  
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
