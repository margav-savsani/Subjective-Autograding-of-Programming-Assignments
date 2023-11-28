#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName){

  int src_index = stnNameToIndex.get(srcStnName)->value;  //stored source index
  int dest_index = stnNameToIndex.get(destStnName)->value;  //stored destination index

  TrainInfoPerStation * t = new TrainInfoPerStation(0, 0, 0, 0);    //a dummy train
  listOfObjects<TrainInfoPerStation *> *req = new listOfObjects<TrainInfoPerStation *> (t);   //created a list to store the journeys
  listOfObjects<StationConnectionInfo *> *src_to = adjacency[src_index].toStations;     //stored the adjacent stations
  listOfObjects<StationConnectionInfo *> *s = src_to;

  while(s != nullptr){      //loop on adjacent stations of source
    listOfObjects<TrainInfoPerStation *> * stl = s->object->trains;     //stored trains of a station s
    while(stl != nullptr){          //loop on trains from source to it's adjacent station
      int s2i = s->object->adjacentStnIndex;
      int sc = stl->object->journeyCode;
      bool found = false;     //to say whether a journey is direct or not
      while(true){    // loop to check journeycode 
        if(s2i == -1){found = false;break;}
        else if (s2i == dest_index){found = true; break;}
        else{
          listOfObjects<StationConnectionInfo *> * d = adjacency[s2i].toStations;
          int p = 0;        //to store the station index, if it has a train with journey code equal to it's one of the fromstations trains journeycode
          int present = 0;    //checks whether a journey is found or not
          while(d != nullptr){      //loop on adjacent stations of adjacent stations of s2i
            int a=0;          //similar to p
            listOfObjects<TrainInfoPerStation *> * dtl = d->object->trains;
            while(dtl != nullptr){      //loop on trains from adjacent station of source to it's adjacent station
              int dc = dtl->object->journeyCode;
              if(sc == dc){
                p = d->object->adjacentStnIndex;
                a++;            //increments when given station and it's adjacent station has a journeys with same journeycode
              }
              if(a!= 0){break;}     //if a journey is found we break the loop as the searching for trains in that particular tostation should stop
              dtl = dtl->next;
            }
            if(a!= 0){present ++; break;}     //if a journey is found we break the loop as the searching for tostation should stop
            d = d->next;
          }
          if(present != 0){s2i = p;}
          else {found = false; break;}
        }
      }

      if(found == true){        //found true represents there is a direct journey from source to destination
        listOfObjects<TrainInfoPerStation *> * j = req;
          while(true){        //loop to find tail of the list we created
            if(j->next == nullptr) {
              listOfObjects<TrainInfoPerStation *> * temp = new listOfObjects<TrainInfoPerStation *> (stl->object);
              j->next = temp;     //adding the direct journey to the list
              j->next->prev = j;
              break;
            }
            j = j->next;
          }
      }
      stl = stl->next;
    }
    s = s->next;
  }
  if(req->next == nullptr){       //this represents there are no direct journeys
    cout<<"No direct journeys available"<<endl;
    return;
  }
  printStationInfo(req->next);     //call on printStationInfo function on the list(created) of direct journeys
}

#endif