#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
bool direct(int stni, int desti, StationAdjacencyList adjacency[], int jc) {
  bool k = false;                                                                   //bool variable for finding same journey code
  if (stni == desti) {
    return true;                                                                    //base case for recurrsion
  } 
  else if (stni == -1) {
    return false;                                                                   //base for terminating
  } 
  else {
    listOfObjects < StationConnectionInfo * > * adjsta = adjacency[stni].toStations; //to stations of stations with stni index
    while (adjsta != nullptr) {
      stni = adjsta -> object -> adjacentStnIndex;                                   //index to of to station
      listOfObjects < TrainInfoPerStation * > * train = adjsta -> object -> trains;  //list of trains of tostation
      while (train != nullptr) {
        if (jc == train -> object -> journeyCode) {
          k = true;                                                                  //if found the train with given journey code
          break;                                                                     //break
        } 
        else train = train -> next;                                                //else continue
      }
      if (k) {
        break;                                                                       //break the loop if found a train 
      } 
      else adjsta = adjsta -> next;                                                //else continue
    }
    if(k){
      return direct(stni, desti, adjacency, jc);                                     //recurrsion if not found
    } 
    else return false;                                                             //else return 
  }
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
   int jcode;                                                                         //journey code
  bool gotit = false;                                                                //bool for direct journey codes
  int toindex = stnNameToIndex.get(srcStnName) -> value;                             //source station index value
  int desti = stnNameToIndex.get(destStnName) -> value;                              //destination station index value
  listOfObjects < StationConnectionInfo * > * src_ = adjacency[toindex].toStations; //adjacency list
  TrainInfoPerStation * z = new TrainInfoPerStation(0, 0, 0, 0);                     //traininfoperstation constructor
  listOfObjects < TrainInfoPerStation * > * directjour = new listOfObjects < TrainInfoPerStation * > (z);
  while (src_ != NULL) {
    toindex = src_ -> object -> adjacentStnIndex;                                   //index of tostation 
    listOfObjects < TrainInfoPerStation * > * train = src_ -> object -> trains;     //list of trains of tostation
    while (train != nullptr) {
      jcode = train -> object -> journeyCode;                                       //journey code of train
      if (direct(toindex, desti, adjacency, jcode)) {
        gotit = true;                                                               //bool variable for found a direct journey
        listOfObjects < TrainInfoPerStation * > * copy = directjour;
        while (copy -> next != nullptr) {
          copy = copy -> next;
        }
        copy -> next = new listOfObjects < TrainInfoPerStation * > (train -> object); //appending the new direct journey found
      }
      train = train -> next;                                                          //else continue
    }
    src_ = src_ -> next;                                                              //else continue
  }
  printStationInfo(directjour);                                                       //print all the direct journey
  if (!gotit) {
    cout << "No direct journeys available" << endl;
  }

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
