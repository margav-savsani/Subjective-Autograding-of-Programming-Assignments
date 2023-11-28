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

  listOfObjects<TrainInfoPerStation *> *listhead = nullptr;
  listOfObjects<TrainInfoPerStation *> *listtail = nullptr;

  //each entry to adjacency array is pointer to object of type StationAdjacencyList
  //each object of StationAdjacencyList has two lists "toStations" and "fromStations"
  //each of these is a list of pointers to objects of class StationConnectionInfo
  //Each object of class StationConnectionInfo has a station index (recall all station 
  //names are mapped to unique indices through the dictionary stnNameToIndex in the 
  //class Planner (see planner.h), and a list of pointers to TrainInfoPerStation

  int srcindex = stnNameToIndex.get(srcStnName)->value;
  int destindex = stnNameToIndex.get(destStnName)->value;

  listOfObjects<TrainInfoPerStation *> *queuehead = nullptr;
  listOfObjects<TrainInfoPerStation *> *queuetail = nullptr;

  listOfObjects<int> *stncodeshead = nullptr;
  listOfObjects<int> *stncodestail = nullptr;

  istOfObjects<StationConnectionInfo *> *y = adjacency[destindex].fromStations;            //storing all journeycodes of trains reaching destination in an array
  while(y != nullptr){
    listOfObjects<TrainInfoPerStation *> *trs = y->object->trains;
    while(trs != nullptr){
      fromjourneycodes[count] = trs->object->journeyCode;
      count++;
      trs = trs->next;
    }
    y = y->next;
  }

  listOfObjects<StationConnectionInfo *> *x = adjacency[srcindex].toStations;                //contains(fromjourneycodes, temp->object->journeyCode)

  while(x != nullptr){
    listOfObjects<TrainInfoPerStation *> *temp = x->object->trains;
    while(temp != nullptr){
      if(std::find(fromjourneycodes, fromjourneycodes + 512, temp->object->journeyCode) != fromjourneycodes + 512){                            //as if array doesnt contain the journey code then the train wont reach dest at all so we don't include it in the queue
        if(alpha==1){
          queuehead = new listOfObjects<TrainInfoPerStation *>(temp->object);
          //queuehead->object = temp->object;
          stncodeshead = new listOfObjects<int>(x->object->adjacentStnIndex);
          queuetail = queuehead;
          stncodestail = stncodeshead;
          alpha++;
        }
        else{
          //queuetail->object = temp->object;
          queuetail->next = new listOfObjects<TrainInfoPerStation *>(temp->object);
          stncodestail->next = new listOfObjects<int>(x->object->adjacentStnIndex);
          //stncodestail->object = x->object->adjacentStnIndex;
          queuetail = queuetail->next;
          stncodestail = stncodestail->next;
        }
      }
      temp = temp->next;
    }
    x = x->next;
  }
  
  return;
}

#endif
