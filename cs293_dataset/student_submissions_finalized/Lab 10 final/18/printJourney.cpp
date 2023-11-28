#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef DICTIONARY_H
#include "dictionary.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include <bits/stdc++.h>
using namespace std;

struct Train{
  TrainInfoPerStation *A;
  int jCode;
  int arr;
  int dep;
  int srcIndex;
  int destIndex;
  string src;
  string dest;

  Train(TrainInfoPerStation *B){
    A = B;
    jCode = B->journeyCode;
    int i;
    for(i=0; i<7; i++){
      if(B->daysOfWeek[i]){
        break;
      }
    }
    //now i contains the index of day on which the train leaves
    arr = (2400*i) + B->arrTime;
    dep = (2400*i) + B->depTime;
  }
};

struct Journey{
  listOfObjects<Train *> *trains;
  Train *last;
  int stops;
  int transit; //transit time

  Journey(Train *A){
    listOfObjects<Train *> *n = new listOfObjects<Train *>(A);
    trains = n;
    last = A;
    stops = 0;
    transit = 0;
  }

  void add_train(Train *A){
    if(trains==nullptr){
      trains = new listOfObjects<Train *>(A);
      last=A;
      return;
    }
    if(last==A){
      return;
    }
    listOfObjects<Train *> *n = trains;
    while(n->next!=nullptr){
      n=n->next;
    }
    n->next = new listOfObjects<Train *>(A);
    last=A;
  }
};

void print(listOfObjects<Journey *> *toprint){
  while(toprint!=nullptr){
    Journey *currJourney = toprint->object;
    listOfObjects<Train *> *trains_toprint = currJourney->trains;
    Train *first = trains_toprint->object;
    cout<<"Train Code "<<first->jCode<<": Starts at "<<(first->src)<<" at "<<(first->arr)%2400<< " reaches "<<(first->dest)<<" at "<<(first->dep)%2400<<endl;
    while(trains_toprint->next!=nullptr){
      trains_toprint=trains_toprint->next;
      cout<<"Change to-"<<endl;
      Train *first = trains_toprint->object;
      cout<<"Train Code "<<first->jCode<<": Starts at "<<first->src<<" at "<<(first->arr)%2400<< " reaches "<<first->dest<<" at "<<(first->dep)%2400<<endl;
    }
    // cout<<"Total transit time in the jouney is "<<currJourney->transit<<endl;
    toprint=toprint->next;
  }
  return;
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{
  int srcStnIndex = stnNameToIndex.get(srcStnName)->value;  //source station name index
  int destStnIndex = stnNameToIndex.get(destStnName)->value;  // destination station name index

  deque<int> queue;   // bfs queue
  queue.push_back(srcStnIndex); 
  int* parents = new int[DICT_SIZE];  //indices of parent
  
  //dict of stn with trains reaching that stn which went to src stn too
  Dictionary<listOfObjects<TrainInfoPerStation*>*> trStn;

  //storing the source station
  Entry<listOfObjects<TrainInfoPerStation*>*> station(stationInfo[srcStnIndex]); 
  station.key = srcStnName; 
  trStn.put(station);

  while(!queue.empty()){ 
    if(queue.front() == destStnIndex){
      listOfObjects<TrainInfoPerStation*>* tr_list = trStn.get(destStnName)->value; //getting the list of trains reaching the destination station
      printStationInfo(tr_list);   //printing the output
    }
    else{    
      listOfObjects<StationConnectionInfo *> *adj = adjacency[queue.front()].toStations; //list of adjacent stations
      int iterator = 1;
      while(adj != nullptr){ 
        queue.push_back(adj->object->adjacentStnIndex);    //insertion in the queue
        parents[adj->object->adjacentStnIndex] = queue.front();

        int parentStnIndex = parents[adj->object->adjacentStnIndex];
        listOfObjects<TrainInfoPerStation*>* tr_l_p = trStn.get(stnNameToIndex.getKeyAtIndex(parentStnIndex))->value;  //trains leaving parent station
        listOfObjects<TrainInfoPerStation*>* tr_r_curr = stationInfo[adj->object->adjacentStnIndex];  //all trains reaching current station
        listOfObjects<TrainInfoPerStation*>* rec_tr_r_curr = tr_r_curr;                  
        listOfObjects<TrainInfoPerStation*>* tr_r = nullptr;                                           //trains reaching curr station from parent 
        listOfObjects<TrainInfoPerStation*>* rec_tr_r = nullptr;                                     
        bool first = true; 
        while(tr_l_p != nullptr){  //trains leaving parent station
          while(tr_r_curr != nullptr){   //trains arriving at current station
            if(tr_l_p->object->journeyCode == tr_r_curr->object->journeyCode){
              if(first){  
                first = false;
                tr_r = new listOfObjects<TrainInfoPerStation*>(tr_r_curr->object);
                rec_tr_r = tr_r;
              }
              else{  
                tr_r->next = new listOfObjects<TrainInfoPerStation*>(tr_r_curr->object);
                tr_r = tr_r->next;
              }
            }
            tr_r_curr = tr_r_curr->next;
          }
          tr_r_curr = rec_tr_r_curr;   
          tr_l_p = tr_l_p->next;
        }
        tr_r = rec_tr_r; 

        Entry<listOfObjects<TrainInfoPerStation*>*> newstation(tr_r);
        newstation.key = stnNameToIndex.getKeyAtIndex(adj->object->adjacentStnIndex);
        trStn.put(newstation);

        iterator++;
        
        adj = adj->next;

      }
    }
    queue.pop_front();  //bfs algorithm
  }

}



#endif
