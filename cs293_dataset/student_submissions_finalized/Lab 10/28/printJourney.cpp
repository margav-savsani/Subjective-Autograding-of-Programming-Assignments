#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

class Node // Single vertex of the graph
{
public:
  int Index;
  listOfObjects<TrainInfoPerStation *> *trains;
  listOfObjects<TrainInfoPerStation *> *trains2;

  Node(int index)
  {
    Index = index;
    trains = NULL;
    trains2 = NULL;
  }
};
listOfObjects<TrainInfoPerStation *> *presentadd(listOfObjects<TrainInfoPerStation *> *train, listOfObjects<TrainInfoPerStation *> *trainsll)
{
  while (trainsll != NULL) // traversing the linked list
  {
    if (trainsll->object->journeyCode == train->object->journeyCode)
    {
      return trainsll;
    }
    trainsll = trainsll->next;
  }
  return NULL;
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
