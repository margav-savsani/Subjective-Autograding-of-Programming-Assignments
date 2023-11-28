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


  //Initializing a queue using array of fixed size as number of station has upper limit
  StationConnectionInfo *VisitQueue[DICT_SIZE];
  int queue_size=0; //size of the queue

  // stations to which we can go from source
  listOfObjects<StationConnectionInfo *> *toStations = (adjacency[(stnNameToIndex.get(srcStnName))->value]).toStations;
  
  // stations from which we can come to destination
  listOfObjects<StationConnectionInfo *> *fromStations = (adjacency[(stnNameToIndex.get(destStnName))->value]).fromStations;

  // defining 2 linked lists of int to store the relevent journey code from the above two lists 
  listOfObjects<int> *sourceOutList=nullptr;
  listOfObjects<int> *destInList=nullptr;

  // loop to store values in sourceOutList
  while(toStations != nullptr){
    listOfObjects<TrainInfoPerStation *> *trains = toStations->object->trains;
    while (trains!=nullptr){
      if (sourceOutList == nullptr){
        sourceOutList = new listOfObjects<int>(trains->object->journeyCode);
        trains = trains->next;
        continue;
      }
      sourceOutList->next = new listOfObjects<int>(trains->object->journeyCode);
      sourceOutList->next->prev = sourceOutList;
      sourceOutList = sourceOutList->next;
      trains = trains->next;
    }
    toStations = toStations->next;
  }
  
  // loop to store values in destInList
  while(fromStations != nullptr){
    listOfObjects<TrainInfoPerStation *> *trains = fromStations->object->trains;
    while (trains!=nullptr){
      if (destInList == nullptr){
        destInList = new listOfObjects<int>(trains->object->journeyCode);
        trains = trains->next;
        continue;
      }
      destInList->next = new listOfObjects<int>(trains->object->journeyCode);
      destInList->next->prev = destInList;
      destInList = destInList->next;     
      trains = trains->next;
    }
    fromStations = fromStations->next;
  }
  
  // taking intersection of the two lists and storing it in list
  listOfObjects<int> *list=nullptr;
  listOfObjects<int> *dummysourceOutList=sourceOutList;
  listOfObjects<int> *dummydestInList=destInList;
  while (dummysourceOutList != nullptr){
    while (dummydestInList != nullptr){
      if (dummysourceOutList->object == dummydestInList->object){
        if (list == nullptr){
          list = new listOfObjects<int>(dummysourceOutList->object);
        }
        else{
          listOfObjects<int> *dummylist=list;
          if (!(dummylist->object == dummysourceOutList->object)){
            while (dummylist->next != nullptr){
              dummylist = dummylist->next;
              if (dummylist->object == dummysourceOutList->object){
                break;
              }
            }
          }
          if (! (dummylist->object == dummysourceOutList->object)){
            dummylist->next = new listOfObjects<int>(dummysourceOutList->object);
            dummylist->next->prev = dummylist;
          }
        }
      }
      dummydestInList = dummydestInList->prev;
    }
    dummydestInList = destInList;
    dummysourceOutList = dummysourceOutList->prev;
  }



  // if nothing common then no need to go further
  if (list == nullptr){
    cout << "No direct journeys available" << endl;
    return;
  }
  
  // adding the source stationConnectionInfo in queue after creating it
  toStations = (adjacency[(stnNameToIndex.get(srcStnName))->value]).toStations;
  StationConnectionInfo *t = new StationConnectionInfo((stnNameToIndex.get(srcStnName))->value);
  listOfObjects<TrainInfoPerStation *> *k = t->trains;
  while(toStations != nullptr){
    listOfObjects<TrainInfoPerStation *> *h = toStations->object->trains;
    while (h!=nullptr){
      listOfObjects<int> *dummylist = list;
      while (dummylist != nullptr){
        if (dummylist->object == h->object->journeyCode){
          if (!t->trains){
            t->trains = new listOfObjects<TrainInfoPerStation *>(h->object);
            k = t->trains;
            break;
          }
          k->next = new listOfObjects<TrainInfoPerStation *>(h->object);
          k->next->prev = k;
          k = k->next;
          break;
        }
        dummylist = dummylist->next;
      }
      h = h->next;
    }
    toStations = toStations->next;
  }
  VisitQueue[queue_size] = t;
  queue_size++;

  //creating linked list variable to store the results
  listOfObjects<int> *ans=nullptr;

  // main loop of BFS
  while(queue_size){
    // popping one element from the queue
    StationConnectionInfo *p = VisitQueue[0];
    for (int i=0; i<queue_size; VisitQueue[i++] = VisitQueue[i+1]);
    queue_size--;

    // if the node is the dest station then print the info rather than doing more search
    if (p->adjacentStnIndex == (stnNameToIndex.get(destStnName))->value){
      listOfObjects<TrainInfoPerStation *> *h = p->trains;
      while (h!=nullptr){
        if (ans==nullptr){
          ans = new listOfObjects<int>(h->object->journeyCode);
        }
        else{
          ans->next = new listOfObjects<int>(h->object->journeyCode);
          ans->next->prev = ans;
          ans = ans->next;
        }
        h = h->next;
      }
      continue;
    }

    // storing the journeycodes which will be relevent for the next step (i.e. removing an element and putting its children in it)
    listOfObjects<int> *currentList=nullptr;
    listOfObjects<TrainInfoPerStation *> *x = p->trains;
    while (x!=nullptr){
      if (currentList == nullptr){
        currentList = new listOfObjects<int>(x->object->journeyCode);
        x = x->next;
        continue;
      }
      listOfObjects<int> *dummylist=currentList;
      if (!(dummylist->object == x->object->journeyCode)){
        while (dummylist->next){
          dummylist = dummylist->next;
          if (dummylist->object == x->object->journeyCode){
            break;
          }
        }
        if (!(dummylist->object == x->object->journeyCode)){
          dummylist->next = new listOfObjects<int>(x->object->journeyCode);
          dummylist->next->prev == dummylist;
        }
      }
      x = x->next;
    }

    // going through all the stations in toStations of the adjacent station index present in popped element
    listOfObjects<StationConnectionInfo *> *to = (adjacency[p->adjacentStnIndex]).toStations;
    while (to != nullptr){
      StationConnectionInfo *currentInfo = new StationConnectionInfo(to->object->adjacentStnIndex);
      listOfObjects<TrainInfoPerStation *> *r = currentInfo->trains;
      listOfObjects<TrainInfoPerStation *> *h = to->object->trains;
      while (h!=nullptr){
        listOfObjects<int> *dummylist = currentList;
        while (dummylist){
          if (dummylist->object == h->object->journeyCode){
            if (currentInfo->trains == nullptr){
              currentInfo->trains = new listOfObjects<TrainInfoPerStation *>(h->object);
              r = currentInfo->trains;
              break;
            }
            r->next = new listOfObjects<TrainInfoPerStation *>(h->object);
            r->next->prev = r;
            r = r->next;
            break;
          }
          dummylist = dummylist->next;
        }
        h = h->next;
      }
      if (currentInfo->trains!=nullptr){
        VisitQueue[queue_size] = currentInfo;
        queue_size++;
      }
      to = to->next;
    }
  }

  if (ans == nullptr){
    cout << "No direct journeys available" << endl;
  }
  // printing the final list
  listOfObjects<TrainInfoPerStation *> *printingList = stationInfo[(stnNameToIndex.get(srcStnName))->value];
  while (printingList != nullptr){
    listOfObjects<int> *dummyAns = ans;
    while(dummyAns){
      if (dummyAns->object == printingList->object->journeyCode){
        listOfObjects<TrainInfoPerStation *> *h = new listOfObjects<TrainInfoPerStation *>(printingList->object);
        printStationInfo(h);  
      }
      dummyAns=dummyAns->prev;
    }
    printingList = printingList->next;
  }

  //cout << "This function is to be implemented by you." << endl;

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
