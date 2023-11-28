#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

struct Element
{
  int stnidx;
  int jc;
};

bool operator==(TrainInfoPerStation a, TrainInfoPerStation b) {
  if (a.arrTime == b.arrTime && a.daysOfWeek == b.daysOfWeek && a.depTime == b.depTime && a.journeyCode == b.journeyCode)
    return true;
  else 
    return false;
} 

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp

  int src = stnNameToIndex.get(srcStnName)->value;
  int dest = stnNameToIndex.get(destStnName)->value;
  StationAdjacencyList* l = new StationAdjacencyList(adjacency[src]);
  listOfObjects<StationConnectionInfo *> *to_stn = l->toStations;
  StationAdjacencyList* d = new StationAdjacencyList(adjacency[dest]);
  listOfObjects<StationConnectionInfo *> *from_stn = d->fromStations;

  // result = (src.toStn.jc) intersection (dest.fromStn.jc)
  listOfObjects<TrainInfoPerStation*> *start = new listOfObjects<TrainInfoPerStation*>(new TrainInfoPerStation(0, 0, 0, 0));
  listOfObjects<int*> *stations_start = new listOfObjects<int*>(new int(0));
  listOfObjects<TrainInfoPerStation*> *end = new listOfObjects<TrainInfoPerStation*>(new TrainInfoPerStation(0, 0, 0, 0));
  listOfObjects<int*> *stations_end = new listOfObjects<int*>(new int(0));


  listOfObjects<TrainInfoPerStation*> *result = new listOfObjects<TrainInfoPerStation*>(new TrainInfoPerStation(0, 0, 0, 0));

  listOfObjects<int*> *stations = new listOfObjects<int*>(new int(0));

  listOfObjects<TrainInfoPerStation*> *startcpy = start;
  listOfObjects<int*> *stnstcpy = stations_start;
  // making first as dummy object, and finally shifting head to 2nd element
  while (to_stn != nullptr) {

    listOfObjects<TrainInfoPerStation*> *train = to_stn->object->trains;
    
    while (train != nullptr) {
      TrainInfoPerStation* journey = train->object; 
      start->next = new listOfObjects<TrainInfoPerStation*>(journey); start = start->next;
      stations_start->next = new listOfObjects<int*>(new int(to_stn->object->adjacentStnIndex)); stations_start = stations_start->next;
      train = train->next;
    }
    to_stn = to_stn->next;
  }
  start = startcpy->next;
  stations_start = stnstcpy->next;

  listOfObjects<TrainInfoPerStation*> *endcpy = end;
  listOfObjects<int*> *stnendcpy = stations_end;
  while (from_stn != nullptr) {
    listOfObjects<TrainInfoPerStation*> *train = from_stn->object->trains;

    while (train != nullptr) {
      TrainInfoPerStation* journey = train->object;
      end->next = new listOfObjects<TrainInfoPerStation*>(journey); end = end->next;

      stations_end->next = new listOfObjects<int*>(new int(from_stn->object->adjacentStnIndex)); stations_end = stations_end->next;

      train = train->next;
    }
    from_stn = from_stn->next;
  }
  end = endcpy->next;
  stations_end = stnendcpy->next;


  // taking intersection of these vectors
  
  listOfObjects<TrainInfoPerStation*>* resultcpy = result;
  listOfObjects<int*> *cpy = stations;
  while (start != nullptr) {
    bool flag = false;
    TrainInfoPerStation* targetobj;
    int targetstn;
    listOfObjects<TrainInfoPerStation*>*endcpy = end;
    while (end != nullptr) {
      if (start->object->journeyCode == end->object->journeyCode) {
        // checking if the object is there in end
        targetobj = new TrainInfoPerStation(*start->object);
        targetstn = *stations_start->object;
        flag = true;
        break;
      }
      end = end->next;
    }
    end = endcpy;
    if (flag) {
      
      result->next = new listOfObjects<TrainInfoPerStation*>(targetobj); result = result->next;
      stations->next = new listOfObjects<int*>(new int(targetstn)); stations = stations->next;
    }
    start = start->next; 
    stations_start = stations_start->next;
  }
  result = resultcpy->next;
  stations = cpy->next;
  // result formed. 
  if(result == nullptr) {
    cout << "No direct journeys available" << endl;
    return;
  }

  // initialising the queue -- using stationindex, journeycode struct. 
  listOfObjects<Element*> *Q = new listOfObjects<Element*>(new Element(Element{0,0}));

  listOfObjects<TrainInfoPerStation*> *resultcpy1 = result;
  listOfObjects<int*>* stncpy = stations;
  listOfObjects<Element*> *Qcpy = Q;
  while (resultcpy1 != nullptr) {
    Element push{*stncpy->object,resultcpy1->object->journeyCode};
    Q->next = new listOfObjects<Element*>(new Element(push)); Q = Q->next;
    resultcpy1 = resultcpy1->next;
    stncpy = stncpy->next;
  }
  // Q is already at the end of the linked list !
  Qcpy = Qcpy->next;
  // Maintaining a pointer to the last position of Q.
  // Queue initialised -- now running a while loop.
  while (Qcpy != nullptr) {
    Element currelem = *Qcpy->object; Qcpy = Qcpy->next;

    if (currelem.stnidx == dest) {
      // destination found : just continue
      continue;
    }

    StationAdjacencyList *list = new StationAdjacencyList(adjacency[currelem.stnidx]);

    // now iterating through the adjacency list of currelem to find journeycodes matching with those of result
    listOfObjects<StationConnectionInfo*>* to_stn1 = list->toStations;

    bool flag = false;
    while (to_stn1 != nullptr) {
      listOfObjects<TrainInfoPerStation*> *train = to_stn1->object->trains;
      while (train != nullptr) {
        if (train->object->journeyCode == currelem.jc) {
          Element e{to_stn1->object->adjacentStnIndex, currelem.jc};
          Q->next = new listOfObjects<Element*>(new Element(e)); Q = Q->next;
          flag = true;
          break;
        }
        train = train->next;
      }
      if (flag) break;
      to_stn1 = to_stn1->next;
    }

    if (flag) continue;

    else {
      // flag is false, i.e. journeycode is not found : path terminates -- remove it from possible results.

      listOfObjects<TrainInfoPerStation*>* rcpy = result;
      if (result->object->journeyCode == currelem.jc) {result = result->next; break;}
      while (result->next != nullptr) {
        TrainInfoPerStation* curr = result->object;
        if (curr->journeyCode == currelem.jc) {
          result->next = result->next->next;
          break;
        }
      }
    }
  }

  if(result == nullptr) {
    cout << "No direct journeys available" << endl;
    return;
  }
  printStationInfo(result);
  return;
}

#endif
