#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

class qObj
{
public:
  int stn;
  int code;
  int changes;
};

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  listOfObjects<qObj> *q;
  qObj t;
  t.stn = 0;
  t.code = 0;
  t.changes = 0;
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
      x.changes = 0;
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
        if(x.code != q->object.code) x.changes = q->object.changes+1;
        else x.changes = q->object.changes;
        listOfObjects<TrainInfoPerStation *> *list = stationInfo[currStn->object->adjacentStnIndex];
        int arrival;
        while(list->object->journeyCode != x.code && list->)
        // put condition here
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
  // Whenever you need to print a journey, construct a
  // listOfObjects<TrainInfoPerStation *> appropriately, and then
  // use printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of
  // the Planner class. It is declared in planner.h and implemented in
  // planner.cpp
  return;
}

#endif
