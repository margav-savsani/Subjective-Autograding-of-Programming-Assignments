#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;
  
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

  // insert your code here
   // insert your code here
  listOfObjects<TrainInfoPerStation *> *station=nullptr;
  listOfObjects<TrainInfoPerStation *> *stat=nullptr;
  Entry<int> *index_start=stnNameToIndex.get(srcStnName);  //stoes the entry of the source station
  Entry<int> *index_end=stnNameToIndex.get(destStnName);  //stores the entry of the destination station
  int i=index_start->value;
  int j=index_end->value;
  listOfObjects<StationConnectionInfo *> *toS=adjacency[i].toStations;
  listOfObjects<StationConnectionInfo *> *fromS=adjacency[j].fromStations;
  listOfObjects<int> *arr=new listOfObjects<int> (0);
  listOfObjects<int> *array=arr;

  while(fromS!=NULL)
  {
  listOfObjects<TrainInfoPerStation *> *tra=fromS->object->trains;
    while(tra!=NULL)
    {
      int t=tra->object->journeyCode;
      arr->next=new listOfObjects<int>(t);//stores the codes of the from journeyCode 
      arr=arr->next;
      tra=tra->next;
    }
    fromS=fromS->next;
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
