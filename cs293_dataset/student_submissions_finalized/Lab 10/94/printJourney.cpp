#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

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

  int s=stnNameToIndex.get(srcStnName)->value; // source index
  int d=stnNameToIndex.get(destStnName)->value;// destination index
  
  // added a dummy element so that null pointer is not passed in functions
  TrainInfoPerStation *dummy=new TrainInfoPerStation(0,0,0,0);
  //the final list which is to be printed
  listOfObjects<TrainInfoPerStation*>*direct=new listOfObjects<TrainInfoPerStation*>(dummy);

  // adjacency list of source
  listOfObjects<StationConnectionInfo *> *to=adjacency[s].toStations;

  // searching without any condition(no train name)
  while(to!=NULL){
    int sindex=to->object->adjacentStnIndex;
    if(to->object->adjacentStnIndex==d){
      append(direct,to->object->trains); // appends if destination is found
    }
    else{ // iterates over every train and every adjacent node
      listOfObjects<TrainInfoPerStation*>*ite=to->object->trains;
      while(ite!=NULL){
        searchwithTrain(ite->object,sindex,d,direct,adjacency);
        ite=ite->next;
      }
    }
    to=to->next;
  }

  
  return;
}

#endif
