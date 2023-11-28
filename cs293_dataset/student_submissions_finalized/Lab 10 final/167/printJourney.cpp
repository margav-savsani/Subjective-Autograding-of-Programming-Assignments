#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP
#ifndef STD_HEADERS_H
#include "std_headers.h"

#endif

using namespace std;
bool alljour(int stnindex, int destindex, StationAdjacencyList adjacency[], int jourcode, int maxstop, int maxStopOvers, listOfObjects < TrainInfoPerStation * > * onejour, listOfObjects < listOfObjects < TrainInfoPerStation * > * > * final) {

  if (stnindex == destindex) {
    listOfObjects < listOfObjects < TrainInfoPerStation * > * > * y = final;
    while (y -> next != nullptr) {
      y = y -> next;
    }
    listOfObjects < listOfObjects < TrainInfoPerStation * > * > * r = new listOfObjects < listOfObjects < TrainInfoPerStation * > * > (onejour);
    y -> next = r;
    return true;
  }
  if (maxstop > maxStopOvers + 1) {
    return false;
  }
  //if (stni == -1) {
  //  return false; 
  //}
  int stopcopy;
  bool check = false;
  listOfObjects < StationConnectionInfo * > * newsta = adjacency[stnindex].toStations; //to stations of stations with stni index
  while (newsta != nullptr) {
    listOfObjects < TrainInfoPerStation * > * trainlist = newsta -> object -> trains; //list of trains of tostation
    while (trainlist != nullptr) {
      int j=trainlist -> object -> journeyCode;
      stopcopy = maxstop;
      if (jourcode != trainlist -> object -> journeyCode) {
        maxstop++;
      }
      TrainInfoPerStation * u = new TrainInfoPerStation(0, 0, 0, 0);
      listOfObjects < TrainInfoPerStation * > * copy1 = new listOfObjects < TrainInfoPerStation * > (u);
      listOfObjects < TrainInfoPerStation * > * copy3 = onejour;
      listOfObjects < TrainInfoPerStation * > * copy2;

      while (copy3 != nullptr) {
        listOfObjects < TrainInfoPerStation * > * copy4 = copy1;
        while (copy4 -> next != NULL) {
          copy4 = copy4 -> next;
        }
        copy4 -> next = new listOfObjects < TrainInfoPerStation * > (copy3 -> object);
        copy2 = copy4 -> next;
        copy3 = copy3 -> next;
      }
      listOfObjects < TrainInfoPerStation * > * z = onejour;
      while (z -> next != nullptr) {
        z = z -> next;
      }
      z -> next = new listOfObjects < TrainInfoPerStation * > (trainlist -> object);
      int stninew = newsta -> object -> adjacentStnIndex;
      if (alljour(stninew, destindex, adjacency, maxstop, maxStopOvers, j, onejour, final)) {
        check = true;
      }
      onejour = copy1;
      if (jourcode == 0) {
        TrainInfoPerStation * cons = new TrainInfoPerStation(0, 0, 0, 0);
        onejour = new listOfObjects < TrainInfoPerStation * > (cons);
      }
      maxstop = stopcopy;
      trainlist = trainlist -> next;

    }
    newsta = newsta -> next;
  }
  if (check != true) {
    return false;
  }
  return true;
}
void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime) {
  int jourcode; //journey code
  bool checkjour = false; //bool for direct journey codes
  int stni = stnNameToIndex.get(srcStnName) -> value; //source station index value
  int desti = stnNameToIndex.get(destStnName) -> value; //destination station index value
  listOfObjects < StationConnectionInfo * > * src_ = adjacency[stni].toStations; //adjacency list
  TrainInfoPerStation * k = new TrainInfoPerStation(0, 0, 0, 0); //traininfoperstation constructor
  listOfObjects < TrainInfoPerStation * > * u = new listOfObjects < TrainInfoPerStation * > (k);
  listOfObjects < listOfObjects < TrainInfoPerStation * > * > * directjour = new listOfObjects < listOfObjects < TrainInfoPerStation * > * > (u);
  TrainInfoPerStation * tt = new TrainInfoPerStation(0, 0, 0, 0); //traininfoperstation constructor
  listOfObjects < TrainInfoPerStation * > * directjour1 = new listOfObjects < TrainInfoPerStation * > (tt);
  alljour(stni, desti, adjacency, 0, 0, maxStopOvers, directjour1, directjour);
  listOfObjects < listOfObjects < TrainInfoPerStation * > * > * a = directjour -> next;
  while (a != nullptr) {
    checkjour = true;
    cout << endl;
    printStationInfo(a -> object); 
    a = a -> next;
  }
  if (!checkjour) {
    cout << "No direct journeys available" << endl;
  }
  return;
}

#endif