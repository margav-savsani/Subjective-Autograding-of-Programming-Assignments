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

  Entry<int> *srcStnIndexEntry = stnNameToIndex.get(srcStnName);
  Entry<int> *destStnIndexEntry = stnNameToIndex.get(destStnName);
  int srcStnIndex=srcStnIndexEntry->value;
  int destStnIndex=destStnIndexEntry->value;

  listOfObjects<listOfObjects<TrainInfoPerStation *>*> *journeys;
  
  
  listOfObjects<StationConnectionInfo *> *next= adjacency[srcStnIndex].toStations->next;
  listOfObjects<listOfObjects<TrainInfoPerStation *>*> *q;
  listOfObjects<TrainInfoPerStation *> *temp = new listOfObjects<TrainInfoPerStation*>(adjacency[srcStnIndex].toStations->object->trains->object);
  listOfObjects<TrainInfoPerStation *> *temp3 = temp;
  listOfObjects<TrainInfoPerStation *> *temp2 = adjacency[srcStnIndex].toStations->object->trains;
  return;
}

#endif
