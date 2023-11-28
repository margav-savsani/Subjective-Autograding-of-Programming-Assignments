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
  TrainInfoPerStation *train;
  int changes;
  int ini;
  qObj(){
    stn = 0;
    train = new TrainInfoPerStation(0, 0, 0, 0);
    changes = 0;
    ini = 0;
  }
};

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  listOfObjects<qObj> *q;
  qObj t;
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
      *(x.train) = *(currTrain->object);
      x.changes = 0;
      x.ini = x.stn;
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
        *(x.train) = *(currTrain->object);
        if(x.train->journeyCode != q->object.train->journeyCode) x.changes = q->object.changes+1;
        else x.changes = q->object.changes;
        x.ini = q->object.ini;
        int arrival = 0; int departure = 0;
        int i = 0;
        while(!q->object.train->daysOfWeek[i]) i++;
        departure = i*2400+q->object.train->depTime;
        i = 0;
        while(!x.train->daysOfWeek[i]) i++;
        arrival = i*2400+x.train->arrTime;
        if(x.changes <= maxStopOvers && departure-arrival <= maxTransitTime*100)
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
      finalcurr->object = q->object.ini;
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
    cout << "No such journeys available" << endl;
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
