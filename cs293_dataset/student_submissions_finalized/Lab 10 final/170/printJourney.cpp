#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime){

  int src_index = stnNameToIndex.get(srcStnName)->value;
  int dest_index = stnNameToIndex.get(destStnName)->value;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  TrainInfoPerStation * t = new TrainInfoPerStation(0, 0, 0, 0);
  listOfObjects<TrainInfoPerStation *> *req = new listOfObjects<TrainInfoPerStation *> (t);
  listOfObjects<StationConnectionInfo *> *src_to = adjacency[src_index].toStations;
  listOfObjects<StationConnectionInfo *> *dest_from = adjacency[dest_index].fromStations;

  int a = 0;
  int b = 0;

  listOfObjects<StationConnectionInfo *> *s = src_to;
  while(s != nullptr){
    if(s->object->adjacentStnIndex == dest_index){
      listOfObjects<TrainInfoPerStation *> * j = req;
      while(true){
        if(j->next == nullptr) {
          j->next = s->object->trains;
          j->next->prev = j;
          b++;
          break;
        }
        j = j->next;
      }
    }
    s = s->next;
  }

  if(b != 1){
    listOfObjects<StationConnectionInfo *> *s = src_to;
    while(s != nullptr){
      listOfObjects<TrainInfoPerStation *> * stl = s->object->trains;
      while(stl != nullptr){
        int sc = stl->object->journeyCode;
        listOfObjects<StationConnectionInfo *> *d = dest_from;
        while(d != nullptr){
          listOfObjects<TrainInfoPerStation *> * dtl = d->object->trains;
          while(dtl != nullptr){
            int dc = dtl->object->journeyCode;
            if(sc == dc){
              listOfObjects<TrainInfoPerStation *> * j = req;
              while(true){
                if(j->next == nullptr) {
                  listOfObjects<TrainInfoPerStation *> * temp = new listOfObjects<TrainInfoPerStation *> (stl->object);
                  j->next = temp;
                  j->next->prev = j;
                  break;
                }
                j = j->next;
              }
              a++;
            }
            if(a == 1){break;}
            dtl = dtl->next;
          }
          if(a == 1){a=0; break;}
          d = d->next;
        }
        stl = stl->next;
      }
      s = s->next;
    }
  }
  if(req->next == nullptr){
    cout<<"No direct journeys available"<<endl;
    return;
  }
  printStationInfo(req->next);
}

#endif
