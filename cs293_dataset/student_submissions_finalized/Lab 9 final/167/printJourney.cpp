#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"

#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"

#endif

using namespace std;

bool direct(int stni, int desti, StationAdjacencyList adjacency[], int jc) {
  bool k = false;                                                                   //bool variable for finding same journey code
  if (stni == desti) {
    return true;                                                                    //base case for recurrsion
  } 
  else if (stni == -1) {
    return false;                                                                   //base for terminating
  } 
  else {
    listOfObjects < StationConnectionInfo * > * adjsta = adjacency[stni].toStations; //to stations of stations with stni index
    while (adjsta != nullptr) {
      stni = adjsta -> object -> adjacentStnIndex;                                   //index to of to station
      listOfObjects < TrainInfoPerStation * > * train = adjsta -> object -> trains;  //list of trains of tostation
      while (train != nullptr) {
        if (jc == train -> object -> journeyCode) {
          k = true;                                                                  //if found the train with given journey code
          break;                                                                     //break
        } 
        else train = train -> next;                                                //else continue
      }
      if (k) {
        break;                                                                       //break the loop if found a train 
      } 
      else adjsta = adjsta -> next;                                                //else continue
    }
    if(k){
      return direct(stni, desti, adjacency, jc);                                     //recurrsion if not found
    } 
    else return false;                                                             //else return 
  }
}
void Planner::printDirectJourneys(string srcStnName, string destStnName) {
  int jcode;                                                                         //journey code
  bool gotit = false;                                                                //bool for direct journey codes
  int toindex = stnNameToIndex.get(srcStnName) -> value;                             //source station index value
  int desti = stnNameToIndex.get(destStnName) -> value;                              //destination station index value
  listOfObjects < StationConnectionInfo * > * src_ = adjacency[toindex].toStations; //adjacency list
  TrainInfoPerStation * z = new TrainInfoPerStation(0, 0, 0, 0);                     //traininfoperstation constructor
  listOfObjects < TrainInfoPerStation * > * directjour = new listOfObjects < TrainInfoPerStation * > (z);
  while (src_ != NULL) {
    toindex = src_ -> object -> adjacentStnIndex;                                   //index of tostation 
    listOfObjects < TrainInfoPerStation * > * train = src_ -> object -> trains;     //list of trains of tostation
    while (train != nullptr) {
      jcode = train -> object -> journeyCode;                                       //journey code of train
      if (direct(toindex, desti, adjacency, jcode)) {
        gotit = true;                                                               //bool variable for found a direct journey
        listOfObjects < TrainInfoPerStation * > * copy = directjour;
        while (copy -> next != nullptr) {
          copy = copy -> next;
        }
        copy -> next = new listOfObjects < TrainInfoPerStation * > (train -> object); //appending the new direct journey found
      }
      train = train -> next;                                                          //else continue
    }
    src_ = src_ -> next;                                                              //else continue
  }
  printStationInfo(directjour);                                                       //print all the direct journey
  if (!gotit) {
    cout << "No direct journeys available" << endl;
  }
  /*
        //jcode=trains->journeyCode;
        //p.push_back(tra);
        while(train!=nullptr){
          jcode=train->object->journeyCode;
          listOfObjects<StationConnectionInfo*> *adjsta=adjacency[toindex].toStations;
          while(adjsta!=NULL){
              listOfObjects<TrainInfoPerStation *> *train_=adjsta->object->trains;
              toindex=adjsta->object->adjacentStnIndex;
              if(toindex==desti){
              directjour=train_;
              //directjour=directjour->next;
              break;
              }
              while(train_!=nullptr){
              if(train_->object->journeyCode==jcode){
                 listOfObjects<StationConnectionInfo*> *a=adjacency[toindex].toStations;
                 while(a!=nullptr){
                  listOfObjects<TrainInfoPerStation *> *trainj=a->object->trains;
                  toindex=a->object->adjacentStnIndex;
                  if(toindex==desti){
                      directjour=trainj;
                      //directjour=directjour->next;
                      break;
                    }
                    a=a->next;
                  }
              }
                train_=train_->next;
          }
          adjsta=adjsta->next;
        }
        train=train->next;
        }
        src_=src_->next;
      }
      
        
        /*
          while(train_!=nullptr){
              if(train_->object->journeyCode==jcode){
                 listOfObjects<StationConnectionInfo*> *a=adjacency[toindex].toStations;
                 listOfObjects<TrainInfoPerStation *> *trainj=adjsta->object->trains;
                 toindex=a->object->adjacentStnIndex;
                 if(toindex==desti){
                    directjour=trainj;
                    directjour=directjour->next;
                    break;
                  }
                 while(trainj!=nullptr){
                  if(trainj->object->journeyCode==jcode){
                    listOfObjects<StationConnectionInfo*> *b=adjacency[toindex].toStations;
                    listOfObjects<TrainInfoPerStation *> *traink=adjsta->object->trains;
                    toindex=a->object->adjacentStnIndex;
                    if(toindex==desti){
                        directjour=traink;
                        directjour=directjour->next;
                        break;
                      }
                   }
                   trainj=trainj->next;
                 }
              }
              train_=train_->next;
          }
        }
        src_=src_->next;
      }*/
  // insert your code here

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp

  return;
}

#endif