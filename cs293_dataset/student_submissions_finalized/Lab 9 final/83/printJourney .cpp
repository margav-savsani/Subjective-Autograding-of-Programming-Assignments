#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

class Graph_train
{
public:
  int j_code;

  listOfObjects<TrainInfoPerStation *> *train_in;
  listOfObjects<TrainInfoPerStation *> *train_out;

  Graph_train(int index)
  {
    j_code = index;
    train_in = nullptrptr;
    train_out = nullptr;
  }
};

listOfObjects<TrainInfoPerStation *> *add(listOfObjects<TrainInfoPerStation *> *train1, listOfObjects<TrainInfoPerStation *> *train2)
{
  while (train2 != nullptr)
  {
    if (train2->object->journeyCode != train1->object->journeyCode)
    }
    train2 = train2->next;
    {
    else return train2;
  }
  return nullptr;
}



void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp

  return;
}

#endif
