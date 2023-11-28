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

  // insert your code here

  cout << "This function is to be implemented by you." << endl;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  listOfObjects<TrainInfoPerStation *> *srcTrains = stationInfo[stnNameToIndex.get(srcStnName)->value];
  listOfObjects<TrainInfoPerStation *> *destTrains = stationInfo[stnNameToIndex.get(srcStnName)->value];
  listOfObjects<TrainInfoPerStation *> *common = nullptr;

  listOfObjects<TrainInfoPerStation *> *tempSrc = srcTrains;
  listOfObjects<TrainInfoPerStation *> *tempDest = destTrains;
  listOfObjects<TrainInfoPerStation *> *tempCommon = common;

  while (tempSrc != nullptr)
  {
    while (tempDest != nullptr)
    {
      if (tempSrc->object->journeyCode == tempDest->object->journeyCode && tempSrc->object->stopSeq < tempDest->object->stopSeq)
      {
        if (common == nullptr)
        {
          common = new listOfObjects<TrainInfoPerStation *>(tempSrc->object->journeyCode, tempSrc->object->stopSeq, tempSrc->object->arrTime, tempSrc->object->depTime);
        }
      }
      tempDest = tempDest->next;
    }
    tempSrc = tempSrc->next;
  }
  return;
}

#endif
