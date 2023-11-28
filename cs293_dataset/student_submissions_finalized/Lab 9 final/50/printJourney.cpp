#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

class qObj
{
public:
  int stn;
  int code;
};

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  listOfObjects<qObj> *q;
  qObj t;
  t.stn = 0;
  t.code = 0;
  q = new listOfObjects<qObj>(t);
  listOfObjects<qObj> *qcurr = q;
  listOfObjects<int> *final;
  final = new listOfObjects<int>(0);
  listOfObjects<int> *finalcurr = final;
  listOfObjects<StationConnectionInfo *> *currStn = adjacency[stnNameToIndex.get(srcStnName)->value].toStations;
  while (currStn != nullptr)
  {
    listOfObjects<TrainInfoPerStation *> *currTrain = currStn->object->trains;
    while (currTrain != nullptr)
    {
      qObj x;
      x.stn = currStn->object->adjacentStnIndex;
      x.code = currTrain->object->journeyCode;
      listOfObjects<qObj> *qnext;
      qnext = new listOfObjects<qObj>(t);
      qcurr->object = x;
      qcurr->next = qnext;
      qnext->prev = qcurr;
      qcurr = qcurr->next;
      currTrain = currTrain->next;
    }
    currStn = currStn->next;
  }
  while (true)
  {
    if (q->object.stn == 0 && q->next == nullptr)
      break;
    listOfObjects<StationConnectionInfo *> *currStn = adjacency[q->object.stn].toStations;
    while (currStn != nullptr)
    {
      listOfObjects<TrainInfoPerStation *> *currTrain = currStn->object->trains;
      while (currTrain != nullptr)
      {
        qObj x;
        x.stn = currStn->object->adjacentStnIndex;
        x.code = currTrain->object->journeyCode;
        if (x.code == q->object.code)
        {
          listOfObjects<qObj> *qnext;
          qnext = new listOfObjects<qObj>(t);
          qcurr->object = x;
          qcurr->next = qnext;
          qnext->prev = qcurr;
          qcurr = qcurr->next;
        }
        currTrain = currTrain->next;
      }
      currStn = currStn->next;
    }
    if (q->object.stn == stnNameToIndex.get(destStnName)->value)
    {
      listOfObjects<int> *finalnext;
      finalnext = new listOfObjects<int>(0);
      finalcurr->object = q->object.code;
      finalcurr->next = finalnext;
      finalnext->prev = finalcurr;
      finalcurr = finalcurr->next;
    }
    listOfObjects<qObj> *del = q;
    q = q->next;
    delete del;
  }
  listOfObjects<TrainInfoPerStation *> *send;
  send = new listOfObjects<TrainInfoPerStation *>(nullptr);
  listOfObjects<TrainInfoPerStation *> *move = send;
  finalcurr = final;
  while (finalcurr != nullptr)
  {
    listOfObjects<TrainInfoPerStation *> *curr = stationInfo[stnNameToIndex.get(srcStnName)->value];
    while (curr != nullptr)
    {
      if (curr->object->journeyCode == finalcurr->object)
      {
        move->object = curr->object;
        listOfObjects<TrainInfoPerStation *> *temp;
        temp = new listOfObjects<TrainInfoPerStation *>(nullptr);
        move->next = temp;
        temp->prev = move;
        move = move->next;
      }
      curr = curr->next;
    }
    finalcurr = finalcurr->next;
  }
  if (send->object == nullptr)
  {
    cout << "No direct journeys available" << endl;
    return;
  }
  printStationInfo(send);
  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  return;
}

#endif
